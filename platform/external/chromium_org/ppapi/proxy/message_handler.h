// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_MESSAGE_HANDLER_H_
#define PPAPI_PROXY_MESSAGE_HANDLER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "ppapi/c/dev/ppb_messaging_deprecated.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/ppp_message_handler.h"
#include "ppapi/proxy/ppapi_proxy_export.h"

namespace IPC {
class Message;
}

namespace ppapi {

class ScopedPPVar;

namespace proxy {

class MessageLoopResource;

class PPAPI_PROXY_EXPORT MessageHandler {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  static scoped_ptr<MessageHandler> Create(
      PP_Instance instance,
      const PPP_MessageHandler_0_2* handler_if,
      void* user_data,
      PP_Resource message_loop,
      int32_t* error);
  
  
  
  static scoped_ptr<MessageHandler> CreateDeprecated(
      PP_Instance instance,
      const PPP_MessageHandler_0_1_Deprecated* handler_if,
      void* user_data,
      PP_Resource message_loop,
      int32_t* error);
  ~MessageHandler();

  bool LoopIsValid() const;

  void HandleMessage(ScopedPPVar var);
  void HandleBlockingMessage(ScopedPPVar var,
                             scoped_ptr<IPC::Message> reply_msg);

 private:
  MessageHandler(PP_Instance instance,
                 const PPP_MessageHandler_0_2* handler_if,
                 void* user_data,
                 scoped_refptr<MessageLoopResource> message_loop);
  MessageHandler(PP_Instance instance,
                 const PPP_MessageHandler_0_1_Deprecated* handler_if,
                 void* user_data,
                 scoped_refptr<MessageLoopResource> message_loop);


  PP_Instance instance_;
  const PPP_MessageHandler_0_2* handler_if_;
  const PPP_MessageHandler_0_1_Deprecated* handler_if_0_1_;
  void* user_data_;
  scoped_refptr<MessageLoopResource> message_loop_;

  DISALLOW_COPY_AND_ASSIGN(MessageHandler);
};

}  
}  

#endif  
