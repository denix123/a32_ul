/*
 * Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "ppapi/native_client/src/untrusted/pnacl_irt_shim/irt_shim_ppapi.h"

#include "native_client/src/untrusted/irt/irt.h"
#include "ppapi/nacl_irt/public/irt_ppapi.h"
#include "ppapi/native_client/src/untrusted/pnacl_irt_shim/pnacl_shim.h"
#include "ppapi/nacl_irt/plugin_main.h"


static struct PP_StartFunctions g_user_start_functions;

static int32_t shim_PPPInitializeModule(PP_Module module_id,
                                        PPB_GetInterface get_browser_intf) {
  
  __set_real_Pnacl_PPBGetInterface(get_browser_intf);
  return (*g_user_start_functions.PPP_InitializeModule)(
      module_id,
      &__Pnacl_PPBGetInterface);
}

static void shim_PPPShutdownModule(void) {
  (*g_user_start_functions.PPP_ShutdownModule)();
}

#ifdef PNACL_SHIM_AOT
int (*real_irt_ppapi_start)(const struct PP_StartFunctions *) = NULL;
#else
extern int irt_ppapi_start(const struct PP_StartFunctions *);
static int (* const real_irt_ppapi_start)(const struct PP_StartFunctions *) =
    &irt_ppapi_start;
#endif

int irt_shim_ppapi_start(const struct PP_StartFunctions *funcs) {
  g_user_start_functions = *funcs;
  const struct PP_StartFunctions wrapped_ppapi_methods = {
    shim_PPPInitializeModule,
    shim_PPPShutdownModule,
    __Pnacl_PPPGetInterface
  };
  __set_real_Pnacl_PPPGetInterface(g_user_start_functions.PPP_GetInterface);
  return (*real_irt_ppapi_start)(&wrapped_ppapi_methods);
}

#ifndef PNACL_SHIM_AOT
const struct nacl_irt_ppapihook nacl_irt_ppapihook_pnacl_private = {
  irt_shim_ppapi_start,
  PpapiPluginRegisterThreadCreator,
};
#endif
