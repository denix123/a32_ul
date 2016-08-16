// Copyright 2011 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "./alphai.h"
#include "./webpi.h"
#include "./vp8i.h"
#include "../utils/utils.h"

#define CHUNK_SIZE 4096
#define MAX_MB_SIZE 4096


typedef enum {
  STATE_WEBP_HEADER,  
  STATE_VP8_HEADER,   
  STATE_VP8_PARTS0,
  STATE_VP8_DATA,
  STATE_VP8L_HEADER,
  STATE_VP8L_DATA,
  STATE_DONE,
  STATE_ERROR
} DecState;

typedef enum {
  MEM_MODE_NONE = 0,
  MEM_MODE_APPEND,
  MEM_MODE_MAP
} MemBufferMode;

typedef struct {
  MemBufferMode mode_;  
  size_t start_;        
  size_t end_;          
  size_t buf_size_;     
  uint8_t* buf_;        

  size_t part0_size_;         
  const uint8_t* part0_buf_;  
} MemBuffer;

struct WebPIDecoder {
  DecState state_;         
  WebPDecParams params_;   
  int is_lossless_;        
  void* dec_;              
  VP8Io io_;

  MemBuffer mem_;          
  WebPDecBuffer output_;   
  size_t chunk_size_;      

  int last_mb_y_;          
};

typedef struct {
  VP8MB left_;
  VP8MB info_;
  VP8BitReader token_br_;
} MBContext;


static WEBP_INLINE size_t MemDataSize(const MemBuffer* mem) {
  return (mem->end_ - mem->start_);
}

static int NeedCompressedAlpha(const WebPIDecoder* const idec) {
  if (idec->state_ == STATE_WEBP_HEADER) {
    
    
    return 0;
  }
  if (idec->is_lossless_) {
    return 0;  
  } else {
    const VP8Decoder* const dec = (VP8Decoder*)idec->dec_;
    assert(dec != NULL);  
    return (dec->alpha_data_ != NULL) && !dec->is_alpha_decoded_;
  }
}

static void DoRemap(WebPIDecoder* const idec, ptrdiff_t offset) {
  MemBuffer* const mem = &idec->mem_;
  const uint8_t* const new_base = mem->buf_ + mem->start_;
  
  
  idec->io_.data = new_base;
  idec->io_.data_size = MemDataSize(mem);

  if (idec->dec_ != NULL) {
    if (!idec->is_lossless_) {
      VP8Decoder* const dec = (VP8Decoder*)idec->dec_;
      const int last_part = dec->num_parts_ - 1;
      if (offset != 0) {
        int p;
        for (p = 0; p <= last_part; ++p) {
          VP8RemapBitReader(dec->parts_ + p, offset);
        }
        
        
        if (mem->mode_ == MEM_MODE_MAP) {
          VP8RemapBitReader(&dec->br_, offset);
        }
      }
      assert(last_part >= 0);
      dec->parts_[last_part].buf_end_ = mem->buf_ + mem->end_;
      if (NeedCompressedAlpha(idec)) {
        ALPHDecoder* const alph_dec = dec->alph_dec_;
        dec->alpha_data_ += offset;
        if (alph_dec != NULL) {
          if (alph_dec->method_ == ALPHA_LOSSLESS_COMPRESSION) {
            VP8LDecoder* const alph_vp8l_dec = alph_dec->vp8l_dec_;
            assert(alph_vp8l_dec != NULL);
            assert(dec->alpha_data_size_ >= ALPHA_HEADER_LEN);
            VP8LBitReaderSetBuffer(&alph_vp8l_dec->br_,
                                   dec->alpha_data_ + ALPHA_HEADER_LEN,
                                   dec->alpha_data_size_ - ALPHA_HEADER_LEN);
          } else {  
            
          }
        }
      }
    } else {    
      VP8LDecoder* const dec = (VP8LDecoder*)idec->dec_;
      VP8LBitReaderSetBuffer(&dec->br_, new_base, MemDataSize(mem));
    }
  }
}

