// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_APPLICATION_SERVICE_PROVIDER_IMPL_H_
#define MOJO_PUBLIC_APPLICATION_SERVICE_PROVIDER_IMPL_H_

#include "mojo/public/cpp/application/lib/service_connector.h"
#include "mojo/public/interfaces/application/service_provider.mojom.h"

namespace mojo {
namespace internal {
class WeakServiceProvider;
class ServiceConnectorBase;
}

class ServiceProviderImpl : public InterfaceImpl<ServiceProvider> {
 public:
  ServiceProviderImpl();
  virtual ~ServiceProviderImpl();

  template <typename Interface>
  void AddService(InterfaceFactory<Interface>* factory) {
    AddServiceConnector(
        new internal::InterfaceFactoryConnector<Interface>(factory));
  }

  
  
  
  
  
  
  
  ServiceProvider* CreateRemoteServiceProvider();

 private:
  typedef std::map<std::string, internal::ServiceConnectorBase*>
      NameToServiceConnectorMap;

  friend class internal::WeakServiceProvider;

  
  virtual void ConnectToService(
      const String& service_name,
      ScopedMessagePipeHandle client_handle) MOJO_OVERRIDE;

  
  virtual void OnConnectionError() MOJO_OVERRIDE;

  void AddServiceConnector(
      internal::ServiceConnectorBase* service_connector);
  void RemoveServiceConnector(
      internal::ServiceConnectorBase* service_connector);

  void ClearRemote();

  NameToServiceConnectorMap service_connectors_;

  internal::WeakServiceProvider* remote_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(ServiceProviderImpl);
};

}  

#endif  
