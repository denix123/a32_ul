// Copyright 2011 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#include "./dsp.h"

#if defined(__ANDROID__)
#include <cpu-features.h>
#endif


#if (defined(__pic__) || defined(__PIC__)) && defined(__i386__)
static WEBP_INLINE void GetCPUInfo(int cpu_info[4], int info_type) {
  __asm__ volatile (
    "mov %%ebx, %%edi\n"
    "cpuid\n"
    "xchg %%edi, %%ebx\n"
    : "=a"(cpu_info[0]), "=D"(cpu_info[1]), "=c"(cpu_info[2]), "=d"(cpu_info[3])
    : "a"(info_type));
}
#elif defined(__i386__) || defined(__x86_64__)
static WEBP_INLINE void GetCPUInfo(int cpu_info[4], int info_type) {
  __asm__ volatile (
    "cpuid\n"
    : "=a"(cpu_info[0]), "=b"(cpu_info[1]), "=c"(cpu_info[2]), "=d"(cpu_info[3])
    : "a"(info_type));
}
#elif defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 150030729  
#define GetCPUInfo(info, type) __cpuidex(info, type, 0)  
#elif defined(WEBP_MSC_SSE2)
#define GetCPUInfo __cpuid
#endif

#if !defined(__native_client__) && (defined(__i386__) || defined(__x86_64__))
static WEBP_INLINE uint64_t xgetbv(void) {
  const uint32_t ecx = 0;
  uint32_t eax, edx;
  
  __asm__ volatile (
    ".byte 0x0f, 0x01, 0xd0\n"
    : "=a"(eax), "=d"(edx) : "c" (ecx));
  return ((uint64_t)edx << 32) | eax;
}
#elif defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 160040219  
#define xgetbv() _xgetbv(0)
#elif defined(_M_IX86)
static WEBP_INLINE uint64_t xgetbv(void) {
  uint32_t eax_, edx_;
  __asm {
    xor ecx, ecx  
    
    __asm _emit 0x0f __asm _emit 0x01 __asm _emit 0xd0
    mov eax_, eax
    mov edx_, edx
  }
  return ((uint64_t)edx_ << 32) | eax_;
}
#else
#define xgetbv() 0U  
#endif

#if defined(__i386__) || defined(__x86_64__) || defined(WEBP_MSC_SSE2)
static int x86CPUInfo(CPUFeature feature) {
  int cpu_info[4];
  GetCPUInfo(cpu_info, 1);
  if (feature == kSSE2) {
    return 0 != (cpu_info[3] & 0x04000000);
  }
  if (feature == kSSE3) {
    return 0 != (cpu_info[2] & 0x00000001);
  }
  if (feature == kAVX) {
    
    if ((cpu_info[2] & 0x18000000) == 0x18000000) {
      
      return (xgetbv() & 0x6) == 0x6;
    }
  }
  if (feature == kAVX2) {
    if (x86CPUInfo(kAVX)) {
      GetCPUInfo(cpu_info, 7);
      return ((cpu_info[1] & 0x00000020) == 0x00000020);
    }
  }
  return 0;
}
VP8CPUInfo VP8GetCPUInfo = x86CPUInfo;
#elif defined(WEBP_ANDROID_NEON)  
static int AndroidCPUInfo(CPUFeature feature) {
  const AndroidCpuFamily cpu_family = android_getCpuFamily();
  const uint64_t cpu_features = android_getCpuFeatures();
  if (feature == kNEON) {
    return (cpu_family == ANDROID_CPU_FAMILY_ARM &&
            0 != (cpu_features & ANDROID_CPU_ARM_FEATURE_NEON));
  }
  return 0;
}
VP8CPUInfo VP8GetCPUInfo = AndroidCPUInfo;
#elif defined(WEBP_USE_NEON)
static int armCPUInfo(CPUFeature feature) {
  (void)feature;
  return 1;
}
VP8CPUInfo VP8GetCPUInfo = armCPUInfo;
#elif defined(WEBP_USE_MIPS32)
static int mipsCPUInfo(CPUFeature feature) {
  (void)feature;
  return 1;
}
VP8CPUInfo VP8GetCPUInfo = mipsCPUInfo;
#else
VP8CPUInfo VP8GetCPUInfo = NULL;
#endif

