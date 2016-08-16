// Copyright 2012 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_RESCALER_H_
#define WEBP_UTILS_RESCALER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../webp/types.h"

typedef struct {
  int x_expand;               
  int num_channels;           
  int fy_scale, fx_scale;     
  int64_t fxy_scale;          
  
  int y_accum;                
  int y_add, y_sub;           
  int x_add, x_sub;           
  int src_width, src_height;  
  int dst_width, dst_height;  
  uint8_t* dst;
  int dst_stride;
  int32_t* irow, *frow;       
} WebPRescaler;

void WebPRescalerInit(WebPRescaler* const rescaler,
                      int src_width, int src_height,
                      uint8_t* const dst,
                      int dst_width, int dst_height, int dst_stride,
                      int num_channels,
                      int x_add, int x_sub,
                      int y_add, int y_sub,
                      int32_t* const work);

int WebPRescaleNeededLines(const WebPRescaler* const rescaler,
                           int max_num_lines);

int WebPRescalerImport(WebPRescaler* const rescaler, int num_rows,
                       const uint8_t* src, int src_stride);

extern void (*WebPRescalerImportRow)(WebPRescaler* const wrk,
                                     const uint8_t* const src, int channel);
extern void (*WebPRescalerExportRow)(WebPRescaler* const wrk, int x_out);

static WEBP_INLINE
int WebPRescalerHasPendingOutput(const WebPRescaler* const rescaler) {
  return (rescaler->y_accum <= 0);
}

// Export as many rows as possible. Return the numbers of rows written.
int WebPRescalerExport(WebPRescaler* const rescaler);


#ifdef __cplusplus
}    
#endif

#endif  
