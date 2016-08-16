// Copyright 2010 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_BIT_READER_H_
#define WEBP_UTILS_BIT_READER_H_

#include <assert.h>
#ifdef _MSC_VER
#include <stdlib.h>  
#endif
#include "../webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(__i386__) || defined(_M_IX86)      
#define BITS 24
#elif defined(__x86_64__) || defined(_M_X64)   
#define BITS 56
#elif defined(__arm__) || defined(_M_ARM)      
#define BITS 24
#elif defined(__mips__)                        
#define BITS 24
#else                                          
#define BITS 24  
#endif


#if (BITS > 24)
typedef uint64_t bit_t;
#else
typedef uint32_t bit_t;
#endif

typedef uint32_t range_t;


typedef struct VP8BitReader VP8BitReader;
struct VP8BitReader {
  
  bit_t value_;               
  range_t range_;             
  int bits_;                  
  
  const uint8_t* buf_;        
  const uint8_t* buf_end_;    
  int eof_;                   
};

void VP8InitBitReader(VP8BitReader* const br,
                      const uint8_t* const start, const uint8_t* const end);

void VP8RemapBitReader(VP8BitReader* const br, ptrdiff_t offset);

uint32_t VP8GetValue(VP8BitReader* const br, int num_bits);
static WEBP_INLINE uint32_t VP8Get(VP8BitReader* const br) {
  return VP8GetValue(br, 1);
}

int32_t VP8GetSignedValue(VP8BitReader* const br, int num_bits);



#define VP8L_MAX_NUM_BIT_READ 24

typedef uint64_t vp8l_val_t;  

typedef struct {
  vp8l_val_t     val_;        
  const uint8_t* buf_;        
  size_t         len_;        
  size_t         pos_;        
  int            bit_pos_;    
  int            eos_;        
  int            error_;      
} VP8LBitReader;

void VP8LInitBitReader(VP8LBitReader* const br,
                       const uint8_t* const start,
                       size_t length);

void VP8LBitReaderSetBuffer(VP8LBitReader* const br,
                            const uint8_t* const buffer, size_t length);

uint32_t VP8LReadBits(VP8LBitReader* const br, int n_bits);

static WEBP_INLINE uint32_t VP8LPrefetchBits(VP8LBitReader* const br) {
  return (uint32_t)(br->val_ >> br->bit_pos_);
}

static WEBP_INLINE void VP8LSetBitPos(VP8LBitReader* const br, int val) {
  br->bit_pos_ = val;
}

void VP8LFillBitWindow(VP8LBitReader* const br);

#ifdef __cplusplus
}    
#endif

#endif  
