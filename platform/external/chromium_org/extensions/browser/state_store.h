// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_STATE_STORE_H_
#define EXTENSIONS_BROWSER_STATE_STORE_H_

#include <set>
#include <string>

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/browser/value_store/value_store_frontend.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class ExtensionRegistry;

class StateStore : public base::SupportsWeakPtr<StateStore>,
                   public ExtensionRegistryObserver,
                   public content::NotificationObserver {
 public:
  typedef ValueStoreFrontend::ReadCallback ReadCallback;

  
  
  StateStore(content::BrowserContext* context,
             const base::FilePath& db_path,
             bool deferred_load);
  
  StateStore(content::BrowserContext* context, scoped_ptr<ValueStore> store);
  virtual ~StateStore();

  
  
  
  void RequestInitAfterDelay();

  
  
  void RegisterKey(const std::string& key);

  
  
  void GetExtensionValue(const std::string& extension_id,
                         const std::string& key,
                         ReadCallback callback);

  
  void SetExtensionValue(const std::string& extension_id,
                         const std::string& key,
                         scoped_ptr<base::Value> value);

  
  void RemoveExtensionValue(const std::string& extension_id,
                            const std::string& key);

  
  bool IsInitialized() const;

 private:
  class DelayedTaskQueue;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  void Init();

  
  
  void InitAfterDelay();

  
  void RemoveKeysForExtension(const std::string& extension_id);

  
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;
  virtual void OnExtensionWillBeInstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      bool is_update,
      bool from_ephemeral,
      const std::string& old_name) OVERRIDE;

  
  base::FilePath db_path_;

  
  ValueStoreFrontend store_;

  
  
  std::set<std::string> registered_keys_;

  
  scoped_ptr<DelayedTaskQueue> task_queue_;

  content::NotificationRegistrar registrar_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;
};

}  

#endif  
