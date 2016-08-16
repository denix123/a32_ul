// Copyright 2012 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_DSP_LOSSLESS_H_
#define WEBP_DSP_LOSSLESS_H_

#include "../webp/types.h"
#include "../webp/decode.h"

#include "../enc/histogram.h"
#include "../utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef uint32_t (*VP8LPredictorFunc)(uint32_t left, const uint32_t* const top);
extern VP8LPredictorFunc VP8LPredictors[16];

typedef void (*VP8LProcessBlueAndRedFunc)(uint32_t* argb_data, int num_pixels);
extern VP8LProcessBlueAndRedFunc VP8LSubtractGreenFromBlueAndRed;
extern VP8LProcessBlueAndRedFunc VP8LAddGreenToBlueAndRed;

typedef struct {
  
  
  uint8_t green_to_red_;
  uint8_t green_to_blue_;
  uint8_t red_to_blue_;
} VP8LMultipliers;
typedef void (*VP8LTransformColorFunc)(const VP8LMultipliers* const m,
                                       uint32_t* argb_data, int num_pixels);
extern VP8LTransformColorFunc VP8LTransformColor;
extern VP8LTransformColorFunc VP8LTransformColorInverse;

typedef void (*VP8LConvertFunc)(const uint32_t* src, int num_pixels,
                                uint8_t* dst);
extern VP8LConvertFunc VP8LConvertBGRAToRGB;
extern VP8LConvertFunc VP8LConvertBGRAToRGBA;
extern VP8LConvertFunc VP8LConvertBGRAToRGBA4444;
extern VP8LConvertFunc VP8LConvertBGRAToRGB565;
extern VP8LConvertFunc VP8LConvertBGRAToBGR;

extern void VP8LTransformColor_C(const VP8LMultipliers* const m,
                                 uint32_t* data, int num_pixels);
extern void VP8LTransformColorInverse_C(const VP8LMultipliers* const m,
                                        uint32_t* data, int num_pixels);

extern void VP8LConvertBGRAToRGB_C(const uint32_t* src,
                                   int num_pixels, uint8_t* dst);
extern void VP8LConvertBGRAToRGBA_C(const uint32_t* src,
                                    int num_pixels, uint8_t* dst);
extern void VP8LConvertBGRAToRGBA4444_C(const uint32_t* src,
                                        int num_pixels, uint8_t* dst);
extern void VP8LConvertBGRAToRGB565_C(const uint32_t* src,
                                      int num_pixels, uint8_t* dst);
extern void VP8LConvertBGRAToBGR_C(const uint32_t* src,
                                   int num_pixels, uint8_t* dst);
extern void VP8LSubtractGreenFromBlueAndRed_C(uint32_t* argb_data,
                                              int num_pixels);
extern void VP8LAddGreenToBlueAndRed_C(uint32_t* data, int num_pixels);

void VP8LDspInit(void);


struct VP8LTransform;  

void VP8LInverseTransform(const struct VP8LTransform* const transform,
                          int row_start, int row_end,
                          const uint32_t* const in, uint32_t* const out);

void VP8LColorIndexInverseTransformAlpha(
    const struct VP8LTransform* const transform, int y_start, int y_end,
    const uint8_t* src, uint8_t* dst);

void VP8LResidualImage(int width, int height, int bits,
                       uint32_t* const argb, uint32_t* const argb_scratch,
                       uint32_t* const image);

void VP8LColorSpaceTransform(int width, int height, int bits, int quality,
                             uint32_t* const argb, uint32_t* image);


void VP8LConvertFromBGRA(const uint32_t* const in_data, int num_pixels,
                         WEBP_CSP_MODE out_colorspace, uint8_t* const rgba);


static WEBP_INLINE uint32_t VP8LSubSampleSize(uint32_t size,
                                              uint32_t sampling_bits) {
  return (size + (1 << sampling_bits) - 1) >> sampling_bits;
}

#define LOG_LOOKUP_IDX_MAX 256
extern const float kLog2Table[LOG_LOOKUP_IDX_MAX];
extern const float kSLog2Table[LOG_LOOKUP_IDX_MAX];
typedef float (*VP8LFastLog2SlowFunc)(uint32_t v);

extern VP8LFastLog2SlowFunc VP8LFastLog2Slow;
extern VP8LFastLog2SlowFunc VP8LFastSLog2Slow;

static WEBP_INLINE float VP8LFastLog2(uint32_t v) {
  return (v < LOG_LOOKUP_IDX_MAX) ? kLog2Table[v] : VP8LFastLog2Slow(v);
}
static WEBP_INLINE float VP8LFastSLog2(uint32_t v) {
  return (v < LOG_LOOKUP_IDX_MAX) ? kSLog2Table[v] : VP8LFastSLog2Slow(v);
}