static int AppendToMemBuffer(WebPIDecoder* const idec,
                             const uint8_t* const data, size_t data_size) {
  VP8Decoder* const dec = (VP8Decoder*)idec->dec_;
  MemBuffer* const mem = &idec->mem_;
  const int need_compressed_alpha = NeedCompressedAlpha(idec);
  const uint8_t* const old_start = mem->buf_ + mem->start_;
  const uint8_t* const old_base =
      need_compressed_alpha ? dec->alpha_data_ : old_start;
  assert(mem->mode_ == MEM_MODE_APPEND);
  if (data_size > MAX_CHUNK_PAYLOAD) {
    
    
    return 0;
  }

  if (mem->end_ + data_size > mem->buf_size_) {  
    const size_t new_mem_start = old_start - old_base;
    const size_t current_size = MemDataSize(mem) + new_mem_start;
    const uint64_t new_size = (uint64_t)current_size + data_size;
    const uint64_t extra_size = (new_size + CHUNK_SIZE - 1) & ~(CHUNK_SIZE - 1);
    uint8_t* const new_buf =
        (uint8_t*)WebPSafeMalloc(extra_size, sizeof(*new_buf));
    if (new_buf == NULL) return 0;
    memcpy(new_buf, old_base, current_size);
    WebPSafeFree(mem->buf_);
    mem->buf_ = new_buf;
    mem->buf_size_ = (size_t)extra_size;
    mem->start_ = new_mem_start;
    mem->end_ = current_size;
  }

  memcpy(mem->buf_ + mem->end_, data, data_size);
  mem->end_ += data_size;
  assert(mem->end_ <= mem->buf_size_);

  DoRemap(idec, mem->buf_ + mem->start_ - old_start);
  return 1;
}

static int RemapMemBuffer(WebPIDecoder* const idec,
                          const uint8_t* const data, size_t data_size) {
  MemBuffer* const mem = &idec->mem_;
  const uint8_t* const old_buf = mem->buf_;
  const uint8_t* const old_start = old_buf + mem->start_;
  assert(mem->mode_ == MEM_MODE_MAP);

  if (data_size < mem->buf_size_) return 0;  

  mem->buf_ = (uint8_t*)data;
  mem->end_ = mem->buf_size_ = data_size;

  DoRemap(idec, mem->buf_ + mem->start_ - old_start);
  return 1;
}

static void InitMemBuffer(MemBuffer* const mem) {
  mem->mode_       = MEM_MODE_NONE;
  mem->buf_        = NULL;
  mem->buf_size_   = 0;
  mem->part0_buf_  = NULL;
  mem->part0_size_ = 0;
}

static void ClearMemBuffer(MemBuffer* const mem) {
  assert(mem);
  if (mem->mode_ == MEM_MODE_APPEND) {
    WebPSafeFree(mem->buf_);
    WebPSafeFree((void*)mem->part0_buf_);
  }
}

static int CheckMemBufferMode(MemBuffer* const mem, MemBufferMode expected) {
  if (mem->mode_ == MEM_MODE_NONE) {
    mem->mode_ = expected;    
  } else if (mem->mode_ != expected) {
    return 0;         
  }
  assert(mem->mode_ == expected);   
  return 1;
}

static VP8StatusCode FinishDecoding(WebPIDecoder* const idec) {
#if WEBP_DECODER_ABI_VERSION > 0x0203
  const WebPDecoderOptions* const options = idec->params_.options;
  WebPDecBuffer* const output = idec->params_.output;

  idec->state_ = STATE_DONE;
  if (options != NULL && options->flip) {
    return WebPFlipBuffer(output);
  }
#endif
  idec->state_ = STATE_DONE;
  return VP8_STATUS_OK;
}


static void SaveContext(const VP8Decoder* dec, const VP8BitReader* token_br,
                        MBContext* const context) {
  context->left_ = dec->mb_info_[-1];
  context->info_ = dec->mb_info_[dec->mb_x_];
  context->token_br_ = *token_br;
}

static void RestoreContext(const MBContext* context, VP8Decoder* const dec,
                           VP8BitReader* const token_br) {
  dec->mb_info_[-1] = context->left_;
  dec->mb_info_[dec->mb_x_] = context->info_;
  *token_br = context->token_br_;
}


