// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_STORAGE_STORAGE_FRONTEND_H_
#define EXTENSIONS_BROWSER_API_STORAGE_STORAGE_FRONTEND_H_

#include <map>
#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/browser/api/storage/settings_namespace.h"
#include "extensions/browser/api/storage/settings_observer.h"
#include "extensions/browser/api/storage/settings_storage_factory.h"
#include "extensions/browser/api/storage/value_store_cache.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class StorageFrontend : public BrowserContextKeyedAPI {
 public:
  
  static StorageFrontend* Get(content::BrowserContext* context);

  
  static StorageFrontend* CreateForTesting(
      const scoped_refptr<SettingsStorageFactory>& storage_factory,
      content::BrowserContext* context);

  
  virtual ~StorageFrontend();

  
  ValueStoreCache* GetValueStoreCache(
      settings_namespace::Namespace settings_namespace) const;

  
  bool IsStorageEnabled(settings_namespace::Namespace settings_namespace) const;

  
  
  void RunWithStorage(scoped_refptr<const Extension> extension,
                      settings_namespace::Namespace settings_namespace,
                      const ValueStoreCache::StorageCallback& callback);

  
  void DeleteStorageSoon(const std::string& extension_id);

  
  scoped_refptr<SettingsObserverList> GetObservers();

  void DisableStorageForTesting(
      settings_namespace::Namespace settings_namespace);

  
  static BrowserContextKeyedAPIFactory<StorageFrontend>* GetFactoryInstance();
  static const char* service_name();
  static const bool kServiceRedirectedInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

 private:
  friend class BrowserContextKeyedAPIFactory<StorageFrontend>;

  typedef std::map<settings_namespace::Namespace, ValueStoreCache*> CacheMap;

  
  explicit StorageFrontend(content::BrowserContext* context);

  
  StorageFrontend(const scoped_refptr<SettingsStorageFactory>& storage_factory,
                  content::BrowserContext* context);

  void Init(const scoped_refptr<SettingsStorageFactory>& storage_factory);

  
  content::BrowserContext* const browser_context_;

  
  scoped_refptr<SettingsObserverList> observers_;

  
  scoped_ptr<SettingsObserver> browser_context_observer_;

  
  
  CacheMap caches_;

  DISALLOW_COPY_AND_ASSIGN(StorageFrontend);
};

}  

#endif  
