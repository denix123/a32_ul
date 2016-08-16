// Copyright 2013 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_DEC_ALPHAI_H_
#define WEBP_DEC_ALPHAI_H_

#include "./webpi.h"
#include "../utils/filters.h"

#ifdef __cplusplus
extern "C" {
#endif

struct VP8LDecoder;  

typedef struct ALPHDecoder ALPHDecoder;
struct ALPHDecoder {
  int width_;
  int height_;
  int method_;
  WEBP_FILTER_TYPE filter_;
  int pre_processing_;
  struct VP8LDecoder* vp8l_dec_;
  VP8Io io_;
  int use_8b_decode;  
                      
                      
};


ALPHDecoder* ALPHNew(void);

void ALPHDelete(ALPHDecoder* const dec);


#ifdef __cplusplus
}    
#endif

#endif  
