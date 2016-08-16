// Copyright 2010 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#include <stdlib.h>

#include "./vp8i.h"
#include "./vp8li.h"
#include "./webpi.h"
#include "../webp/mux_types.h"  

// Note: chunk data size must be padded to multiple of 2 when written.

static WEBP_INLINE uint32_t get_le24(const uint8_t* const data) {
  return data[0] | (data[1] << 8) | (data[2] << 16);
}

static WEBP_INLINE uint32_t get_le32(const uint8_t* const data) {
  return (uint32_t)get_le24(data) | (data[3] << 24);
}

static VP8StatusCode ParseRIFF(const uint8_t** const data,
                               size_t* const data_size, int have_all_data,
                               size_t* const riff_size) {
  assert(data != NULL);
  assert(data_size != NULL);
  assert(riff_size != NULL);

  *riff_size = 0;  
  if (*data_size >= RIFF_HEADER_SIZE && !memcmp(*data, "RIFF", TAG_SIZE)) {
    if (memcmp(*data + 8, "WEBP", TAG_SIZE)) {
      return VP8_STATUS_BITSTREAM_ERROR;  
    } else {
      const uint32_t size = get_le32(*data + TAG_SIZE);
      
      if (size < TAG_SIZE + CHUNK_HEADER_SIZE) {
        return VP8_STATUS_BITSTREAM_ERROR;
      }
      if (size > MAX_CHUNK_PAYLOAD) {
        return VP8_STATUS_BITSTREAM_ERROR;
      }
      if (have_all_data && (size > *data_size - CHUNK_HEADER_SIZE)) {
        return VP8_STATUS_NOT_ENOUGH_DATA;  
      }
      
      *riff_size = size;
      *data += RIFF_HEADER_SIZE;
      *data_size -= RIFF_HEADER_SIZE;
    }
  }
  return VP8_STATUS_OK;
}

static VP8StatusCode ParseVP8X(const uint8_t** const data,
                               size_t* const data_size,
                               int* const found_vp8x,
                               int* const width_ptr, int* const height_ptr,
                               uint32_t* const flags_ptr) {
  const uint32_t vp8x_size = CHUNK_HEADER_SIZE + VP8X_CHUNK_SIZE;
  assert(data != NULL);
  assert(data_size != NULL);
  assert(found_vp8x != NULL);

  *found_vp8x = 0;

  if (*data_size < CHUNK_HEADER_SIZE) {
    return VP8_STATUS_NOT_ENOUGH_DATA;  
  }

  if (!memcmp(*data, "VP8X", TAG_SIZE)) {
    int width, height;
    uint32_t flags;
    const uint32_t chunk_size = get_le32(*data + TAG_SIZE);
    if (chunk_size != VP8X_CHUNK_SIZE) {
      return VP8_STATUS_BITSTREAM_ERROR;  
    }

    
    if (*data_size < vp8x_size) {
      return VP8_STATUS_NOT_ENOUGH_DATA;  
    }
    flags = get_le32(*data + 8);
    width = 1 + get_le24(*data + 12);
    height = 1 + get_le24(*data + 15);
    if (width * (uint64_t)height >= MAX_IMAGE_AREA) {
      return VP8_STATUS_BITSTREAM_ERROR;  
    }

    if (flags_ptr != NULL) *flags_ptr = flags;
    if (width_ptr != NULL) *width_ptr = width;
    if (height_ptr != NULL) *height_ptr = height;
    
    *data += vp8x_size;
    *data_size -= vp8x_size;
    *found_vp8x = 1;
  }
  return VP8_STATUS_OK;
}