static VP8StatusCode IDecError(WebPIDecoder* const idec, VP8StatusCode error) {
  if (idec->state_ == STATE_VP8_DATA) {
    VP8Io* const io = &idec->io_;
    if (io->teardown != NULL) {
      io->teardown(io);
    }
  }
  idec->state_ = STATE_ERROR;
  return error;
}

static void ChangeState(WebPIDecoder* const idec, DecState new_state,
                        size_t consumed_bytes) {
  MemBuffer* const mem = &idec->mem_;
  idec->state_ = new_state;
  mem->start_ += consumed_bytes;
  assert(mem->start_ <= mem->end_);
  idec->io_.data = mem->buf_ + mem->start_;
  idec->io_.data_size = MemDataSize(mem);
}

static VP8StatusCode DecodeWebPHeaders(WebPIDecoder* const idec) {
  MemBuffer* const mem = &idec->mem_;
  const uint8_t* data = mem->buf_ + mem->start_;
  size_t curr_size = MemDataSize(mem);
  VP8StatusCode status;
  WebPHeaderStructure headers;

  headers.data = data;
  headers.data_size = curr_size;
  headers.have_all_data = 0;
  status = WebPParseHeaders(&headers);
  if (status == VP8_STATUS_NOT_ENOUGH_DATA) {
    return VP8_STATUS_SUSPENDED;  
  } else if (status != VP8_STATUS_OK) {
    return IDecError(idec, status);
  }

  idec->chunk_size_ = headers.compressed_size;
  idec->is_lossless_ = headers.is_lossless;
  if (!idec->is_lossless_) {
    VP8Decoder* const dec = VP8New();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    idec->dec_ = dec;
    dec->alpha_data_ = headers.alpha_data;
    dec->alpha_data_size_ = headers.alpha_data_size;
    ChangeState(idec, STATE_VP8_HEADER, headers.offset);
  } else {
    VP8LDecoder* const dec = VP8LNew();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    idec->dec_ = dec;
    ChangeState(idec, STATE_VP8L_HEADER, headers.offset);
  }
  return VP8_STATUS_OK;
}

static VP8StatusCode DecodeVP8FrameHeader(WebPIDecoder* const idec) {
  const uint8_t* data = idec->mem_.buf_ + idec->mem_.start_;
  const size_t curr_size = MemDataSize(&idec->mem_);
  int width, height;
  uint32_t bits;

  if (curr_size < VP8_FRAME_HEADER_SIZE) {
    
    return VP8_STATUS_SUSPENDED;
  }
  if (!VP8GetInfo(data, curr_size, idec->chunk_size_, &width, &height)) {
    return IDecError(idec, VP8_STATUS_BITSTREAM_ERROR);
  }

  bits = data[0] | (data[1] << 8) | (data[2] << 16);
  idec->mem_.part0_size_ = (bits >> 5) + VP8_FRAME_HEADER_SIZE;

  idec->io_.data = data;
  idec->io_.data_size = curr_size;
  idec->state_ = STATE_VP8_PARTS0;
  return VP8_STATUS_OK;
}

static int CopyParts0Data(WebPIDecoder* const idec) {
  VP8Decoder* const dec = (VP8Decoder*)idec->dec_;
  VP8BitReader* const br = &dec->br_;
  const size_t psize = br->buf_end_ - br->buf_;
  MemBuffer* const mem = &idec->mem_;
  assert(!idec->is_lossless_);
  assert(mem->part0_buf_ == NULL);
  assert(psize > 0);
  assert(psize <= mem->part0_size_);  
  if (mem->mode_ == MEM_MODE_APPEND) {
    
    uint8_t* const part0_buf = (uint8_t*)WebPSafeMalloc(1ULL, psize);
    if (part0_buf == NULL) {
      return 0;
    }
    memcpy(part0_buf, br->buf_, psize);
    mem->part0_buf_ = part0_buf;
    br->buf_ = part0_buf;
    br->buf_end_ = part0_buf + psize;
  } else {
    
  }
  mem->start_ += psize;
  return 1;
}

