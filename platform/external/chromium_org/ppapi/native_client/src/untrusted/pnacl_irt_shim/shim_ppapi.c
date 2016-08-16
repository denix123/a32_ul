/*
 * Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "ppapi/native_client/src/untrusted/pnacl_irt_shim/shim_ppapi.h"

#include <string.h>
#include "native_client/src/untrusted/irt/irt.h"
#include "ppapi/nacl_irt/public/irt_ppapi.h"
#include "ppapi/native_client/src/shared/ppapi_proxy/ppruntime.h"
#include "ppapi/native_client/src/untrusted/pnacl_irt_shim/irt_shim_ppapi.h"
#include "ppapi/native_client/src/untrusted/pnacl_irt_shim/pnacl_shim.h"

static int mystrcmp(const char* s1, const char *s2) {
  while((*s1 && *s2) && (*s1++ == *s2++));
  return *(--s1) - *(--s2);
}

TYPE_nacl_irt_query __pnacl_real_irt_query_func = NULL;

size_t __pnacl_wrap_irt_query_func(const char *interface_ident,
                                     void *table, size_t tablesize) {
  if (0 != mystrcmp(interface_ident, NACL_IRT_PPAPIHOOK_v0_1)) {
    return (*__pnacl_real_irt_query_func)(interface_ident, table, tablesize);
  }
#ifndef PNACL_SHIM_AOT
  return (*__pnacl_real_irt_query_func)(NACL_IRT_PPAPIHOOK_PNACL_PRIVATE_v0_1,
                                        table, tablesize);
#else
  struct nacl_irt_ppapihook real_irt_ppapi_hook;
  if ((*__pnacl_real_irt_query_func)(NACL_IRT_PPAPIHOOK_v0_1,
                                     &real_irt_ppapi_hook,
                                     sizeof real_irt_ppapi_hook) !=
      sizeof real_irt_ppapi_hook) {
    return 0;
  }
  real_irt_ppapi_start = real_irt_ppapi_hook.ppapi_start;
  struct nacl_irt_ppapihook *dest = table;
  if (sizeof *dest <= tablesize) {
    dest->ppapi_start = irt_shim_ppapi_start;
    dest->ppapi_register_thread_creator =
        real_irt_ppapi_hook.ppapi_register_thread_creator;
    return sizeof *dest;
  }
  return 0;
#endif
}