static VP8StatusCode ParseOptionalChunks(const uint8_t** const data,
                                         size_t* const data_size,
                                         size_t const riff_size,
                                         const uint8_t** const alpha_data,
                                         size_t* const alpha_size) {
  const uint8_t* buf;
  size_t buf_size;
  uint32_t total_size = TAG_SIZE +           
                        CHUNK_HEADER_SIZE +  
                        VP8X_CHUNK_SIZE;     
  assert(data != NULL);
  assert(data_size != NULL);
  buf = *data;
  buf_size = *data_size;

  assert(alpha_data != NULL);
  assert(alpha_size != NULL);
  *alpha_data = NULL;
  *alpha_size = 0;

  while (1) {
    uint32_t chunk_size;
    uint32_t disk_chunk_size;   

    *data = buf;
    *data_size = buf_size;

    if (buf_size < CHUNK_HEADER_SIZE) {  
      return VP8_STATUS_NOT_ENOUGH_DATA;
    }

    chunk_size = get_le32(buf + TAG_SIZE);
    if (chunk_size > MAX_CHUNK_PAYLOAD) {
      return VP8_STATUS_BITSTREAM_ERROR;          
    }
    
    disk_chunk_size = (CHUNK_HEADER_SIZE + chunk_size + 1) & ~1;
    total_size += disk_chunk_size;

    
    if (riff_size > 0 && (total_size > riff_size)) {
      return VP8_STATUS_BITSTREAM_ERROR;          
    }

    
    
    
    
    if (!memcmp(buf, "VP8 ", TAG_SIZE) ||
        !memcmp(buf, "VP8L", TAG_SIZE)) {
      return VP8_STATUS_OK;
    }

    if (buf_size < disk_chunk_size) {             
      return VP8_STATUS_NOT_ENOUGH_DATA;
    }

    if (!memcmp(buf, "ALPH", TAG_SIZE)) {         
      *alpha_data = buf + CHUNK_HEADER_SIZE;
      *alpha_size = chunk_size;
    }

    
    buf += disk_chunk_size;
    buf_size -= disk_chunk_size;
  }
}

static VP8StatusCode ParseVP8Header(const uint8_t** const data_ptr,
                                    size_t* const data_size, int have_all_data,
                                    size_t riff_size, size_t* const chunk_size,
                                    int* const is_lossless) {
  const uint8_t* const data = *data_ptr;
  const int is_vp8 = !memcmp(data, "VP8 ", TAG_SIZE);
  const int is_vp8l = !memcmp(data, "VP8L", TAG_SIZE);
  const uint32_t minimal_size =
      TAG_SIZE + CHUNK_HEADER_SIZE;  
                                     
  assert(data != NULL);
  assert(data_size != NULL);
  assert(chunk_size != NULL);
  assert(is_lossless != NULL);

  if (*data_size < CHUNK_HEADER_SIZE) {
    return VP8_STATUS_NOT_ENOUGH_DATA;  
  }

  if (is_vp8 || is_vp8l) {
    
    const uint32_t size = get_le32(data + TAG_SIZE);
    if ((riff_size >= minimal_size) && (size > riff_size - minimal_size)) {
      return VP8_STATUS_BITSTREAM_ERROR;  
    }
    if (have_all_data && (size > *data_size - CHUNK_HEADER_SIZE)) {
      return VP8_STATUS_NOT_ENOUGH_DATA;  
    }
    
    *chunk_size = size;
    *data_ptr += CHUNK_HEADER_SIZE;
    *data_size -= CHUNK_HEADER_SIZE;
    *is_lossless = is_vp8l;
  } else {
    
    *is_lossless = VP8LCheckSignature(data, *data_size);
    *chunk_size = *data_size;
  }

  return VP8_STATUS_OK;
}