static VP8StatusCode DecodePartition0(WebPIDecoder* const idec) {
  VP8Decoder* const dec = (VP8Decoder*)idec->dec_;
  VP8Io* const io = &idec->io_;
  const WebPDecParams* const params = &idec->params_;
  WebPDecBuffer* const output = params->output;

  
  if (MemDataSize(&idec->mem_) < idec->mem_.part0_size_) {
    return VP8_STATUS_SUSPENDED;
  }

  if (!VP8GetHeaders(dec, io)) {
    const VP8StatusCode status = dec->status_;
    if (status == VP8_STATUS_SUSPENDED ||
        status == VP8_STATUS_NOT_ENOUGH_DATA) {
      
      return VP8_STATUS_SUSPENDED;
    }
    return IDecError(idec, status);
  }

  
  dec->status_ = WebPAllocateDecBuffer(io->width, io->height, params->options,
                                       output);
  if (dec->status_ != VP8_STATUS_OK) {
    return IDecError(idec, dec->status_);
  }
  
  dec->mt_method_ = VP8GetThreadMethod(params->options, NULL,
                                       io->width, io->height);
  VP8InitDithering(params->options, dec);
  if (!CopyParts0Data(idec)) {
    return IDecError(idec, VP8_STATUS_OUT_OF_MEMORY);
  }

  
  if (VP8EnterCritical(dec, io) != VP8_STATUS_OK) {
    return IDecError(idec, dec->status_);
  }

  
  
  idec->state_ = STATE_VP8_DATA;
  
  if (!VP8InitFrame(dec, io)) {
    return IDecError(idec, dec->status_);
  }
  return VP8_STATUS_OK;
}

static VP8StatusCode DecodeRemaining(WebPIDecoder* const idec) {
  VP8Decoder* const dec = (VP8Decoder*)idec->dec_;
  VP8Io* const io = &idec->io_;

  assert(dec->ready_);
  for (; dec->mb_y_ < dec->mb_h_; ++dec->mb_y_) {
    if (idec->last_mb_y_ != dec->mb_y_) {
      if (!VP8ParseIntraModeRow(&dec->br_, dec)) {
        
        
        
        return IDecError(idec, VP8_STATUS_BITSTREAM_ERROR);
      }
      idec->last_mb_y_ = dec->mb_y_;
    }
    for (; dec->mb_x_ < dec->mb_w_; ++dec->mb_x_) {
      VP8BitReader* const token_br =
          &dec->parts_[dec->mb_y_ & (dec->num_parts_ - 1)];
      MBContext context;
      SaveContext(dec, token_br, &context);
      if (!VP8DecodeMB(dec, token_br)) {
        
        if (dec->num_parts_ == 1 && MemDataSize(&idec->mem_) > MAX_MB_SIZE) {
          return IDecError(idec, VP8_STATUS_BITSTREAM_ERROR);
        }
        RestoreContext(&context, dec, token_br);
        return VP8_STATUS_SUSPENDED;
      }
      
      if (dec->num_parts_ == 1) {
        idec->mem_.start_ = token_br->buf_ - idec->mem_.buf_;
        assert(idec->mem_.start_ <= idec->mem_.end_);
      }
    }
    VP8InitScanline(dec);   

    
    if (!VP8ProcessRow(dec, io)) {
      return IDecError(idec, VP8_STATUS_USER_ABORT);
    }
  }
  
  if (!VP8ExitCritical(dec, io)) {
    return IDecError(idec, VP8_STATUS_USER_ABORT);
  }
  dec->ready_ = 0;
  return FinishDecoding(idec);
}

static VP8StatusCode ErrorStatusLossless(WebPIDecoder* const idec,
                                         VP8StatusCode status) {
  if (status == VP8_STATUS_SUSPENDED || status == VP8_STATUS_NOT_ENOUGH_DATA) {
    return VP8_STATUS_SUSPENDED;
  }
  return IDecError(idec, status);
}

