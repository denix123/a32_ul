// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_APPLICATION_INTERFACE_FACTORY_H_
#define MOJO_PUBLIC_CPP_APPLICATION_INTERFACE_FACTORY_H_

#include "mojo/public/cpp/bindings/interface_impl.h"
#include "mojo/public/cpp/bindings/interface_request.h"

namespace mojo {

class ApplicationConnection;
template <typename Interface> class InterfaceRequest;

template <typename Interface>
class InterfaceFactory {
 public:
  virtual ~InterfaceFactory() {}
  virtual void Create(ApplicationConnection* connection,
                      InterfaceRequest<Interface> request) = 0;
};

}  

#endif  
