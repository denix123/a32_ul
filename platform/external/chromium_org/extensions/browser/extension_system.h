// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_SYSTEM_H_
#define EXTENSIONS_BROWSER_EXTENSION_SYSTEM_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/common/extension.h"

class ExtensionService;

#if defined(OS_CHROMEOS)
namespace chromeos {
class DeviceLocalAccountManagementPolicyProvider;
}
#endif  

namespace content {
class BrowserContext;
}

namespace extensions {

class Blacklist;
class ContentVerifier;
class DeclarativeUserScriptMaster;
class ErrorConsole;
class EventRouter;
class Extension;
class ExtensionSet;
class InfoMap;
class InstallVerifier;
class LazyBackgroundTaskQueue;
class ManagementPolicy;
class OneShotEvent;
class ProcessManager;
class QuotaService;
class RuntimeData;
class SharedUserScriptMaster;
class StateStore;
class WarningService;

class ExtensionSystem : public KeyedService {
 public:
  ExtensionSystem();
  virtual ~ExtensionSystem();

  
  static ExtensionSystem* Get(content::BrowserContext* context);

  
  
  
  virtual void InitForRegularProfile(bool extensions_enabled) = 0;

  
  virtual ExtensionService* extension_service() = 0;

  
  
  virtual RuntimeData* runtime_data() = 0;

  
  
  
  virtual ManagementPolicy* management_policy() = 0;

  
  virtual SharedUserScriptMaster* shared_user_script_master() = 0;

  
  virtual ProcessManager* process_manager() = 0;

  
  virtual StateStore* state_store() = 0;

  
  virtual StateStore* rules_store() = 0;

  
  virtual InfoMap* info_map() = 0;

  
  virtual LazyBackgroundTaskQueue* lazy_background_task_queue() = 0;

  
  virtual EventRouter* event_router() = 0;

  
  virtual WarningService* warning_service() = 0;

  
  virtual Blacklist* blacklist() = 0;

  
  virtual ErrorConsole* error_console() = 0;

  
  virtual InstallVerifier* install_verifier() = 0;

  
  
  virtual QuotaService* quota_service() = 0;

  
  
  
  
  
  virtual void RegisterExtensionWithRequestContexts(
      const Extension* extension) {}

  
  
  
  virtual void UnregisterExtensionWithRequestContexts(
      const std::string& extension_id,
      const UnloadedExtensionInfo::Reason reason) {}

  
  virtual const OneShotEvent& ready() const = 0;

  
  virtual ContentVerifier* content_verifier() = 0;

  
  
  
  virtual scoped_ptr<ExtensionSet> GetDependentExtensions(
      const Extension* extension) = 0;

  
  virtual DeclarativeUserScriptMaster*
      GetDeclarativeUserScriptMasterByExtension(
          const ExtensionId& extension_id) = 0;
};

}  

#endif  
