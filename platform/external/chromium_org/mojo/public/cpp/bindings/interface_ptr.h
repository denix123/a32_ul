// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_INTERFACE_PTR_H_
#define MOJO_PUBLIC_CPP_BINDINGS_INTERFACE_PTR_H_

#include <algorithm>

#include "mojo/public/cpp/bindings/error_handler.h"
#include "mojo/public/cpp/bindings/lib/interface_ptr_internal.h"
#include "mojo/public/cpp/environment/environment.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {
class ErrorHandler;

template <typename Interface>
class InterfacePtr {
  MOJO_MOVE_ONLY_TYPE_FOR_CPP_03(InterfacePtr, RValue)
 public:
  InterfacePtr() {}

  InterfacePtr(RValue other) {
    internal_state_.Swap(&other.object->internal_state_);
  }
  InterfacePtr& operator=(RValue other) {
    reset();
    internal_state_.Swap(&other.object->internal_state_);
    return *this;
  }

  ~InterfacePtr() {}

  Interface* get() const {
    return internal_state_.instance();
  }
  Interface* operator->() const { return get(); }
  Interface& operator*() const { return *get(); }

  void reset() {
    State doomed;
    internal_state_.Swap(&doomed);
  }

  
  
  
  
  bool WaitForIncomingMethodCall() {
    return internal_state_.WaitForIncomingMethodCall();
  }

  
  
  
  
  
  
  
  
  
  void Bind(
      ScopedMessagePipeHandle handle,
      const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
    reset();
    internal_state_.Bind(handle.Pass(), waiter);
  }

  
  void set_client(typename Interface::Client* client) {
    internal_state_.set_client(client);
  }

  
  
  
  bool encountered_error() const {
    return internal_state_.encountered_error();
  }

  
  
  
  
  void set_error_handler(ErrorHandler* error_handler) {
    internal_state_.set_error_handler(error_handler);
  }

  
  
  
  ScopedMessagePipeHandle PassMessagePipe() {
    State state;
    internal_state_.Swap(&state);
    return state.PassMessagePipe();
  }

  
  internal::InterfacePtrState<Interface>* internal_state() {
    return &internal_state_;
  }

  
  
 private:
  typedef internal::InterfacePtrState<Interface> InterfacePtr::*Testable;

 public:
  operator Testable() const {
    return internal_state_.is_bound() ? &InterfacePtr::internal_state_ : NULL;
  }

 private:
  typedef internal::InterfacePtrState<Interface> State;
  mutable State internal_state_;
};

template <typename Interface>
InterfacePtr<Interface> MakeProxy(
    ScopedMessagePipeHandle handle,
    const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
  InterfacePtr<Interface> ptr;
  if (handle.is_valid())
    ptr.Bind(handle.Pass(), waiter);
  return ptr.Pass();
}

}  

#endif  
