/*
 * Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef PPAPI_NATIVE_CLIENT_SRC_UNTRUSTED_PNACL_IRT_SHIM_IRT_SHIM_PPAPI_H_
#define PPAPI_NATIVE_CLIENT_SRC_UNTRUSTED_PNACL_IRT_SHIM_IRT_SHIM_PPAPI_H_

#include "ppapi/nacl_irt/public/irt_ppapi.h"

#ifdef PNACL_SHIM_AOT

extern int (*real_irt_ppapi_start)(const struct PP_StartFunctions *);
extern int irt_shim_ppapi_start(const struct PP_StartFunctions *funcs);

#else

#define NACL_IRT_PPAPIHOOK_PNACL_PRIVATE_v0_1   \
  "nacl-irt-ppapihook-pnacl-private-0.1"
extern const struct nacl_irt_ppapihook nacl_irt_ppapihook_pnacl_private;

#endif

#endif
