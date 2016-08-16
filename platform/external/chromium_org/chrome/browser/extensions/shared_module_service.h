// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_SHARED_MODULE_SERVICE_H_
#define CHROME_BROWSER_EXTENSIONS_SHARED_MODULE_SERVICE_H_

#include <list>

#include "base/scoped_observer.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/manifest_handlers/shared_module_info.h"

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;
class ExtensionSet;
class ExtensionRegistry;

class SharedModuleService : public ExtensionRegistryObserver {
 public:
  enum ImportStatus {
    
    IMPORT_STATUS_OK,

    
    
    IMPORT_STATUS_UNSATISFIED,

    
    
    IMPORT_STATUS_UNRECOVERABLE
  };

  explicit SharedModuleService(content::BrowserContext* context);
  virtual ~SharedModuleService();

  
  
  
  ImportStatus CheckImports(
      const Extension* extension,
      std::list<SharedModuleInfo::ImportInfo>* missing_modules,
      std::list<SharedModuleInfo::ImportInfo>* outdated_modules);

  
  
  
  ImportStatus SatisfyImports(const Extension* extension);

  
  scoped_ptr<ExtensionSet> GetDependentExtensions(const Extension* extension);

 private:
  
  void PruneSharedModules();

  
  virtual void OnExtensionInstalled(content::BrowserContext* browser_context,
                                    const Extension* extension,
                                    bool is_update) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  
  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(SharedModuleService);
};

}  

#endif  
