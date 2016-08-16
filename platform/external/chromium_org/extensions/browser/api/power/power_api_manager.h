// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_POWER_POWER_API_MANAGER_H_
#define EXTENSIONS_BROWSER_API_POWER_POWER_API_MANAGER_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/power_save_blocker.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/api/power.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class PowerApiManager : public BrowserContextKeyedAPI,
                        public extensions::ExtensionRegistryObserver {
 public:
  typedef base::Callback<scoped_ptr<content::PowerSaveBlocker>(
      content::PowerSaveBlocker::PowerSaveBlockerType,
      const std::string&)> CreateBlockerFunction;

  static PowerApiManager* Get(content::BrowserContext* context);

  
  static BrowserContextKeyedAPIFactory<PowerApiManager>* GetFactoryInstance();

  
  
  void AddRequest(const std::string& extension_id,
                  core_api::power::Level level);

  
  
  void RemoveRequest(const std::string& extension_id);

  
  
  void SetCreateBlockerFunctionForTesting(CreateBlockerFunction function);

  
  virtual void OnExtensionUnloaded(content::BrowserContext* browser_context,
                                   const Extension* extension,
                                   UnloadedExtensionInfo::Reason reason)
      OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<PowerApiManager>;

  explicit PowerApiManager(content::BrowserContext* context);
  virtual ~PowerApiManager();

  
  
  void UpdatePowerSaveBlocker();

  
  static const char* service_name() { return "PowerApiManager"; }
  static const bool kServiceRedirectedInIncognito = true;
  static const bool kServiceIsCreatedWithBrowserContext = false;
  virtual void Shutdown() OVERRIDE;

  content::BrowserContext* browser_context_;

  
  
  
  CreateBlockerFunction create_blocker_function_;

  scoped_ptr<content::PowerSaveBlocker> power_save_blocker_;

  
  
  core_api::power::Level current_level_;

  
  
  typedef std::map<std::string, core_api::power::Level> ExtensionLevelMap;
  ExtensionLevelMap extension_levels_;

  DISALLOW_COPY_AND_ASSIGN(PowerApiManager);
};

}  

#endif  