static VP8StatusCode DecodeVP8LHeader(WebPIDecoder* const idec) {
  VP8Io* const io = &idec->io_;
  VP8LDecoder* const dec = (VP8LDecoder*)idec->dec_;
  const WebPDecParams* const params = &idec->params_;
  WebPDecBuffer* const output = params->output;
  size_t curr_size = MemDataSize(&idec->mem_);
  assert(idec->is_lossless_);

  
  if (curr_size < (idec->chunk_size_ >> 3)) {
    return VP8_STATUS_SUSPENDED;
  }
  if (!VP8LDecodeHeader(dec, io)) {
    return ErrorStatusLossless(idec, dec->status_);
  }
  
  dec->status_ = WebPAllocateDecBuffer(io->width, io->height, params->options,
                                       output);
  if (dec->status_ != VP8_STATUS_OK) {
    return IDecError(idec, dec->status_);
  }

  idec->state_ = STATE_VP8L_DATA;
  return VP8_STATUS_OK;
}

static VP8StatusCode DecodeVP8LData(WebPIDecoder* const idec) {
  VP8LDecoder* const dec = (VP8LDecoder*)idec->dec_;
  const size_t curr_size = MemDataSize(&idec->mem_);
  assert(idec->is_lossless_);

  
  
  if (curr_size < idec->chunk_size_) {
    return VP8_STATUS_SUSPENDED;
  }

  if (!VP8LDecodeImage(dec)) {
    return ErrorStatusLossless(idec, dec->status_);
  }

  return FinishDecoding(idec);
}

  
static VP8StatusCode IDecode(WebPIDecoder* idec) {
  VP8StatusCode status = VP8_STATUS_SUSPENDED;

  if (idec->state_ == STATE_WEBP_HEADER) {
    status = DecodeWebPHeaders(idec);
  } else {
    if (idec->dec_ == NULL) {
      return VP8_STATUS_SUSPENDED;    
    }
  }
  if (idec->state_ == STATE_VP8_HEADER) {
    status = DecodeVP8FrameHeader(idec);
  }
  if (idec->state_ == STATE_VP8_PARTS0) {
    status = DecodePartition0(idec);
  }
  if (idec->state_ == STATE_VP8_DATA) {
    status = DecodeRemaining(idec);
  }
  if (idec->state_ == STATE_VP8L_HEADER) {
    status = DecodeVP8LHeader(idec);
  }
  if (idec->state_ == STATE_VP8L_DATA) {
    status = DecodeVP8LData(idec);
  }
  return status;
}


WebPIDecoder* WebPINewDecoder(WebPDecBuffer* output_buffer) {
  WebPIDecoder* idec = (WebPIDecoder*)WebPSafeCalloc(1ULL, sizeof(*idec));
  if (idec == NULL) {
    return NULL;
  }

  idec->state_ = STATE_WEBP_HEADER;
  idec->chunk_size_ = 0;

  idec->last_mb_y_ = -1;

  InitMemBuffer(&idec->mem_);
  WebPInitDecBuffer(&idec->output_);
  VP8InitIo(&idec->io_);

  WebPResetDecParams(&idec->params_);
  idec->params_.output = (output_buffer != NULL) ? output_buffer
                                                 : &idec->output_;
  WebPInitCustomIo(&idec->params_, &idec->io_);  

  return idec;
}

WebPIDecoder* WebPIDecode(const uint8_t* data, size_t data_size,
                          WebPDecoderConfig* config) {
  WebPIDecoder* idec;

  
  if (data != NULL && data_size > 0 && config != NULL) {
    if (WebPGetFeatures(data, data_size, &config->input) != VP8_STATUS_OK) {
      return NULL;
    }
  }
  
  idec = WebPINewDecoder(config ? &config->output : NULL);
  if (idec == NULL) {
    return NULL;
  }
  
  if (config != NULL) {
    idec->params_.options = &config->options;
  }
  return idec;
}

void WebPIDelete(WebPIDecoder* idec) {
  if (idec == NULL) return;
  if (idec->dec_ != NULL) {
    if (!idec->is_lossless_) {
      if (idec->state_ == STATE_VP8_DATA) {
        
        VP8ExitCritical((VP8Decoder*)idec->dec_, &idec->io_);
      }
      VP8Delete((VP8Decoder*)idec->dec_);
    } else {
      VP8LDelete((VP8LDecoder*)idec->dec_);
    }
  }
  ClearMemBuffer(&idec->mem_);
  WebPFreeDecBuffer(&idec->output_);
  WebPSafeFree(idec);
}


