// Copyright 2014 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_ENDIAN_INL_H_
#define WEBP_UTILS_ENDIAN_INL_H_

#ifdef HAVE_CONFIG_H
#include "../webp/config.h"
#endif

#include "../webp/types.h"

#if !defined(WORDS_BIGENDIAN) && \
    (defined(__BIG_ENDIAN__) || defined(_M_PPC) || \
     (defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))
#define WORDS_BIGENDIAN
#endif

#if defined(WORDS_BIGENDIAN)
#define HToLE32 BSwap32
#define HToLE16 BSwap16
#else
#define HToLE32(x) (x)
#define HToLE16(x) (x)
#endif

#if !defined(HAVE_CONFIG_H)
#ifdef __GNUC__
# define LOCAL_GCC_VERSION ((__GNUC__ << 8) | __GNUC_MINOR__)
#else
# define LOCAL_GCC_VERSION 0
#endif  

#ifdef __clang__
# define LOCAL_CLANG_VERSION ((__clang_major__ << 8) | __clang_minor__)
#else
# define LOCAL_CLANG_VERSION 0
#endif  

#if LOCAL_GCC_VERSION >= 0x403 || LOCAL_CLANG_VERSION >= 0x303
#define HAVE_BUILTIN_BSWAP32
#define HAVE_BUILTIN_BSWAP64
#endif
#if LOCAL_GCC_VERSION >= 0x408 || LOCAL_CLANG_VERSION >= 0x303
#define HAVE_BUILTIN_BSWAP16
#endif
#endif  

static WEBP_INLINE uint16_t BSwap16(uint16_t x) {
#if defined(HAVE_BUILTIN_BSWAP16)
  return __builtin_bswap16(x);
#elif defined(_MSC_VER)
  return _byteswap_ushort(x);
#else
  
  return (x >> 8) | ((x & 0xff) << 8);
#endif  
}

static WEBP_INLINE uint32_t BSwap32(uint32_t x) {
#if defined(HAVE_BUILTIN_BSWAP32)
  return __builtin_bswap32(x);
#elif defined(__i386__) || defined(__x86_64__)
  uint32_t swapped_bytes;
  __asm__ volatile("bswap %0" : "=r"(swapped_bytes) : "0"(x));
  return swapped_bytes;
#elif defined(_MSC_VER)
  return (uint32_t)_byteswap_ulong(x);
#else
  return (x >> 24) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000) | (x << 24);
#endif  
}

static WEBP_INLINE uint64_t BSwap64(uint64_t x) {
#if defined(HAVE_BUILTIN_BSWAP64)
  return __builtin_bswap64(x);
#elif defined(__x86_64__)
  uint64_t swapped_bytes;
  __asm__ volatile("bswapq %0" : "=r"(swapped_bytes) : "0"(x));
  return swapped_bytes;
#elif defined(_MSC_VER)
  return (uint64_t)_byteswap_uint64(x);
#else  
  x = ((x & 0xffffffff00000000ull) >> 32) | ((x & 0x00000000ffffffffull) << 32);
  x = ((x & 0xffff0000ffff0000ull) >> 16) | ((x & 0x0000ffff0000ffffull) << 16);
  x = ((x & 0xff00ff00ff00ff00ull) >>  8) | ((x & 0x00ff00ff00ff00ffull) <<  8);
  return x;
#endif  
}

#endif  
