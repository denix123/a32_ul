// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_SYSTEM_MACROS_H_
#define MOJO_PUBLIC_CPP_SYSTEM_MACROS_H_

#include "mojo/public/c/system/macros.h"


#if defined(_MSC_VER) || defined(__clang__)
#define MOJO_OVERRIDE override
#else
#define MOJO_OVERRIDE
#endif

#define MOJO_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

namespace mojo {
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
#if !defined(_MSC_VER)
template <typename T, size_t N>
char (&ArraySizeHelper(const T (&array)[N]))[N];
#endif
}  
#define MOJO_ARRAYSIZE(array) (sizeof(::mojo::ArraySizeHelper(array)))

#define MOJO_MOVE_ONLY_TYPE_FOR_CPP_03(type, rvalue_type) \
   private: \
    struct rvalue_type { \
      explicit rvalue_type(type* object) : object(object) {} \
      type* object; \
    }; \
    type(type&); \
    void operator=(type&); \
   public: \
    operator rvalue_type() { return rvalue_type(this); } \
    type Pass() { return type(rvalue_type(this)); } \
    typedef void MoveOnlyTypeForCPP03; \
   private:

#endif  
