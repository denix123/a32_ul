// Copyright 2010 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_DSP_YUV_H_
#define WEBP_DSP_YUV_H_

#include "./dsp.h"
#include "../dec/decode_vp8.h"


#if defined(WEBP_EXPERIMENTAL_FEATURES)
#endif


#ifdef __cplusplus
extern "C" {
#endif

enum {
  YUV_FIX = 16,                    
  YUV_HALF = 1 << (YUV_FIX - 1),
  YUV_MASK = (256 << YUV_FIX) - 1,
  YUV_RANGE_MIN = -227,            
  YUV_RANGE_MAX = 256 + 226,       

  YUV_FIX2 = 14,                   
  YUV_HALF2 = 1 << (YUV_FIX2 - 1),
  YUV_MASK2 = (256 << YUV_FIX2) - 1
};

#define kYScale 19077    
#define kVToR   26149    
#define kUToG   6419     
#define kVToG   13320    
#define kUToB   33050    
#define kRCst (-kYScale * 16 - kVToR * 128 + YUV_HALF2)
#define kGCst (-kYScale * 16 + kUToG * 128 + kVToG * 128 + YUV_HALF2)
#define kBCst (-kYScale * 16 - kUToB * 128 + YUV_HALF2)


#if !defined(WEBP_YUV_USE_TABLE)


static WEBP_INLINE int VP8Clip8(int v) {
  return ((v & ~YUV_MASK2) == 0) ? (v >> YUV_FIX2) : (v < 0) ? 0 : 255;
}

static WEBP_INLINE int VP8YUVToR(int y, int v) {
  return VP8Clip8(kYScale * y + kVToR * v + kRCst);
}

static WEBP_INLINE int VP8YUVToG(int y, int u, int v) {
  return VP8Clip8(kYScale * y - kUToG * u - kVToG * v + kGCst);
}

static WEBP_INLINE int VP8YUVToB(int y, int u) {
  return VP8Clip8(kYScale * y + kUToB * u + kBCst);
}

static WEBP_INLINE void VP8YuvToRgb(int y, int u, int v,
                                    uint8_t* const rgb) {
  rgb[0] = VP8YUVToR(y, v);
  rgb[1] = VP8YUVToG(y, u, v);
  rgb[2] = VP8YUVToB(y, u);
}

static WEBP_INLINE void VP8YuvToBgr(int y, int u, int v,
                                    uint8_t* const bgr) {
  bgr[0] = VP8YUVToB(y, u);
  bgr[1] = VP8YUVToG(y, u, v);
  bgr[2] = VP8YUVToR(y, v);
}

static WEBP_INLINE void VP8YuvToRgb565(int y, int u, int v,
                                       uint8_t* const rgb) {
  const int r = VP8YUVToR(y, v);      
  const int g = VP8YUVToG(y, u, v);   
  const int b = VP8YUVToB(y, u);      
  const int rg = (r & 0xf8) | (g >> 5);
  const int gb = ((g << 3) & 0xe0) | (b >> 3);
#ifdef WEBP_SWAP_16BIT_CSP
  rgb[0] = gb;
  rgb[1] = rg;
#else
  rgb[0] = rg;
  rgb[1] = gb;
#endif
}

static WEBP_INLINE void VP8YuvToRgba4444(int y, int u, int v,
                                         uint8_t* const argb) {
  const int r = VP8YUVToR(y, v);        
  const int g = VP8YUVToG(y, u, v);     
  const int b = VP8YUVToB(y, u);        
  const int rg = (r & 0xf0) | (g >> 4);
  const int ba = (b & 0xf0) | 0x0f;     
#ifdef WEBP_SWAP_16BIT_CSP
  argb[0] = ba;
  argb[1] = rg;
#else
  argb[0] = rg;
  argb[1] = ba;
#endif
}

#else


extern int16_t VP8kVToR[256], VP8kUToB[256];
extern int32_t VP8kVToG[256], VP8kUToG[256];
extern uint8_t VP8kClip[YUV_RANGE_MAX - YUV_RANGE_MIN];
extern uint8_t VP8kClip4Bits[YUV_RANGE_MAX - YUV_RANGE_MIN];

static WEBP_INLINE void VP8YuvToRgb(int y, int u, int v,
                                    uint8_t* const rgb) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  rgb[0] = VP8kClip[y + r_off - YUV_RANGE_MIN];
  rgb[1] = VP8kClip[y + g_off - YUV_RANGE_MIN];
  rgb[2] = VP8kClip[y + b_off - YUV_RANGE_MIN];
}

static WEBP_INLINE void VP8YuvToBgr(int y, int u, int v,
                                    uint8_t* const bgr) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  bgr[0] = VP8kClip[y + b_off - YUV_RANGE_MIN];
  bgr[1] = VP8kClip[y + g_off - YUV_RANGE_MIN];
  bgr[2] = VP8kClip[y + r_off - YUV_RANGE_MIN];
}

