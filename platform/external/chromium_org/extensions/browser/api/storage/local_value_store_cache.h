// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_STORAGE_LOCAL_VALUE_STORE_CACHE_H_
#define EXTENSIONS_BROWSER_API_STORAGE_LOCAL_VALUE_STORE_CACHE_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/browser/api/storage/settings_storage_quota_enforcer.h"
#include "extensions/browser/api/storage/value_store_cache.h"

namespace extensions {

class SettingsStorageFactory;

class LocalValueStoreCache : public ValueStoreCache {
 public:
  LocalValueStoreCache(const scoped_refptr<SettingsStorageFactory>& factory,
                       const base::FilePath& profile_path);
  virtual ~LocalValueStoreCache();

  
  virtual void RunWithValueStoreForExtension(
      const StorageCallback& callback,
      scoped_refptr<const Extension> extension) OVERRIDE;
  virtual void DeleteStorageSoon(const std::string& extension_id) OVERRIDE;

 private:
  typedef std::map<std::string, linked_ptr<ValueStore> > StorageMap;

  ValueStore* GetStorage(scoped_refptr<const Extension> extension);

  
  const scoped_refptr<SettingsStorageFactory> storage_factory_;

  
  const base::FilePath extension_base_path_;

  
  const base::FilePath app_base_path_;

  
  const SettingsStorageQuotaEnforcer::Limits quota_;

  
  StorageMap storage_map_;

  DISALLOW_COPY_AND_ASSIGN(LocalValueStoreCache);
};

}  

#endif  