typedef double (*VP8LCostFunc)(const uint32_t* population, int length);
typedef double (*VP8LCostCombinedFunc)(const uint32_t* X, const uint32_t* Y,
                                       int length);

extern VP8LCostFunc VP8LExtraCost;
extern VP8LCostCombinedFunc VP8LExtraCostCombined;

typedef struct {        
  int counts[2];        
  int streaks[2][2];    
} VP8LStreaks;

typedef VP8LStreaks (*VP8LCostCountFunc)(const uint32_t* population,
                                         int length);
typedef VP8LStreaks (*VP8LCostCombinedCountFunc)(const uint32_t* X,
                                                 const uint32_t* Y, int length);

extern VP8LCostCountFunc VP8LHuffmanCostCount;
extern VP8LCostCombinedCountFunc VP8LHuffmanCostCombinedCount;

typedef void (*VP8LHistogramAddFunc)(const VP8LHistogram* const a,
                                     const VP8LHistogram* const b,
                                     VP8LHistogram* const out);
extern VP8LHistogramAddFunc VP8LHistogramAdd;


static WEBP_INLINE int VP8LBitsLog2Ceiling(uint32_t n) {
  const int log_floor = BitsLog2Floor(n);
  if (n == (n & ~(n - 1)))  
    return log_floor;
  else
    return log_floor + 1;
}

static WEBP_INLINE void VP8LPrefixEncodeBitsNoLUT(int distance, int* const code,
                                                  int* const extra_bits) {
  const int highest_bit = BitsLog2Floor(--distance);
  const int second_highest_bit = (distance >> (highest_bit - 1)) & 1;
  *extra_bits = highest_bit - 1;
  *code = 2 * highest_bit + second_highest_bit;
}

static WEBP_INLINE void VP8LPrefixEncodeNoLUT(int distance, int* const code,
                                              int* const extra_bits,
                                              int* const extra_bits_value) {
  const int highest_bit = BitsLog2Floor(--distance);
  const int second_highest_bit = (distance >> (highest_bit - 1)) & 1;
  *extra_bits = highest_bit - 1;
  *extra_bits_value = distance & ((1 << *extra_bits) - 1);
  *code = 2 * highest_bit + second_highest_bit;
}

#define PREFIX_LOOKUP_IDX_MAX   512
typedef struct {
  int8_t code_;
  int8_t extra_bits_;
} VP8LPrefixCode;

extern const VP8LPrefixCode kPrefixEncodeCode[PREFIX_LOOKUP_IDX_MAX];
extern const uint8_t kPrefixEncodeExtraBitsValue[PREFIX_LOOKUP_IDX_MAX];
static WEBP_INLINE void VP8LPrefixEncodeBits(int distance, int* const code,
                                             int* const extra_bits) {
  if (distance < PREFIX_LOOKUP_IDX_MAX) {
    const VP8LPrefixCode prefix_code = kPrefixEncodeCode[distance];
    *code = prefix_code.code_;
    *extra_bits = prefix_code.extra_bits_;
  } else {
    VP8LPrefixEncodeBitsNoLUT(distance, code, extra_bits);
  }
}

static WEBP_INLINE void VP8LPrefixEncode(int distance, int* const code,
                                         int* const extra_bits,
                                         int* const extra_bits_value) {
  if (distance < PREFIX_LOOKUP_IDX_MAX) {
    const VP8LPrefixCode prefix_code = kPrefixEncodeCode[distance];
    *code = prefix_code.code_;
    *extra_bits = prefix_code.extra_bits_;
    *extra_bits_value = kPrefixEncodeExtraBitsValue[distance];
  } else {
    VP8LPrefixEncodeNoLUT(distance, code, extra_bits, extra_bits_value);
  }
}

static WEBP_INLINE uint32_t VP8LSubPixels(uint32_t a, uint32_t b) {
  const uint32_t alpha_and_green =
      0x00ff00ffu + (a & 0xff00ff00u) - (b & 0xff00ff00u);
  const uint32_t red_and_blue =
      0xff00ff00u + (a & 0x00ff00ffu) - (b & 0x00ff00ffu);
  return (alpha_and_green & 0xff00ff00u) | (red_and_blue & 0x00ff00ffu);
}

void VP8LBundleColorMap(const uint8_t* const row, int width,
                        int xbits, uint32_t* const dst);


#ifdef __cplusplus
}    
#endif

#endif  
