// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_INTERFACE_IMPL_H_
#define MOJO_PUBLIC_CPP_BINDINGS_INTERFACE_IMPL_H_

#include "mojo/public/cpp/bindings/interface_request.h"
#include "mojo/public/cpp/bindings/lib/interface_impl_internal.h"
#include "mojo/public/cpp/environment/environment.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {

template <typename Interface>
class InterfaceImpl : public internal::InterfaceImplBase<Interface> {
 public:
  typedef typename Interface::Client Client;
  typedef Interface ImplementedInterface;

  InterfaceImpl() : internal_state_(this) {}
  virtual ~InterfaceImpl() {}

  
  
  
  Client* client() { return internal_state_.client(); }

  
  
  
  
  bool WaitForIncomingMethodCall() {
    return internal_state_.WaitForIncomingMethodCall();
  }

  
  virtual void OnConnectionEstablished() {}

  
  
  
  
  virtual void OnConnectionError() {}

  
  internal::InterfaceImplState<Interface>* internal_state() {
    return &internal_state_;
  }

 private:
  internal::InterfaceImplState<Interface> internal_state_;
  MOJO_DISALLOW_COPY_AND_ASSIGN(InterfaceImpl);
};

template <typename Impl>
Impl* BindToPipe(
    Impl* instance,
    ScopedMessagePipeHandle handle,
    const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
  instance->internal_state()->Bind(handle.Pass(), true, waiter);
  return instance;
}

template <typename Impl>
Impl* WeakBindToPipe(
    Impl* instance,
    ScopedMessagePipeHandle handle,
    const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
  instance->internal_state()->Bind(handle.Pass(), false, waiter);
  return instance;
}

template <typename Impl, typename Interface>
Impl* BindToProxy(
    Impl* instance,
    InterfacePtr<Interface>* ptr,
    const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
  instance->internal_state()->BindProxy(ptr, true, waiter);
  return instance;
}

template <typename Impl, typename Interface>
Impl* WeakBindToProxy(
    Impl* instance,
    InterfacePtr<Interface>* ptr,
    const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
  instance->internal_state()->BindProxy(ptr, false, waiter);
  return instance;
}

template <typename Impl, typename Interface>
Impl* BindToRequest(
    Impl* instance,
    InterfaceRequest<Interface>* request,
    const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
  return BindToPipe(instance, request->PassMessagePipe(), waiter);
}

template <typename Impl, typename Interface>
Impl* WeakBindToRequest(
    Impl* instance,
    InterfaceRequest<Interface>* request,
    const MojoAsyncWaiter* waiter = Environment::GetDefaultAsyncWaiter()) {
  return WeakBindToPipe(instance, request->PassMessagePipe(), waiter);
}

}  

#endif  
