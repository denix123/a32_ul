// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_STORAGE_SETTINGS_TEST_UTIL_H_
#define EXTENSIONS_BROWSER_API_STORAGE_SETTINGS_TEST_UTIL_H_

#include <set>
#include <string>

#include "base/compiler_specific.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/test/base/testing_profile.h"
#include "extensions/browser/api/storage/settings_namespace.h"
#include "extensions/browser/api/storage/settings_storage_factory.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/mock_extension_system.h"
#include "extensions/common/extension.h"

class ValueStore;

namespace extensions {

class StorageFrontend;
namespace settings_test_util {

scoped_ptr<base::Value> CreateKilobyte();

scoped_ptr<base::Value> CreateMegabyte();

ValueStore* GetStorage(scoped_refptr<const Extension> extension,
                       settings_namespace::Namespace setting_namespace,
                       StorageFrontend* frontend);

ValueStore* GetStorage(scoped_refptr<const Extension> extension,
                       StorageFrontend* frontend);

scoped_refptr<const Extension> AddExtensionWithId(
    content::BrowserContext* context,
    const std::string& id,
    Manifest::Type type);

scoped_refptr<const Extension> AddExtensionWithIdAndPermissions(
    content::BrowserContext* context,
    const std::string& id,
    Manifest::Type type,
    const std::set<std::string>& permissions);

class MockExtensionSystemWithEventRouter : public MockExtensionSystem {
 public:
  explicit MockExtensionSystemWithEventRouter(content::BrowserContext* context);
  virtual ~MockExtensionSystemWithEventRouter();

  
  static KeyedService* Build(content::BrowserContext* context);

  
  virtual EventRouter* event_router() OVERRIDE;

 private:
  scoped_ptr<EventRouter> event_router_;

  DISALLOW_COPY_AND_ASSIGN(MockExtensionSystemWithEventRouter);
};

class ScopedSettingsStorageFactory : public SettingsStorageFactory {
 public:
  ScopedSettingsStorageFactory();

  explicit ScopedSettingsStorageFactory(
      const scoped_refptr<SettingsStorageFactory>& delegate);

  
  void Reset(const scoped_refptr<SettingsStorageFactory>& delegate);

  
  virtual ValueStore* Create(const base::FilePath& base_path,
                             const std::string& extension_id) OVERRIDE;
  virtual void DeleteDatabaseIfExists(
      const base::FilePath& base_path,
      const std::string& extension_id) OVERRIDE;

 private:
  
  virtual ~ScopedSettingsStorageFactory();

  scoped_refptr<SettingsStorageFactory> delegate_;
};

}  

}  

#endif  
