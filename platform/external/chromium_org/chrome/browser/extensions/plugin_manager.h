// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_PLUGIN_MANAGER_H_
#define CHROME_BROWSER_EXTENSIONS_PLUGIN_MANAGER_H_

#include <set>
#include <string>

#include "base/scoped_observer.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/manifest_handlers/nacl_modules_handler.h"

class GURL;
class Profile;

namespace content {
class BrowserContext;
}

namespace extensions {
class ExtensionRegistry;

class PluginManager : public BrowserContextKeyedAPI,
                      public ExtensionRegistryObserver {
 public:
  explicit PluginManager(content::BrowserContext* context);
  virtual ~PluginManager();

  
  static BrowserContextKeyedAPIFactory<PluginManager>* GetFactoryInstance();

 private:
  friend class BrowserContextKeyedAPIFactory<PluginManager>;

#if !defined(DISABLE_NACL)

  
  
  
  
  
  
  void RegisterNaClModule(const NaClModuleInfo& info);
  void UnregisterNaClModule(const NaClModuleInfo& info);

  
  
  void UpdatePluginListWithNaClModules();

  extensions::NaClModuleInfo::List::iterator FindNaClModule(const GURL& url);

#endif  

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  static const char* service_name() { return "PluginManager"; }
  static const bool kServiceIsNULLWhileTesting = true;

  extensions::NaClModuleInfo::List nacl_module_list_;

  Profile* profile_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;
};

}  

#endif  
