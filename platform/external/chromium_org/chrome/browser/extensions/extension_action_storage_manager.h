// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ACTION_STORAGE_MANAGER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ACTION_STORAGE_MANAGER_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/extensions/api/extension_action/extension_action_api.h"
#include "extensions/browser/extension_registry_observer.h"

class ExtensionAction;

namespace content {
class BrowserContext;
}

namespace extensions {
class ExtensionRegistry;
class StateStore;

class ExtensionActionStorageManager : public ExtensionActionAPI::Observer,
                                      public ExtensionRegistryObserver {
 public:
  explicit ExtensionActionStorageManager(content::BrowserContext* context);
  virtual ~ExtensionActionStorageManager();

 private:
  
  virtual void OnExtensionActionUpdated(
      ExtensionAction* extension_action,
      content::WebContents* web_contents,
      content::BrowserContext* browser_context) OVERRIDE;
  virtual void OnExtensionActionAPIShuttingDown() OVERRIDE;

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;

  
  void WriteToStorage(ExtensionAction* extension_action);
  void ReadFromStorage(
      const std::string& extension_id, scoped_ptr<base::Value> value);

  
  
  StateStore* GetStateStore();

  content::BrowserContext* browser_context_;

  ScopedObserver<ExtensionActionAPI, ExtensionActionAPI::Observer>
      extension_action_observer_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  base::WeakPtrFactory<ExtensionActionStorageManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionActionStorageManager);
};

}  

#endif  