static WEBP_INLINE void VP8YuvToRgb565(int y, int u, int v,
                                       uint8_t* const rgb) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  const int rg = ((VP8kClip[y + r_off - YUV_RANGE_MIN] & 0xf8) |
                  (VP8kClip[y + g_off - YUV_RANGE_MIN] >> 5));
  const int gb = (((VP8kClip[y + g_off - YUV_RANGE_MIN] << 3) & 0xe0) |
                   (VP8kClip[y + b_off - YUV_RANGE_MIN] >> 3));
#ifdef WEBP_SWAP_16BIT_CSP
  rgb[0] = gb;
  rgb[1] = rg;
#else
  rgb[0] = rg;
  rgb[1] = gb;
#endif
}

static WEBP_INLINE void VP8YuvToRgba4444(int y, int u, int v,
                                         uint8_t* const argb) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  const int rg = ((VP8kClip4Bits[y + r_off - YUV_RANGE_MIN] << 4) |
                   VP8kClip4Bits[y + g_off - YUV_RANGE_MIN]);
  const int ba = (VP8kClip4Bits[y + b_off - YUV_RANGE_MIN] << 4) | 0x0f;
#ifdef WEBP_SWAP_16BIT_CSP
  argb[0] = ba;
  argb[1] = rg;
#else
  argb[0] = rg;
  argb[1] = ba;
#endif
}

#endif  


static WEBP_INLINE void VP8YuvToArgb(uint8_t y, uint8_t u, uint8_t v,
                                     uint8_t* const argb) {
  argb[0] = 0xff;
  VP8YuvToRgb(y, u, v, argb + 1);
}

static WEBP_INLINE void VP8YuvToBgra(uint8_t y, uint8_t u, uint8_t v,
                                     uint8_t* const bgra) {
  VP8YuvToBgr(y, u, v, bgra);
  bgra[3] = 0xff;
}

static WEBP_INLINE void VP8YuvToRgba(uint8_t y, uint8_t u, uint8_t v,
                                     uint8_t* const rgba) {
  VP8YuvToRgb(y, u, v, rgba);
  rgba[3] = 0xff;
}

void VP8YUVInit(void);


#if defined(WEBP_USE_SSE2)

#define WEBP_YUV_USE_SSE2_TABLES

#if defined(FANCY_UPSAMPLING)
void VP8YuvToRgba32(const uint8_t* y, const uint8_t* u, const uint8_t* v,
                    uint8_t* dst);
void VP8YuvToRgb32(const uint8_t* y, const uint8_t* u, const uint8_t* v,
                   uint8_t* dst);
void VP8YuvToBgra32(const uint8_t* y, const uint8_t* u, const uint8_t* v,
                    uint8_t* dst);
void VP8YuvToBgr32(const uint8_t* y, const uint8_t* u, const uint8_t* v,
                   uint8_t* dst);
#endif  

void VP8YUVInitSSE2(void);

#endif    


static WEBP_INLINE int VP8ClipUV(int uv, int rounding) {
  uv = (uv + rounding + (128 << (YUV_FIX + 2))) >> (YUV_FIX + 2);
  return ((uv & ~0xff) == 0) ? uv : (uv < 0) ? 0 : 255;
}

#ifndef USE_YUVj

static WEBP_INLINE int VP8RGBToY(int r, int g, int b, int rounding) {
  const int luma = 16839 * r + 33059 * g + 6420 * b;
  return (luma + rounding + (16 << YUV_FIX)) >> YUV_FIX;  
}

static WEBP_INLINE int VP8RGBToU(int r, int g, int b, int rounding) {
  const int u = -9719 * r - 19081 * g + 28800 * b;
  return VP8ClipUV(u, rounding);
}

static WEBP_INLINE int VP8RGBToV(int r, int g, int b, int rounding) {
  const int v = +28800 * r - 24116 * g - 4684 * b;
  return VP8ClipUV(v, rounding);
}

#else

static WEBP_INLINE int VP8RGBToY(int r, int g, int b, int rounding) {
  const int luma = 19595 * r + 38470 * g + 7471 * b;
  return (luma + rounding) >> YUV_FIX;  
}

static WEBP_INLINE int VP8RGBToU(int r, int g, int b, int rounding) {
  const int u = -11058 * r - 21710 * g + 32768 * b;
  return VP8ClipUV(u, rounding);
}

static WEBP_INLINE int VP8RGBToV(int r, int g, int b, int rounding) {
  const int v = 32768 * r - 27439 * g - 5329 * b;
  return VP8ClipUV(v, rounding);
}

#endif    

#ifdef __cplusplus
}    
#endif

#endif  