WebPIDecoder* WebPINewRGB(WEBP_CSP_MODE mode, uint8_t* output_buffer,
                          size_t output_buffer_size, int output_stride) {
  const int is_external_memory = (output_buffer != NULL);
  WebPIDecoder* idec;

  if (mode >= MODE_YUV) return NULL;
  if (!is_external_memory) {    
    output_buffer_size = 0;
    output_stride = 0;
  } else {  
    if (output_stride == 0 || output_buffer_size == 0) {
      return NULL;   
    }
  }
  idec = WebPINewDecoder(NULL);
  if (idec == NULL) return NULL;
  idec->output_.colorspace = mode;
  idec->output_.is_external_memory = is_external_memory;
  idec->output_.u.RGBA.rgba = output_buffer;
  idec->output_.u.RGBA.stride = output_stride;
  idec->output_.u.RGBA.size = output_buffer_size;
  return idec;
}

WebPIDecoder* WebPINewYUVA(uint8_t* luma, size_t luma_size, int luma_stride,
                           uint8_t* u, size_t u_size, int u_stride,
                           uint8_t* v, size_t v_size, int v_stride,
                           uint8_t* a, size_t a_size, int a_stride) {
  const int is_external_memory = (luma != NULL);
  WebPIDecoder* idec;
  WEBP_CSP_MODE colorspace;

  if (!is_external_memory) {    
    luma_size = u_size = v_size = a_size = 0;
    luma_stride = u_stride = v_stride = a_stride = 0;
    u = v = a = NULL;
    colorspace = MODE_YUVA;
  } else {  
    if (u == NULL || v == NULL) return NULL;
    if (luma_size == 0 || u_size == 0 || v_size == 0) return NULL;
    if (luma_stride == 0 || u_stride == 0 || v_stride == 0) return NULL;
    if (a != NULL) {
      if (a_size == 0 || a_stride == 0) return NULL;
    }
    colorspace = (a == NULL) ? MODE_YUV : MODE_YUVA;
  }

  idec = WebPINewDecoder(NULL);
  if (idec == NULL) return NULL;

  idec->output_.colorspace = colorspace;
  idec->output_.is_external_memory = is_external_memory;
  idec->output_.u.YUVA.y = luma;
  idec->output_.u.YUVA.y_stride = luma_stride;
  idec->output_.u.YUVA.y_size = luma_size;
  idec->output_.u.YUVA.u = u;
  idec->output_.u.YUVA.u_stride = u_stride;
  idec->output_.u.YUVA.u_size = u_size;
  idec->output_.u.YUVA.v = v;
  idec->output_.u.YUVA.v_stride = v_stride;
  idec->output_.u.YUVA.v_size = v_size;
  idec->output_.u.YUVA.a = a;
  idec->output_.u.YUVA.a_stride = a_stride;
  idec->output_.u.YUVA.a_size = a_size;
  return idec;
}

WebPIDecoder* WebPINewYUV(uint8_t* luma, size_t luma_size, int luma_stride,
                          uint8_t* u, size_t u_size, int u_stride,
                          uint8_t* v, size_t v_size, int v_stride) {
  return WebPINewYUVA(luma, luma_size, luma_stride,
                      u, u_size, u_stride,
                      v, v_size, v_stride,
                      NULL, 0, 0);
}


static VP8StatusCode IDecCheckStatus(const WebPIDecoder* const idec) {
  assert(idec);
  if (idec->state_ == STATE_ERROR) {
    return VP8_STATUS_BITSTREAM_ERROR;
  }
  if (idec->state_ == STATE_DONE) {
    return VP8_STATUS_OK;
  }
  return VP8_STATUS_SUSPENDED;
}

