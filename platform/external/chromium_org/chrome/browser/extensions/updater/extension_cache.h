// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_UPDATER_EXTENSION_CACHE_H_
#define CHROME_BROWSER_EXTENSIONS_UPDATER_EXTENSION_CACHE_H_

#include <string>

#include "base/callback_forward.h"
#include "base/files/file_path.h"

namespace extensions {

class ExtensionCache {
 public:
  
  static ExtensionCache* GetInstance();

  
  typedef base::Callback<void(const base::FilePath& file_path,
                              bool file_ownership_passed)> PutExtensionCallback;

  
  
  
  virtual void Start(const base::Closure& callback) = 0;

  
  virtual void Shutdown(const base::Closure& callback) = 0;

  
  
  
  virtual void AllowCaching(const std::string& id) = 0;

  
  
  
  virtual bool GetExtension(const std::string& id,
                            base::FilePath* file_path,
                            std::string* version) = 0;

  
  
  
  
  
  
  virtual void PutExtension(const std::string& id,
                            const base::FilePath& file_path,
                            const std::string& version,
                            const PutExtensionCallback& callback) = 0;

 protected:
  virtual ~ExtensionCache() {}

  
  
  static ExtensionCache* SetForTesting(ExtensionCache* cache);
};

}  

#endif  
