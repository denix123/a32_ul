// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_RUNTIME_RUNTIME_API_DELEGATE_H
#define EXTENSIONS_BROWSER_API_RUNTIME_RUNTIME_API_DELEGATE_H

#include "base/callback.h"
#include "base/version.h"

class GURL;

namespace extensions {

namespace core_api {
namespace runtime {
struct PlatformInfo;
}
}

class Extension;
class UpdateObserver;

class RuntimeAPIDelegate {
 public:
  struct UpdateCheckResult {
    bool success;
    std::string response;
    std::string version;

    UpdateCheckResult(bool success,
                      const std::string& response,
                      const std::string& version);
  };

  virtual ~RuntimeAPIDelegate() {}

  
  typedef base::Callback<void(const UpdateCheckResult&)> UpdateCheckCallback;

  
  virtual void AddUpdateObserver(UpdateObserver* observer) = 0;

  
  virtual void RemoveUpdateObserver(UpdateObserver* observer) = 0;

  
  virtual base::Version GetPreviousExtensionVersion(
      const Extension* extension) = 0;

  
  virtual void ReloadExtension(const std::string& extension_id) = 0;

  
  
  
  virtual bool CheckForUpdates(const std::string& extension_id,
                               const UpdateCheckCallback& callback) = 0;

  
  virtual void OpenURL(const GURL& uninstall_url) = 0;

  
  
  virtual bool GetPlatformInfo(core_api::runtime::PlatformInfo* info) = 0;

  
  
  virtual bool RestartDevice(std::string* error_message) = 0;
};

}  

#endif  
