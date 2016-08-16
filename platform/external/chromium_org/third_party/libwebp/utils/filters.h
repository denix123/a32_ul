// Copyright 2011 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_FILTERS_H_
#define WEBP_UTILS_FILTERS_H_

#include "../webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  WEBP_FILTER_NONE = 0,
  WEBP_FILTER_HORIZONTAL,
  WEBP_FILTER_VERTICAL,
  WEBP_FILTER_GRADIENT,
  WEBP_FILTER_LAST = WEBP_FILTER_GRADIENT + 1,  
  WEBP_FILTER_BEST,
  WEBP_FILTER_FAST
} WEBP_FILTER_TYPE;

typedef void (*WebPFilterFunc)(const uint8_t* in, int width, int height,
                               int stride, uint8_t* out);
typedef void (*WebPUnfilterFunc)(int width, int height, int stride,
                                 int row, int num_rows, uint8_t* data);

extern const WebPFilterFunc WebPFilters[WEBP_FILTER_LAST];

extern const WebPUnfilterFunc WebPUnfilters[WEBP_FILTER_LAST];

WEBP_FILTER_TYPE EstimateBestFilter(const uint8_t* data,
                                    int width, int height, int stride);

#ifdef __cplusplus
}    
#endif

#endif  