static VP8StatusCode ParseHeadersInternal(const uint8_t* data,
                                          size_t data_size,
                                          int* const width,
                                          int* const height,
                                          int* const has_alpha,
                                          int* const has_animation,
                                          int* const format,
                                          WebPHeaderStructure* const headers) {
  int canvas_width = 0;
  int canvas_height = 0;
  int image_width = 0;
  int image_height = 0;
  int found_riff = 0;
  int found_vp8x = 0;
  int animation_present = 0;
  int fragments_present = 0;
  const int have_all_data = (headers != NULL) ? headers->have_all_data : 0;

  VP8StatusCode status;
  WebPHeaderStructure hdrs;

  if (data == NULL || data_size < RIFF_HEADER_SIZE) {
    return VP8_STATUS_NOT_ENOUGH_DATA;
  }
  memset(&hdrs, 0, sizeof(hdrs));
  hdrs.data = data;
  hdrs.data_size = data_size;

  
  status = ParseRIFF(&data, &data_size, have_all_data, &hdrs.riff_size);
  if (status != VP8_STATUS_OK) {
    return status;   
  }
  found_riff = (hdrs.riff_size > 0);

  
  {
    uint32_t flags = 0;
    status = ParseVP8X(&data, &data_size, &found_vp8x,
                       &canvas_width, &canvas_height, &flags);
    if (status != VP8_STATUS_OK) {
      return status;  
    }
    animation_present = !!(flags & ANIMATION_FLAG);
    fragments_present = !!(flags & FRAGMENTS_FLAG);
    if (!found_riff && found_vp8x) {
      
      
      return VP8_STATUS_BITSTREAM_ERROR;
    }
    if (has_alpha != NULL) *has_alpha = !!(flags & ALPHA_FLAG);
    if (has_animation != NULL) *has_animation = animation_present;
    if (format != NULL) *format = 0;   

    if (found_vp8x && (animation_present || fragments_present) &&
        headers == NULL) {
      if (width != NULL) *width = canvas_width;
      if (height != NULL) *height = canvas_height;
      return VP8_STATUS_OK;  
    }
  }

  if (data_size < TAG_SIZE) return VP8_STATUS_NOT_ENOUGH_DATA;

  
  if ((found_riff && found_vp8x) ||
      (!found_riff && !found_vp8x && !memcmp(data, "ALPH", TAG_SIZE))) {
    status = ParseOptionalChunks(&data, &data_size, hdrs.riff_size,
                                 &hdrs.alpha_data, &hdrs.alpha_data_size);
    if (status != VP8_STATUS_OK) {
      return status;  
    }
  }

  
  status = ParseVP8Header(&data, &data_size, have_all_data, hdrs.riff_size,
                          &hdrs.compressed_size, &hdrs.is_lossless);
  if (status != VP8_STATUS_OK) {
    return status;  
  }
  if (hdrs.compressed_size > MAX_CHUNK_PAYLOAD) {
    return VP8_STATUS_BITSTREAM_ERROR;
  }

  if (format != NULL && !(animation_present || fragments_present)) {
    *format = hdrs.is_lossless ? 2 : 1;
  }

  if (!hdrs.is_lossless) {
    if (data_size < VP8_FRAME_HEADER_SIZE) {
      return VP8_STATUS_NOT_ENOUGH_DATA;
    }
    
    if (!VP8GetInfo(data, data_size, (uint32_t)hdrs.compressed_size,
                    &image_width, &image_height)) {
      return VP8_STATUS_BITSTREAM_ERROR;
    }
  } else {
    if (data_size < VP8L_FRAME_HEADER_SIZE) {
      return VP8_STATUS_NOT_ENOUGH_DATA;
    }
    
    if (!VP8LGetInfo(data, data_size, &image_width, &image_height, has_alpha)) {
      return VP8_STATUS_BITSTREAM_ERROR;
    }
  }
  
  if (found_vp8x) {
    if (canvas_width != image_width || canvas_height != image_height) {
      return VP8_STATUS_BITSTREAM_ERROR;
    }
  }
  if (width != NULL) *width = image_width;
  if (height != NULL) *height = image_height;
  if (has_alpha != NULL) {
    
    
    *has_alpha |= (hdrs.alpha_data != NULL);
  }
  if (headers != NULL) {
    *headers = hdrs;
    headers->offset = data - headers->data;
    assert((uint64_t)(data - headers->data) < MAX_CHUNK_PAYLOAD);
    assert(headers->offset == headers->data_size - data_size);
  }
  return VP8_STATUS_OK;  
}

VP8StatusCode WebPParseHeaders(WebPHeaderStructure* const headers) {
  VP8StatusCode status;
  int has_animation = 0;
  assert(headers != NULL);
  
  status = ParseHeadersInternal(headers->data, headers->data_size,
                                NULL, NULL, NULL, &has_animation,
                                NULL, headers);
  if (status == VP8_STATUS_OK || status == VP8_STATUS_NOT_ENOUGH_DATA) {
    
    if (has_animation) {
      status = VP8_STATUS_UNSUPPORTED_FEATURE;
    }
  }
  return status;
}


