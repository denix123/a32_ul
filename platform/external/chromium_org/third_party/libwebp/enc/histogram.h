// Copyright 2012 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_ENC_HISTOGRAM_H_
#define WEBP_ENC_HISTOGRAM_H_

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./backward_references.h"
#include "../webp/format_constants.h"
#include "../webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  
  
  uint32_t* literal_;         
  uint32_t red_[NUM_LITERAL_CODES];
  uint32_t blue_[NUM_LITERAL_CODES];
  uint32_t alpha_[NUM_LITERAL_CODES];
  
  uint32_t distance_[NUM_DISTANCE_CODES];
  int palette_code_bits_;
  double bit_cost_;      
  double literal_cost_;  
  double red_cost_;      
  double blue_cost_;
} VP8LHistogram;

typedef struct {
  int size;         
  int max_size;     
  VP8LHistogram** histograms;
} VP8LHistogramSet;

void VP8LHistogramCreate(VP8LHistogram* const p,
                         const VP8LBackwardRefs* const refs,
                         int palette_code_bits);

int VP8LGetHistogramSize(int palette_code_bits);

void VP8LHistogramInit(VP8LHistogram* const p, int palette_code_bits);

void VP8LHistogramStoreRefs(const VP8LBackwardRefs* const refs,
                            VP8LHistogram* const histo);

void VP8LFreeHistogram(VP8LHistogram* const histo);

void VP8LFreeHistogramSet(VP8LHistogramSet* const histo);

VP8LHistogramSet* VP8LAllocateHistogramSet(int size, int cache_bits);

VP8LHistogram* VP8LAllocateHistogram(int cache_bits);

void VP8LHistogramAddSinglePixOrCopy(VP8LHistogram* const histo,
                                     const PixOrCopy* const v);

double VP8LHistogramEstimateBits(const VP8LHistogram* const p);

double VP8LHistogramEstimateBitsBulk(const VP8LHistogram* const p);

static WEBP_INLINE int VP8LHistogramNumCodes(int palette_code_bits) {
  return NUM_LITERAL_CODES + NUM_LENGTH_CODES +
      ((palette_code_bits > 0) ? (1 << palette_code_bits) : 0);
}

int VP8LGetHistoImageSymbols(int xsize, int ysize,
                             const VP8LBackwardRefs* const refs,
                             int quality, int histogram_bits, int cache_bits,
                             VP8LHistogramSet* const image_in,
                             uint16_t* const histogram_symbols);

#ifdef __cplusplus
}
#endif

#endif  
