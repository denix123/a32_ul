// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_PUBLIC_CPP_VIEW_MANAGER_VIEW_MANAGER_DELEGATE_H_
#define MOJO_SERVICES_PUBLIC_CPP_VIEW_MANAGER_VIEW_MANAGER_DELEGATE_H_

#include "base/memory/scoped_ptr.h"
#include "mojo/public/interfaces/application/service_provider.mojom.h"

namespace mojo {

class ServiceProviderImpl;
class View;
class ViewManager;

class ViewManagerDelegate {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void OnEmbed(ViewManager* view_manager,
                       View* root,
                       ServiceProviderImpl* exported_services,
                       scoped_ptr<ServiceProvider> imported_services) = 0;

  
  
  virtual void OnViewManagerDisconnected(ViewManager* view_manager) = 0;

 protected:
  virtual ~ViewManagerDelegate() {}
};

}  

#endif  
