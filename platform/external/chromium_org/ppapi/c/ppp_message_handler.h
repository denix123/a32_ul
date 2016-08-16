/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPP_MESSAGE_HANDLER_H_
#define PPAPI_C_PPP_MESSAGE_HANDLER_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"



struct PPP_MessageHandler_0_2 {
  void (*HandleMessage)(PP_Instance instance,
                        void* user_data,
                        const struct PP_Var* message);
  void (*HandleBlockingMessage)(PP_Instance instance,
                                void* user_data,
                                const struct PP_Var* message,
                                struct PP_Var* response);
  void (*Destroy)(PP_Instance instance, void* user_data);
};

typedef struct PPP_MessageHandler_0_2 PPP_MessageHandler;

#endif  