void WebPResetDecParams(WebPDecParams* const params) {
  if (params != NULL) {
    memset(params, 0, sizeof(*params));
  }
}


static VP8StatusCode DecodeInto(const uint8_t* const data, size_t data_size,
                                WebPDecParams* const params) {
  VP8StatusCode status;
  VP8Io io;
  WebPHeaderStructure headers;

  headers.data = data;
  headers.data_size = data_size;
  headers.have_all_data = 1;
  status = WebPParseHeaders(&headers);   
  if (status != VP8_STATUS_OK) {
    return status;
  }

  assert(params != NULL);
  VP8InitIo(&io);
  io.data = headers.data + headers.offset;
  io.data_size = headers.data_size - headers.offset;
  WebPInitCustomIo(params, &io);  

  if (!headers.is_lossless) {
    VP8Decoder* const dec = VP8New();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    dec->alpha_data_ = headers.alpha_data;
    dec->alpha_data_size_ = headers.alpha_data_size;

    
    if (!VP8GetHeaders(dec, &io)) {
      status = dec->status_;   
    } else {
      
      status = WebPAllocateDecBuffer(io.width, io.height, params->options,
                                     params->output);
      if (status == VP8_STATUS_OK) {  
        
        dec->mt_method_ = VP8GetThreadMethod(params->options, &headers,
                                             io.width, io.height);
        VP8InitDithering(params->options, dec);
        if (!VP8Decode(dec, &io)) {
          status = dec->status_;
        }
      }
    }
    VP8Delete(dec);
  } else {
    VP8LDecoder* const dec = VP8LNew();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    if (!VP8LDecodeHeader(dec, &io)) {
      status = dec->status_;   
    } else {
      
      status = WebPAllocateDecBuffer(io.width, io.height, params->options,
                                     params->output);
      if (status == VP8_STATUS_OK) {  
        if (!VP8LDecodeImage(dec)) {
          status = dec->status_;
        }
      }
    }
    VP8LDelete(dec);
  }

  if (status != VP8_STATUS_OK) {
    WebPFreeDecBuffer(params->output);
  }

#if WEBP_DECODER_ABI_VERSION > 0x0203
  if (params->options != NULL && params->options->flip) {
    status = WebPFlipBuffer(params->output);
  }
#endif
  return status;
}

static uint8_t* DecodeIntoRGBABuffer(WEBP_CSP_MODE colorspace,
                                     const uint8_t* const data,
                                     size_t data_size,
                                     uint8_t* const rgba,
                                     int stride, size_t size) {
  WebPDecParams params;
  WebPDecBuffer buf;
  if (rgba == NULL) {
    return NULL;
  }
  WebPInitDecBuffer(&buf);
  WebPResetDecParams(&params);
  params.output = &buf;
  buf.colorspace    = colorspace;
  buf.u.RGBA.rgba   = rgba;
  buf.u.RGBA.stride = stride;
  buf.u.RGBA.size   = size;
  buf.is_external_memory = 1;
  if (DecodeInto(data, data_size, &params) != VP8_STATUS_OK) {
    return NULL;
  }
  return rgba;
}

uint8_t* WebPDecodeRGBInto(const uint8_t* data, size_t data_size,
                           uint8_t* output, size_t size, int stride) {
  return DecodeIntoRGBABuffer(MODE_RGB, data, data_size, output, stride, size);
}

uint8_t* WebPDecodeRGBAInto(const uint8_t* data, size_t data_size,
                            uint8_t* output, size_t size, int stride) {
  return DecodeIntoRGBABuffer(MODE_RGBA, data, data_size, output, stride, size);
}

uint8_t* WebPDecodeARGBInto(const uint8_t* data, size_t data_size,
                            uint8_t* output, size_t size, int stride) {
  return DecodeIntoRGBABuffer(MODE_ARGB, data, data_size, output, stride, size);
}

