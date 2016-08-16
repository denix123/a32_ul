// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_CONTENT_PUBLIC_APP_REGISTRY_H_
#define ATHENA_CONTENT_PUBLIC_APP_REGISTRY_H_

#include <string>
#include <vector>

#include "athena/athena_export.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"

namespace content {
class BrowserContext;
}

namespace athena {

class AppActivityRegistry;
class AppRegistryImpl;

class ATHENA_EXPORT AppRegistry {
 public:
  
  static void Create();

  
  static AppRegistry* Get();

  
  static void ShutDown();

  
  
  virtual AppActivityRegistry* GetAppActivityRegistry(
      const std::string& app_id,
      content::BrowserContext* browser_context) = 0;

  
  virtual int NumberOfApplications() const = 0;

 protected:
  
  friend AppActivityRegistry;

  
  
  virtual void RemoveAppActivityRegistry(AppActivityRegistry* registry) = 0;

  
  AppRegistry();
  virtual ~AppRegistry();
};

}  

#endif  
