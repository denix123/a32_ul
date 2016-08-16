// Copyright 2013 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_RANDOM_H_
#define WEBP_UTILS_RANDOM_H_

#include <assert.h>
#include "../webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VP8_RANDOM_DITHER_FIX 8   
#define VP8_RANDOM_TABLE_SIZE 55

typedef struct {
  int index1_, index2_;
  uint32_t tab_[VP8_RANDOM_TABLE_SIZE];
  int amp_;
} VP8Random;

void VP8InitRandom(VP8Random* const rg, float dithering);

static WEBP_INLINE int VP8RandomBits2(VP8Random* const rg, int num_bits,
                                      int amp) {
  int diff;
  assert(num_bits + VP8_RANDOM_DITHER_FIX <= 31);
  diff = rg->tab_[rg->index1_] - rg->tab_[rg->index2_];
  if (diff < 0) diff += (1u << 31);
  rg->tab_[rg->index1_] = diff;
  if (++rg->index1_ == VP8_RANDOM_TABLE_SIZE) rg->index1_ = 0;
  if (++rg->index2_ == VP8_RANDOM_TABLE_SIZE) rg->index2_ = 0;
  
  diff = (int)((uint32_t)diff << 1) >> (32 - num_bits);
  diff = (diff * amp) >> VP8_RANDOM_DITHER_FIX;  
  diff += 1 << (num_bits - 1);                   
  return diff;
}

static WEBP_INLINE int VP8RandomBits(VP8Random* const rg, int num_bits) {
  return VP8RandomBits2(rg, num_bits, rg->amp_);
}

#ifdef __cplusplus
}    
#endif

#endif  