uint8_t* WebPDecodeBGRInto(const uint8_t* data, size_t data_size,
                           uint8_t* output, size_t size, int stride) {
  return DecodeIntoRGBABuffer(MODE_BGR, data, data_size, output, stride, size);
}

uint8_t* WebPDecodeBGRAInto(const uint8_t* data, size_t data_size,
                            uint8_t* output, size_t size, int stride) {
  return DecodeIntoRGBABuffer(MODE_BGRA, data, data_size, output, stride, size);
}

uint8_t* WebPDecodeYUVInto(const uint8_t* data, size_t data_size,
                           uint8_t* luma, size_t luma_size, int luma_stride,
                           uint8_t* u, size_t u_size, int u_stride,
                           uint8_t* v, size_t v_size, int v_stride) {
  WebPDecParams params;
  WebPDecBuffer output;
  if (luma == NULL) return NULL;
  WebPInitDecBuffer(&output);
  WebPResetDecParams(&params);
  params.output = &output;
  output.colorspace      = MODE_YUV;
  output.u.YUVA.y        = luma;
  output.u.YUVA.y_stride = luma_stride;
  output.u.YUVA.y_size   = luma_size;
  output.u.YUVA.u        = u;
  output.u.YUVA.u_stride = u_stride;
  output.u.YUVA.u_size   = u_size;
  output.u.YUVA.v        = v;
  output.u.YUVA.v_stride = v_stride;
  output.u.YUVA.v_size   = v_size;
  output.is_external_memory = 1;
  if (DecodeInto(data, data_size, &params) != VP8_STATUS_OK) {
    return NULL;
  }
  return luma;
}


static uint8_t* Decode(WEBP_CSP_MODE mode, const uint8_t* const data,
                       size_t data_size, int* const width, int* const height,
                       WebPDecBuffer* const keep_info) {
  WebPDecParams params;
  WebPDecBuffer output;

  WebPInitDecBuffer(&output);
  WebPResetDecParams(&params);
  params.output = &output;
  output.colorspace = mode;

  
  if (!WebPGetInfo(data, data_size, &output.width, &output.height)) {
    return NULL;
  }
  if (width != NULL) *width = output.width;
  if (height != NULL) *height = output.height;

  
  if (DecodeInto(data, data_size, &params) != VP8_STATUS_OK) {
    return NULL;
  }
  if (keep_info != NULL) {    
    WebPCopyDecBuffer(&output, keep_info);
  }
  
  return WebPIsRGBMode(mode) ? output.u.RGBA.rgba : output.u.YUVA.y;
}

uint8_t* WebPDecodeRGB(const uint8_t* data, size_t data_size,
                       int* width, int* height) {
  return Decode(MODE_RGB, data, data_size, width, height, NULL);
}

uint8_t* WebPDecodeRGBA(const uint8_t* data, size_t data_size,
                        int* width, int* height) {
  return Decode(MODE_RGBA, data, data_size, width, height, NULL);
}

uint8_t* WebPDecodeARGB(const uint8_t* data, size_t data_size,
                        int* width, int* height) {
  return Decode(MODE_ARGB, data, data_size, width, height, NULL);
}

uint8_t* WebPDecodeBGR(const uint8_t* data, size_t data_size,
                       int* width, int* height) {
  return Decode(MODE_BGR, data, data_size, width, height, NULL);
}

uint8_t* WebPDecodeBGRA(const uint8_t* data, size_t data_size,
                        int* width, int* height) {
  return Decode(MODE_BGRA, data, data_size, width, height, NULL);
}

uint8_t* WebPDecodeYUV(const uint8_t* data, size_t data_size,
                       int* width, int* height, uint8_t** u, uint8_t** v,
                       int* stride, int* uv_stride) {
  WebPDecBuffer output;   
  uint8_t* const out = Decode(MODE_YUV, data, data_size,
                              width, height, &output);

  if (out != NULL) {
    const WebPYUVABuffer* const buf = &output.u.YUVA;
    *u = buf->u;
    *v = buf->v;
    *stride = buf->y_stride;
    *uv_stride = buf->u_stride;
    assert(buf->u_stride == buf->v_stride);
  }
  return out;
}

