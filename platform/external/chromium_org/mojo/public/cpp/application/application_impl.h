// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_APPLICATION_APPLICATION_IMPL_H_
#define MOJO_PUBLIC_APPLICATION_APPLICATION_IMPL_H_
#include <vector>

#include "mojo/public/cpp/application/application_connection.h"
#include "mojo/public/cpp/application/lib/service_connector.h"
#include "mojo/public/cpp/application/lib/service_registry.h"
#include "mojo/public/cpp/system/core.h"
#include "mojo/public/interfaces/application/application.mojom.h"
#include "mojo/public/interfaces/application/shell.mojom.h"

namespace mojo {

class ApplicationDelegate;

class ApplicationImpl : public InterfaceImpl<Application> {
 public:
  ApplicationImpl(ApplicationDelegate* delegate,
                  ScopedMessagePipeHandle shell_handle);
  ApplicationImpl(ApplicationDelegate* delegate,
                  MojoHandle shell_handle);
  virtual ~ApplicationImpl();

  Shell* shell() const { return shell_.get(); }

  
  const Array<String>& args() { return args_; }

  
  ApplicationConnection* ConnectToApplication(const String& application_url);

  
  
  template <typename Interface>
  void ConnectToService(const std::string& application_url,
                        InterfacePtr<Interface>* ptr) {
    ConnectToApplication(application_url)->ConnectToService(ptr);
  }

 private:
  class ShellPtrWatcher;

  void BindShell(ScopedMessagePipeHandle shell_handle);
  void ClearConnections();
  void OnShellError() {
    ClearConnections();
    Terminate();
  };

  
  static void Terminate();

  
  virtual void Initialize(Array<String> args) MOJO_OVERRIDE;
  virtual void AcceptConnection(const String& requestor_url,
                                ServiceProviderPtr provider) MOJO_OVERRIDE;

  typedef std::vector<internal::ServiceRegistry*> ServiceRegistryList;

  bool initialized_;
  ServiceRegistryList incoming_service_registries_;
  ServiceRegistryList outgoing_service_registries_;
  ApplicationDelegate* delegate_;
  ShellPtr shell_;
  ShellPtrWatcher* shell_watch_;
  Array<String> args_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(ApplicationImpl);
};

}  

#endif  
