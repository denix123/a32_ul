// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef BASE_SYS_BYTEORDER_H_
#define BASE_SYS_BYTEORDER_H_

#include "base/basictypes.h"
#include "build/build_config.h"

#if defined(OS_WIN)
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

namespace base {

inline uint16 ByteSwap(uint16 x) {
  return ((x & 0x00ff) << 8) | ((x & 0xff00) >> 8);
}

inline uint32 ByteSwap(uint32 x) {
  return ((x & 0x000000fful) << 24) | ((x & 0x0000ff00ul) << 8) |
      ((x & 0x00ff0000ul) >> 8) | ((x & 0xff000000ul) >> 24);
}

inline uint64 ByteSwap(uint64 x) {
  return ((x & 0x00000000000000ffull) << 56) |
      ((x & 0x000000000000ff00ull) << 40) |
      ((x & 0x0000000000ff0000ull) << 24) |
      ((x & 0x00000000ff000000ull) << 8) |
      ((x & 0x000000ff00000000ull) >> 8) |
      ((x & 0x0000ff0000000000ull) >> 24) |
      ((x & 0x00ff000000000000ull) >> 40) |
      ((x & 0xff00000000000000ull) >> 56);
}

inline uint16 ByteSwapToLE16(uint16 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return x;
#else
  return ByteSwap(x);
#endif
}
inline uint32 ByteSwapToLE32(uint32 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return x;
#else
  return ByteSwap(x);
#endif
}
inline uint64 ByteSwapToLE64(uint64 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return x;
#else
  return ByteSwap(x);
#endif
}

inline uint16 NetToHost16(uint16 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return ByteSwap(x);
#else
  return x;
#endif
}
inline uint32 NetToHost32(uint32 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return ByteSwap(x);
#else
  return x;
#endif
}
inline uint64 NetToHost64(uint64 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return ByteSwap(x);
#else
  return x;
#endif
}

inline uint16 HostToNet16(uint16 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return ByteSwap(x);
#else
  return x;
#endif
}
inline uint32 HostToNet32(uint32 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return ByteSwap(x);
#else
  return x;
#endif
}
inline uint64 HostToNet64(uint64 x) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  return ByteSwap(x);
#else
  return x;
#endif
}

}  

#endif  
