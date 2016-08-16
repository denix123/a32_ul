// Copyright 2013 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_QUANT_LEVELS_DEC_H_
#define WEBP_UTILS_QUANT_LEVELS_DEC_H_

#include "../webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif

int WebPDequantizeLevels(uint8_t* const data, int width, int height,
                         int strength);

#ifdef __cplusplus
}    
#endif

#endif  
