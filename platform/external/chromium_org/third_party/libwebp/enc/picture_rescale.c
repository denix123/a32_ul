// Copyright 2014 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#include <assert.h>
#include <stdlib.h>

#include "./vp8enci.h"
#include "../utils/rescaler.h"
#include "../utils/utils.h"

#define HALVE(x) (((x) + 1) >> 1)

static void PictureGrabSpecs(const WebPPicture* const src,
                             WebPPicture* const dst) {
  assert(src != NULL && dst != NULL);
  *dst = *src;
  WebPPictureResetBuffers(dst);
}


static void CopyPlane(const uint8_t* src, int src_stride,
                      uint8_t* dst, int dst_stride, int width, int height) {
  while (height-- > 0) {
    memcpy(dst, src, width);
    src += src_stride;
    dst += dst_stride;
  }
}

static void SnapTopLeftPosition(const WebPPicture* const pic,
                                int* const left, int* const top) {
  if (!pic->use_argb) {
    *left &= ~1;
    *top &= ~1;
  }
}

static int AdjustAndCheckRectangle(const WebPPicture* const pic,
                                   int* const left, int* const top,
                                   int width, int height) {
  SnapTopLeftPosition(pic, left, top);
  if ((*left) < 0 || (*top) < 0) return 0;
  if (width <= 0 || height <= 0) return 0;
  if ((*left) + width > pic->width) return 0;
  if ((*top) + height > pic->height) return 0;
  return 1;
}

int WebPPictureCopy(const WebPPicture* src, WebPPicture* dst) {
  if (src == NULL || dst == NULL) return 0;
  if (src == dst) return 1;

  PictureGrabSpecs(src, dst);
  if (!WebPPictureAlloc(dst)) return 0;

  if (!src->use_argb) {
    CopyPlane(src->y, src->y_stride,
              dst->y, dst->y_stride, dst->width, dst->height);
    CopyPlane(src->u, src->uv_stride,
              dst->u, dst->uv_stride, HALVE(dst->width), HALVE(dst->height));
    CopyPlane(src->v, src->uv_stride,
              dst->v, dst->uv_stride, HALVE(dst->width), HALVE(dst->height));
    if (dst->a != NULL)  {
      CopyPlane(src->a, src->a_stride,
                dst->a, dst->a_stride, dst->width, dst->height);
    }
  } else {
    CopyPlane((const uint8_t*)src->argb, 4 * src->argb_stride,
              (uint8_t*)dst->argb, 4 * dst->argb_stride,
              4 * dst->width, dst->height);
  }
  return 1;
}

int WebPPictureIsView(const WebPPicture* picture) {
  if (picture == NULL) return 0;
  if (picture->use_argb) {
    return (picture->memory_argb_ == NULL);
  }
  return (picture->memory_ == NULL);
}

int WebPPictureView(const WebPPicture* src,
                    int left, int top, int width, int height,
                    WebPPicture* dst) {
  if (src == NULL || dst == NULL) return 0;

  
  if (!AdjustAndCheckRectangle(src, &left, &top, width, height)) return 0;

  if (src != dst) {  
    PictureGrabSpecs(src, dst);
  }
  dst->width = width;
  dst->height = height;
  if (!src->use_argb) {
    dst->y = src->y + top * src->y_stride + left;
    dst->u = src->u + (top >> 1) * src->uv_stride + (left >> 1);
    dst->v = src->v + (top >> 1) * src->uv_stride + (left >> 1);
    dst->y_stride = src->y_stride;
    dst->uv_stride = src->uv_stride;
    if (src->a != NULL) {
      dst->a = src->a + top * src->a_stride + left;
      dst->a_stride = src->a_stride;
    }
  } else {
    dst->argb = src->argb + top * src->argb_stride + left;
    dst->argb_stride = src->argb_stride;
  }
  return 1;
}


int WebPPictureCrop(WebPPicture* pic,
                    int left, int top, int width, int height) {
  WebPPicture tmp;

  if (pic == NULL) return 0;
  if (!AdjustAndCheckRectangle(pic, &left, &top, width, height)) return 0;

  PictureGrabSpecs(pic, &tmp);
  tmp.width = width;
  tmp.height = height;
  if (!WebPPictureAlloc(&tmp)) return 0;

  if (!pic->use_argb) {
    const int y_offset = top * pic->y_stride + left;
    const int uv_offset = (top / 2) * pic->uv_stride + left / 2;
    CopyPlane(pic->y + y_offset, pic->y_stride,
              tmp.y, tmp.y_stride, width, height);
    CopyPlane(pic->u + uv_offset, pic->uv_stride,
              tmp.u, tmp.uv_stride, HALVE(width), HALVE(height));
    CopyPlane(pic->v + uv_offset, pic->uv_stride,
              tmp.v, tmp.uv_stride, HALVE(width), HALVE(height));

    if (tmp.a != NULL) {
      const int a_offset = top * pic->a_stride + left;
      CopyPlane(pic->a + a_offset, pic->a_stride,
                tmp.a, tmp.a_stride, width, height);
    }
  } else {
    const uint8_t* const src =
        (const uint8_t*)(pic->argb + top * pic->argb_stride + left);
    CopyPlane(src, pic->argb_stride * 4,
              (uint8_t*)tmp.argb, tmp.argb_stride * 4,
              width * 4, height);
  }
  WebPPictureFree(pic);
  *pic = tmp;
  return 1;
}


