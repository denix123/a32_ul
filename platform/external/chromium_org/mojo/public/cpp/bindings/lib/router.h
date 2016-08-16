// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_ROUTER_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_ROUTER_H_

#include <map>

#include "mojo/public/cpp/bindings/lib/connector.h"
#include "mojo/public/cpp/bindings/lib/filter_chain.h"
#include "mojo/public/cpp/bindings/lib/shared_data.h"
#include "mojo/public/cpp/environment/environment.h"

namespace mojo {
namespace internal {

class Router : public MessageReceiverWithResponder {
 public:
  Router(ScopedMessagePipeHandle message_pipe,
         FilterChain filters,
         const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter());
  virtual ~Router();

  
  
  void set_incoming_receiver(MessageReceiverWithResponder* receiver) {
    incoming_receiver_ = receiver;
  }

  
  
  void set_error_handler(ErrorHandler* error_handler) {
    connector_.set_error_handler(error_handler);
  }

  
  
  bool encountered_error() const { return connector_.encountered_error(); }

  void CloseMessagePipe() {
    connector_.CloseMessagePipe();
  }

  ScopedMessagePipeHandle PassMessagePipe() {
    return connector_.PassMessagePipe();
  }

  
  virtual bool Accept(Message* message) MOJO_OVERRIDE;
  virtual bool AcceptWithResponder(Message* message, MessageReceiver* responder)
      MOJO_OVERRIDE;

  
  
  bool WaitForIncomingMessage() {
    return connector_.WaitForIncomingMessage();
  }

  
  
  
  
  
  void EnableTestingMode();

 private:
  typedef std::map<uint64_t, MessageReceiver*> ResponderMap;

  class HandleIncomingMessageThunk : public MessageReceiver {
   public:
    HandleIncomingMessageThunk(Router* router);
    virtual ~HandleIncomingMessageThunk();

    
    virtual bool Accept(Message* message) MOJO_OVERRIDE;

   private:
    Router* router_;
  };

  bool HandleIncomingMessage(Message* message);

  HandleIncomingMessageThunk thunk_;
  FilterChain filters_;
  Connector connector_;
  SharedData<Router*> weak_self_;
  MessageReceiverWithResponder* incoming_receiver_;
  ResponderMap responders_;
  uint64_t next_request_id_;
  bool testing_mode_;
};

}  
}  

#endif  
