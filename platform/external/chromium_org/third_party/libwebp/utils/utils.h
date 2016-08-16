// Copyright 2012 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_UTILS_H_
#define WEBP_UTILS_UTILS_H_

#include <assert.h>

#include "../webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif


#define WEBP_MAX_ALLOCABLE_MEMORY (1ULL << 40)

WEBP_EXTERN(void*) WebPSafeMalloc(uint64_t nmemb, size_t size);
WEBP_EXTERN(void*) WebPSafeCalloc(uint64_t nmemb, size_t size);

WEBP_EXTERN(void) WebPSafeFree(void* const ptr);


static WEBP_INLINE int GetLE16(const uint8_t* const data) {
  return (int)(data[0] << 0) | (data[1] << 8);
}

static WEBP_INLINE int GetLE24(const uint8_t* const data) {
  return GetLE16(data) | (data[2] << 16);
}

static WEBP_INLINE uint32_t GetLE32(const uint8_t* const data) {
  return (uint32_t)GetLE16(data) | (GetLE16(data + 2) << 16);
}

static WEBP_INLINE void PutLE16(uint8_t* const data, int val) {
  assert(val < (1 << 16));
  data[0] = (val >> 0);
  data[1] = (val >> 8);
}

static WEBP_INLINE void PutLE24(uint8_t* const data, int val) {
  assert(val < (1 << 24));
  PutLE16(data, val & 0xffff);
  data[2] = (val >> 16);
}

static WEBP_INLINE void PutLE32(uint8_t* const data, uint32_t val) {
  PutLE16(data, (int)(val & 0xffff));
  PutLE16(data + 2, (int)(val >> 16));
}

#if defined(__GNUC__) && \
    ((__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || __GNUC__ >= 4)
static WEBP_INLINE int BitsLog2Floor(uint32_t n) {
  return 31 ^ __builtin_clz(n);
}
#elif defined(_MSC_VER) && _MSC_VER > 1310 && \
      (defined(_M_X64) || defined(_M_IX86))
#include <intrin.h>
#pragma intrinsic(_BitScanReverse)

static WEBP_INLINE int BitsLog2Floor(uint32_t n) {
  uint32_t first_set_bit;
  _BitScanReverse(&first_set_bit, n);
  return first_set_bit;
}
#else
static WEBP_INLINE int BitsLog2Floor(uint32_t n) {
  int log = 0;
  uint32_t value = n;
  int i;

  for (i = 4; i >= 0; --i) {
    const int shift = (1 << i);
    const uint32_t x = value >> shift;
    if (x != 0) {
      value = x;
      log += shift;
    }
  }
  return log;
}
#endif


#ifdef __cplusplus
}    
#endif

#endif  
