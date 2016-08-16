// Copyright 2012 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_WEBP_MUX_TYPES_H_
#define WEBP_WEBP_MUX_TYPES_H_

#include <stdlib.h>  
#include <string.h>  
#include "./types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WebPData WebPData;

typedef enum WebPFeatureFlags {
  FRAGMENTS_FLAG  = 0x00000001,
  ANIMATION_FLAG  = 0x00000002,
  XMP_FLAG        = 0x00000004,
  EXIF_FLAG       = 0x00000008,
  ALPHA_FLAG      = 0x00000010,
  ICCP_FLAG       = 0x00000020
} WebPFeatureFlags;

typedef enum WebPMuxAnimDispose {
  WEBP_MUX_DISPOSE_NONE,       
  WEBP_MUX_DISPOSE_BACKGROUND  
} WebPMuxAnimDispose;

typedef enum WebPMuxAnimBlend {
  WEBP_MUX_BLEND,              
  WEBP_MUX_NO_BLEND            
} WebPMuxAnimBlend;

struct WebPData {
  const uint8_t* bytes;
  size_t size;
};

static WEBP_INLINE void WebPDataInit(WebPData* webp_data) {
  if (webp_data != NULL) {
    memset(webp_data, 0, sizeof(*webp_data));
  }
}

static WEBP_INLINE void WebPDataClear(WebPData* webp_data) {
  if (webp_data != NULL) {
    free((void*)webp_data->bytes);
    WebPDataInit(webp_data);
  }
}

static WEBP_INLINE int WebPDataCopy(const WebPData* src, WebPData* dst) {
  if (src == NULL || dst == NULL) return 0;
  WebPDataInit(dst);
  if (src->bytes != NULL && src->size != 0) {
    dst->bytes = (uint8_t*)malloc(src->size);
    if (dst->bytes == NULL) return 0;
    memcpy((void*)dst->bytes, src->bytes, src->size);
    dst->size = src->size;
  }
  return 1;
}

#ifdef __cplusplus
}    
#endif

#endif  