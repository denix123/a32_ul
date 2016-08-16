/*
 * Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef PPAPI_NACL_IRT_PUBLIC_IRT_NONSFI_H_
#define PPAPI_NACL_IRT_PUBLIC_IRT_NONSFI_H_

#include <stddef.h>

#define NACL_IRT_ICACHE_v0_1 "nacl-irt-icache-0.1"
struct nacl_irt_icache {
  int (*clear_cache)(void* addr, size_t size);
};

#endif  
