// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_STORAGE_SETTINGS_STORAGE_FACTORY_H_
#define EXTENSIONS_BROWSER_API_STORAGE_SETTINGS_STORAGE_FACTORY_H_

#include <string>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"

class ValueStore;

namespace extensions {

class SettingsStorageFactory
    : public base::RefCountedThreadSafe<SettingsStorageFactory> {
 public:
  
  
  virtual ValueStore* Create(const base::FilePath& base_path,
                             const std::string& extension_id) = 0;

  
  
  
  virtual void DeleteDatabaseIfExists(const base::FilePath& base_path,
                                      const std::string& extension_id) = 0;

 protected:
  friend class base::RefCountedThreadSafe<SettingsStorageFactory>;
  virtual ~SettingsStorageFactory() {}
};

}  

#endif  
