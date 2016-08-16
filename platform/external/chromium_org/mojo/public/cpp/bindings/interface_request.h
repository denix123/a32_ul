// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_INTERFACE_REQUEST_H_
#define MOJO_PUBLIC_CPP_BINDINGS_INTERFACE_REQUEST_H_

#include "mojo/public/cpp/bindings/interface_ptr.h"

namespace mojo {

template <typename Interface>
class InterfaceRequest {
  MOJO_MOVE_ONLY_TYPE_FOR_CPP_03(InterfaceRequest, RValue)
 public:
  InterfaceRequest() {}

  InterfaceRequest(RValue other) {
    handle_ = other.object->handle_.Pass();
  }
  InterfaceRequest& operator=(RValue other) {
    handle_ = other.object->handle_.Pass();
    return *this;
  }

  
  bool is_pending() const { return handle_.is_valid(); }

  void Bind(ScopedMessagePipeHandle handle) {
    handle_ = handle.Pass();
  }

  ScopedMessagePipeHandle PassMessagePipe() {
    return handle_.Pass();
  }

 private:
  ScopedMessagePipeHandle handle_;
};

template <typename Interface>
InterfaceRequest<Interface> MakeRequest(ScopedMessagePipeHandle handle) {
  InterfaceRequest<Interface> request;
  request.Bind(handle.Pass());
  return request.Pass();
}

template <typename Interface>
InterfaceRequest<Interface> Get(InterfacePtr<Interface>* ptr) {
  MessagePipe pipe;
  ptr->Bind(pipe.handle0.Pass());
  return MakeRequest<Interface>(pipe.handle1.Pass());
}

}  

#endif  
