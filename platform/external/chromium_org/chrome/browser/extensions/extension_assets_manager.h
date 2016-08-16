// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ASSETS_MANAGER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ASSETS_MANAGER_H_

#include <string>

#include "base/callback.h"
#include "base/files/file_path.h"

class Profile;

namespace extensions {

class Extension;

class ExtensionAssetsManager {
 public:
  
  
  typedef base::Callback<void(const base::FilePath& file_path)>
      InstallExtensionCallback;

  static ExtensionAssetsManager* GetInstance();

  
  
  virtual void InstallExtension(const Extension* extension,
                                const base::FilePath& unpacked_extension_root,
                                const base::FilePath& local_install_dir,
                                Profile* profile,
                                InstallExtensionCallback callback) = 0;

  
  virtual void UninstallExtension(const std::string& id,
                                  Profile* profile,
                                  const base::FilePath& local_install_dir,
                                  const base::FilePath& extension_root) = 0;

 protected:
  virtual ~ExtensionAssetsManager() {}
};

}  

#endif  
