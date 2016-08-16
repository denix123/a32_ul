// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_C_SYSTEM_MACROS_H_
#define MOJO_PUBLIC_C_SYSTEM_MACROS_H_

#include <stddef.h>

#if defined(__GNUC__)
#define MOJO_ALLOW_UNUSED __attribute__((unused))
#else
#define MOJO_ALLOW_UNUSED
#endif

#if defined(__GNUC__)
#define MOJO_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define MOJO_WARN_UNUSED_RESULT
#endif

#ifdef __cplusplus
template <typename T>
inline void mojo_ignore_result(const T&) {
}
#endif

#if __cplusplus >= 201103L
#define MOJO_COMPILE_ASSERT(expr, msg) static_assert(expr, #msg)
#elif defined(__cplusplus)
namespace mojo {
template <bool>
struct CompileAssert {};
}
#define MOJO_COMPILE_ASSERT(expr, msg) \
  typedef ::mojo::CompileAssert<(bool(expr))> msg[bool(expr) ? 1 : -1]
#else
#define MOJO_COMPILE_ASSERT(expr, msg)
#endif

#if __cplusplus >= 201103L
#define MOJO_ALIGNOF(type) alignof(type)
#elif defined(__GNUC__)
#define MOJO_ALIGNOF(type) __alignof__(type)
#elif defined(_MSC_VER)
#define MOJO_ALIGNOF(type) (sizeof(type) - sizeof(type) + __alignof(type))
#else
#error "Please define MOJO_ALIGNOF() for your compiler."
#endif

#if __cplusplus >= 201103L
#define MOJO_ALIGNAS(alignment) alignas(alignment)
#elif defined(__GNUC__)
#define MOJO_ALIGNAS(alignment) __attribute__((aligned(alignment)))
#elif defined(_MSC_VER)
#define MOJO_ALIGNAS(alignment) __declspec(align(alignment))
#else
#error "Please define MOJO_ALIGNAS() for your compiler."
#endif

#endif  
