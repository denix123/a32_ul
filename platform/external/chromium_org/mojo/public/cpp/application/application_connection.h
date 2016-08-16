// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_APPLICATION_APPLICATION_CONNECTION_H_
#define MOJO_PUBLIC_APPLICATION_APPLICATION_CONNECTION_H_

#include <string>

#include "mojo/public/cpp/application/lib/service_connector.h"
#include "mojo/public/interfaces/application/service_provider.mojom.h"

namespace mojo {

class ApplicationConnection {
 public:
  virtual ~ApplicationConnection();

  template <typename Interface>
  void AddService(InterfaceFactory<Interface>* factory) {
    AddServiceConnector(
        new internal::InterfaceFactoryConnector<Interface>(factory));
  }

  
  template <typename Interface>
  void ConnectToService(InterfacePtr<Interface>* ptr) {
    MessagePipe pipe;
    ptr->Bind(pipe.handle0.Pass());
    GetServiceProvider()->ConnectToService(Interface::Name_,
                                           pipe.handle1.Pass());
  }

  
  virtual const std::string& GetRemoteApplicationURL() = 0;

  
  
  virtual ApplicationConnection* ConnectToApplication(
      const std::string& url) = 0;

  
  
  template <typename Interface>
  void ConnectToService(const std::string& application_url,
                        InterfacePtr<Interface>* ptr) {
    ConnectToApplication(application_url)->ConnectToService(ptr);
  }

  
  virtual ServiceProvider* GetServiceProvider() = 0;

 private:
  virtual void AddServiceConnector(
      internal::ServiceConnectorBase* service_connector) = 0;
};

}  

#endif  