static void RescalePlane(const uint8_t* src,
                         int src_width, int src_height, int src_stride,
                         uint8_t* dst,
                         int dst_width, int dst_height, int dst_stride,
                         int32_t* const work,
                         int num_channels) {
  WebPRescaler rescaler;
  int y = 0;
  WebPRescalerInit(&rescaler, src_width, src_height,
                   dst, dst_width, dst_height, dst_stride,
                   num_channels,
                   src_width, dst_width,
                   src_height, dst_height,
                   work);
  memset(work, 0, 2 * dst_width * num_channels * sizeof(*work));
  while (y < src_height) {
    y += WebPRescalerImport(&rescaler, src_height - y,
                            src + y * src_stride, src_stride);
    WebPRescalerExport(&rescaler);
  }
}

static void AlphaMultiplyARGB(WebPPicture* const pic, int inverse) {
  assert(pic->argb != NULL);
  WebPMultARGBRows((uint8_t*)pic->argb, pic->argb_stride * sizeof(*pic->argb),
                   pic->width, pic->height, inverse);
}

static void AlphaMultiplyY(WebPPicture* const pic, int inverse) {
  if (pic->a != NULL) {
    WebPMultRows(pic->y, pic->y_stride, pic->a, pic->a_stride,
                 pic->width, pic->height, inverse);
  }
}

int WebPPictureRescale(WebPPicture* pic, int width, int height) {
  WebPPicture tmp;
  int prev_width, prev_height;
  int32_t* work;

  if (pic == NULL) return 0;
  prev_width = pic->width;
  prev_height = pic->height;
  
  if (width == 0) {
    width = (prev_width * height + prev_height / 2) / prev_height;
  }
  
  if (height == 0) {
    height = (prev_height * width + prev_width / 2) / prev_width;
  }
  
  if (width <= 0 || height <= 0) return 0;

  PictureGrabSpecs(pic, &tmp);
  tmp.width = width;
  tmp.height = height;
  if (!WebPPictureAlloc(&tmp)) return 0;

  if (!pic->use_argb) {
    work = (int32_t*)WebPSafeMalloc(2ULL * width, sizeof(*work));
    if (work == NULL) {
      WebPPictureFree(&tmp);
      return 0;
    }
    
    if (pic->a != NULL) {
      WebPInitAlphaProcessing();
      RescalePlane(pic->a, prev_width, prev_height, pic->a_stride,
                   tmp.a, width, height, tmp.a_stride, work, 1);
    }

    
    
    AlphaMultiplyY(pic, 0);
    RescalePlane(pic->y, prev_width, prev_height, pic->y_stride,
                 tmp.y, width, height, tmp.y_stride, work, 1);
    AlphaMultiplyY(&tmp, 1);

    RescalePlane(pic->u,
                 HALVE(prev_width), HALVE(prev_height), pic->uv_stride,
                 tmp.u,
                 HALVE(width), HALVE(height), tmp.uv_stride, work, 1);
    RescalePlane(pic->v,
                 HALVE(prev_width), HALVE(prev_height), pic->uv_stride,
                 tmp.v,
                 HALVE(width), HALVE(height), tmp.uv_stride, work, 1);
  } else {
    work = (int32_t*)WebPSafeMalloc(2ULL * width * 4, sizeof(*work));
    if (work == NULL) {
      WebPPictureFree(&tmp);
      return 0;
    }
    
    
    
    WebPInitAlphaProcessing();
    AlphaMultiplyARGB(pic, 0);
    RescalePlane((const uint8_t*)pic->argb, prev_width, prev_height,
                 pic->argb_stride * 4,
                 (uint8_t*)tmp.argb, width, height,
                 tmp.argb_stride * 4,
                 work, 4);
    AlphaMultiplyARGB(&tmp, 1);
  }
  WebPPictureFree(pic);
  WebPSafeFree(work);
  *pic = tmp;
  return 1;
}
