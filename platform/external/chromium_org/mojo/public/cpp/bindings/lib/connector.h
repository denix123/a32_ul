// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_CONNECTOR_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_CONNECTOR_H_

#include "mojo/public/c/environment/async_waiter.h"
#include "mojo/public/cpp/bindings/lib/message_queue.h"
#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/environment/environment.h"
#include "mojo/public/cpp/system/core.h"

namespace mojo {
class ErrorHandler;

namespace internal {

class Connector : public MessageReceiver {
 public:
  
  explicit Connector(
      ScopedMessagePipeHandle message_pipe,
      const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter());
  virtual ~Connector();

  
  
  
  void set_incoming_receiver(MessageReceiver* receiver) {
    incoming_receiver_ = receiver;
  }

  
  
  
  void set_enforce_errors_from_incoming_receiver(bool enforce) {
    enforce_errors_from_incoming_receiver_ = enforce;
  }

  
  
  void set_error_handler(ErrorHandler* error_handler) {
    error_handler_ = error_handler;
  }

  
  
  bool encountered_error() const { return error_; }

  
  
  void CloseMessagePipe();

  
  
  ScopedMessagePipeHandle PassMessagePipe();

  
  
  
  bool WaitForIncomingMessage();

  
  virtual bool Accept(Message* message) MOJO_OVERRIDE;

 private:
  static void CallOnHandleReady(void* closure, MojoResult result);
  void OnHandleReady(MojoResult result);

  void WaitToReadMore();

  
  MOJO_WARN_UNUSED_RESULT bool ReadSingleMessage(MojoResult* read_result);

  
  void ReadAllAvailableMessages();

  void NotifyError();

  
  void CancelWait();

  ErrorHandler* error_handler_;
  const MojoAsyncWaiter* waiter_;

  ScopedMessagePipeHandle message_pipe_;
  MessageReceiver* incoming_receiver_;

  MojoAsyncWaitID async_wait_id_;
  bool error_;
  bool drop_writes_;
  bool enforce_errors_from_incoming_receiver_;

  
  
  
  bool* destroyed_flag_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(Connector);
};

}  
}  

#endif  