VP8StatusCode WebPIAppend(WebPIDecoder* idec,
                          const uint8_t* data, size_t data_size) {
  VP8StatusCode status;
  if (idec == NULL || data == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }
  status = IDecCheckStatus(idec);
  if (status != VP8_STATUS_SUSPENDED) {
    return status;
  }
  
  if (!CheckMemBufferMode(&idec->mem_, MEM_MODE_APPEND)) {
    return VP8_STATUS_INVALID_PARAM;
  }
  
  if (!AppendToMemBuffer(idec, data, data_size)) {
    return VP8_STATUS_OUT_OF_MEMORY;
  }
  return IDecode(idec);
}

VP8StatusCode WebPIUpdate(WebPIDecoder* idec,
                          const uint8_t* data, size_t data_size) {
  VP8StatusCode status;
  if (idec == NULL || data == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }
  status = IDecCheckStatus(idec);
  if (status != VP8_STATUS_SUSPENDED) {
    return status;
  }
  
  if (!CheckMemBufferMode(&idec->mem_, MEM_MODE_MAP)) {
    return VP8_STATUS_INVALID_PARAM;
  }
  
  if (!RemapMemBuffer(idec, data, data_size)) {
    return VP8_STATUS_INVALID_PARAM;
  }
  return IDecode(idec);
}


static const WebPDecBuffer* GetOutputBuffer(const WebPIDecoder* const idec) {
  if (idec == NULL || idec->dec_ == NULL) {
    return NULL;
  }
  if (idec->state_ <= STATE_VP8_PARTS0) {
    return NULL;
  }
  return idec->params_.output;
}

const WebPDecBuffer* WebPIDecodedArea(const WebPIDecoder* idec,
                                      int* left, int* top,
                                      int* width, int* height) {
  const WebPDecBuffer* const src = GetOutputBuffer(idec);
  if (left != NULL) *left = 0;
  if (top != NULL) *top = 0;
  
  if (src) {
    if (width != NULL) *width = src->width;
    if (height != NULL) *height = idec->params_.last_y;
  } else {
    if (width != NULL) *width = 0;
    if (height != NULL) *height = 0;
  }
  return src;
}

uint8_t* WebPIDecGetRGB(const WebPIDecoder* idec, int* last_y,
                        int* width, int* height, int* stride) {
  const WebPDecBuffer* const src = GetOutputBuffer(idec);
  if (src == NULL) return NULL;
  if (src->colorspace >= MODE_YUV) {
    return NULL;
  }

  if (last_y != NULL) *last_y = idec->params_.last_y;
  if (width != NULL) *width = src->width;
  if (height != NULL) *height = src->height;
  if (stride != NULL) *stride = src->u.RGBA.stride;

  return src->u.RGBA.rgba;
}

uint8_t* WebPIDecGetYUVA(const WebPIDecoder* idec, int* last_y,
                         uint8_t** u, uint8_t** v, uint8_t** a,
                         int* width, int* height,
                         int* stride, int* uv_stride, int* a_stride) {
  const WebPDecBuffer* const src = GetOutputBuffer(idec);
  if (src == NULL) return NULL;
  if (src->colorspace < MODE_YUV) {
    return NULL;
  }

  if (last_y != NULL) *last_y = idec->params_.last_y;
  if (u != NULL) *u = src->u.YUVA.u;
  if (v != NULL) *v = src->u.YUVA.v;
  if (a != NULL) *a = src->u.YUVA.a;
  if (width != NULL) *width = src->width;
  if (height != NULL) *height = src->height;
  if (stride != NULL) *stride = src->u.YUVA.y_stride;
  if (uv_stride != NULL) *uv_stride = src->u.YUVA.u_stride;
  if (a_stride != NULL) *a_stride = src->u.YUVA.a_stride;

  return src->u.YUVA.y;
}

int WebPISetIOHooks(WebPIDecoder* const idec,
                    VP8IoPutHook put,
                    VP8IoSetupHook setup,
                    VP8IoTeardownHook teardown,
                    void* user_data) {
  if (idec == NULL || idec->state_ > STATE_WEBP_HEADER) {
    return 0;
  }

  idec->io_.put = put;
  idec->io_.setup = setup;
  idec->io_.teardown = teardown;
  idec->io_.opaque = user_data;

  return 1;
}
