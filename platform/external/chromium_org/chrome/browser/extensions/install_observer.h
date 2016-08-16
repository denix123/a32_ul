// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_INSTALL_OBSERVER_H_
#define CHROME_BROWSER_EXTENSIONS_INSTALL_OBSERVER_H_

#include <string>

#include "ui/gfx/image/image_skia.h"

namespace extensions {

class Extension;

class InstallObserver {
 public:
  struct ExtensionInstallParams {
    ExtensionInstallParams(
        std::string extension_id,
        std::string extension_name,
        gfx::ImageSkia installing_icon,
        bool is_app,
        bool is_platform_app);

    std::string extension_id;
    std::string extension_name;
    gfx::ImageSkia installing_icon;
    bool is_app;
    bool is_platform_app;
    bool is_ephemeral;
  };

  
  
  virtual void OnBeginExtensionInstall(const ExtensionInstallParams& params) {}

  
  
  
  virtual void OnBeginExtensionDownload(const std::string& extension_id) {}

  
  
  
  
  virtual void OnDownloadProgress(const std::string& extension_id,
                                  int percent_downloaded) {}

  
  
  virtual void OnBeginCrxInstall(const std::string& extension_id) {}

  
  
  virtual void OnFinishCrxInstall(const std::string& extension_id,
                                  bool success) {}

  
  virtual void OnInstallFailure(const std::string& extension_id) {}

  
  
  virtual void OnDisabledExtensionUpdated(const Extension* extension) {}
  virtual void OnAppInstalledToAppList(const std::string& extension_id) {}

  
  virtual void OnAppsReordered() {}

  
  virtual void OnShutdown() {}

 protected:
  virtual ~InstallObserver() {}
};

}  

#endif  
