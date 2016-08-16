// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_SERVICE_REGISTRY_H_
#define CONTENT_PUBLIC_COMMON_SERVICE_REGISTRY_H_

#include <string>

#include "base/bind.h"
#include "base/callback.h"
#include "base/strings/string_piece.h"
#include "content/common/content_export.h"
#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "mojo/public/cpp/bindings/interface_request.h"
#include "mojo/public/cpp/system/core.h"

namespace content {

class CONTENT_EXPORT ServiceRegistry {
 public:
  virtual ~ServiceRegistry() {}

  
  
  
  
  template <typename Interface>
  void AddService(const base::Callback<void(mojo::InterfaceRequest<Interface>)>
                      service_factory) {
    AddService(Interface::Name_,
               base::Bind(&ServiceRegistry::ForwardToServiceFactory<Interface>,
                          service_factory));
  }
  virtual void AddService(
      const std::string& service_name,
      const base::Callback<void(mojo::ScopedMessagePipeHandle)>
          service_factory) = 0;

  
  
  template <typename Interface>
  void RemoveService() {
    RemoveService(Interface::Name_);
  }
  virtual void RemoveService(const std::string& service_name) = 0;

  
  template <typename Interface>
  void ConnectToRemoteService(mojo::InterfacePtr<Interface>* ptr) {
    mojo::MessagePipe pipe;
    ptr->Bind(pipe.handle0.Pass());
    ConnectToRemoteService(Interface::Name_, pipe.handle1.Pass());
  }
  virtual void ConnectToRemoteService(const base::StringPiece& name,
                                      mojo::ScopedMessagePipeHandle handle) = 0;

 private:
  template <typename Interface>
  static void ForwardToServiceFactory(
      const base::Callback<void(mojo::InterfaceRequest<Interface>)>
          service_factory,
      mojo::ScopedMessagePipeHandle handle) {
    service_factory.Run(mojo::MakeRequest<Interface>(handle.Pass()));
  }
};

}  

#endif  
