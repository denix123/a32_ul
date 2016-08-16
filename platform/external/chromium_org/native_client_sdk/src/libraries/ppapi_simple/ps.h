/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. */

#ifndef PPAPI_SIMPLE_PS_H_
#define PPAPI_SIMPLE_PS_H_

#include "ppapi/c/pp_instance.h"
#include "sdk_util/macros.h"

EXTERN_C_BEGIN


PP_Instance PSGetInstanceId(void);

const void* PSGetInterface(const char *name);

extern void* PSUserCreateInstance(PP_Instance inst);

EXTERN_C_END

#endif  
