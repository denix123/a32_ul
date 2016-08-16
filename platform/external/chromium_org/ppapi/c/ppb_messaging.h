/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_MESSAGING_H_
#define PPAPI_C_PPB_MESSAGING_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/c/ppp_message_handler.h"

#define PPB_MESSAGING_INTERFACE_1_0 "PPB_Messaging;1.0"
#define PPB_MESSAGING_INTERFACE_1_2 "PPB_Messaging;1.2"
#define PPB_MESSAGING_INTERFACE PPB_MESSAGING_INTERFACE_1_2



struct PPB_Messaging_1_2 {
  void (*PostMessage)(PP_Instance instance, struct PP_Var message);
  int32_t (*RegisterMessageHandler)(
      PP_Instance instance,
      void* user_data,
      const struct PPP_MessageHandler_0_2* handler,
      PP_Resource message_loop);
  void (*UnregisterMessageHandler)(PP_Instance instance);
};

typedef struct PPB_Messaging_1_2 PPB_Messaging;

struct PPB_Messaging_1_0 {
  void (*PostMessage)(PP_Instance instance, struct PP_Var message);
};

#endif  