static void DefaultFeatures(WebPBitstreamFeatures* const features) {
  assert(features != NULL);
  memset(features, 0, sizeof(*features));
}

static VP8StatusCode GetFeatures(const uint8_t* const data, size_t data_size,
                                 WebPBitstreamFeatures* const features) {
  if (features == NULL || data == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }
  DefaultFeatures(features);

  
  return ParseHeadersInternal(data, data_size,
                              &features->width, &features->height,
                              &features->has_alpha, &features->has_animation,
                              &features->format, NULL);
}


int WebPGetInfo(const uint8_t* data, size_t data_size,
                int* width, int* height) {
  WebPBitstreamFeatures features;

  if (GetFeatures(data, data_size, &features) != VP8_STATUS_OK) {
    return 0;
  }

  if (width != NULL) {
    *width  = features.width;
  }
  if (height != NULL) {
    *height = features.height;
  }

  return 1;
}


int WebPInitDecoderConfigInternal(WebPDecoderConfig* config,
                                  int version) {
  if (WEBP_ABI_IS_INCOMPATIBLE(version, WEBP_DECODER_ABI_VERSION)) {
    return 0;   
  }
  if (config == NULL) {
    return 0;
  }
  memset(config, 0, sizeof(*config));
  DefaultFeatures(&config->input);
  WebPInitDecBuffer(&config->output);
  return 1;
}

VP8StatusCode WebPGetFeaturesInternal(const uint8_t* data, size_t data_size,
                                      WebPBitstreamFeatures* features,
                                      int version) {
  if (WEBP_ABI_IS_INCOMPATIBLE(version, WEBP_DECODER_ABI_VERSION)) {
    return VP8_STATUS_INVALID_PARAM;   
  }
  if (features == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }
  return GetFeatures(data, data_size, features);
}

VP8StatusCode WebPDecode(const uint8_t* data, size_t data_size,
                         WebPDecoderConfig* config) {
  WebPDecParams params;
  VP8StatusCode status;

  if (config == NULL) {
    return VP8_STATUS_INVALID_PARAM;
  }

  status = GetFeatures(data, data_size, &config->input);
  if (status != VP8_STATUS_OK) {
    if (status == VP8_STATUS_NOT_ENOUGH_DATA) {
      return VP8_STATUS_BITSTREAM_ERROR;  
    }
    return status;
  }

  WebPResetDecParams(&params);
  params.output = &config->output;
  params.options = &config->options;
  status = DecodeInto(data, data_size, &params);

  return status;
}


int WebPIoInitFromOptions(const WebPDecoderOptions* const options,
                          VP8Io* const io, WEBP_CSP_MODE src_colorspace) {
  const int W = io->width;
  const int H = io->height;
  int x = 0, y = 0, w = W, h = H;

  
  io->use_cropping = (options != NULL) && (options->use_cropping > 0);
  if (io->use_cropping) {
    w = options->crop_width;
    h = options->crop_height;
    x = options->crop_left;
    y = options->crop_top;
    if (!WebPIsRGBMode(src_colorspace)) {   
      x &= ~1;
      y &= ~1;
    }
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > W || y + h > H) {
      return 0;  
    }
  }
  io->crop_left   = x;
  io->crop_top    = y;
  io->crop_right  = x + w;
  io->crop_bottom = y + h;
  io->mb_w = w;
  io->mb_h = h;

  
  io->use_scaling = (options != NULL) && (options->use_scaling > 0);
  if (io->use_scaling) {
    if (options->scaled_width <= 0 || options->scaled_height <= 0) {
      return 0;
    }
    io->scaled_width = options->scaled_width;
    io->scaled_height = options->scaled_height;
  }

  
  io->bypass_filtering = options && options->bypass_filtering;

  
#ifdef FANCY_UPSAMPLING
  io->fancy_upsampling = (options == NULL) || (!options->no_fancy_upsampling);
#endif

  if (io->use_scaling) {
    
    io->bypass_filtering = (io->scaled_width < W * 3 / 4) &&
                           (io->scaled_height < H * 3 / 4);
    io->fancy_upsampling = 0;
  }
  return 1;
}

