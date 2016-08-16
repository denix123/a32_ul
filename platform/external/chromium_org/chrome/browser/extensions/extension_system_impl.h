// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_SYSTEM_IMPL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_SYSTEM_IMPL_H_

#include "base/memory/scoped_vector.h"
#include "extensions/browser/extension_system.h"
#include "extensions/common/one_shot_event.h"

class Profile;

namespace extensions {

class ContentVerifier;
class DeclarativeUserScriptMaster;
class ExtensionSystemSharedFactory;
class ExtensionWarningBadgeService;
class NavigationObserver;
class SharedUserScriptMaster;
class StateStoreNotificationObserver;

class ExtensionSystemImpl : public ExtensionSystem {
 public:
  explicit ExtensionSystemImpl(Profile* profile);
  virtual ~ExtensionSystemImpl();

  
  virtual void Shutdown() OVERRIDE;

  virtual void InitForRegularProfile(bool extensions_enabled) OVERRIDE;

  virtual ExtensionService* extension_service() OVERRIDE;  
  virtual RuntimeData* runtime_data() OVERRIDE;  
  virtual ManagementPolicy* management_policy() OVERRIDE;  
  
  virtual SharedUserScriptMaster* shared_user_script_master() OVERRIDE;
  virtual ProcessManager* process_manager() OVERRIDE;
  virtual StateStore* state_store() OVERRIDE;  
  virtual StateStore* rules_store() OVERRIDE;  
  virtual LazyBackgroundTaskQueue* lazy_background_task_queue()
      OVERRIDE;  
  virtual InfoMap* info_map() OVERRIDE; 
  virtual EventRouter* event_router() OVERRIDE;  
  virtual WarningService* warning_service() OVERRIDE;
  virtual Blacklist* blacklist() OVERRIDE;  
  virtual ErrorConsole* error_console() OVERRIDE;
  virtual InstallVerifier* install_verifier() OVERRIDE;
  virtual QuotaService* quota_service() OVERRIDE;  

  virtual void RegisterExtensionWithRequestContexts(
      const Extension* extension) OVERRIDE;

  virtual void UnregisterExtensionWithRequestContexts(
      const std::string& extension_id,
      const UnloadedExtensionInfo::Reason reason) OVERRIDE;

  virtual const OneShotEvent& ready() const OVERRIDE;
  virtual ContentVerifier* content_verifier() OVERRIDE;  
  virtual scoped_ptr<ExtensionSet> GetDependentExtensions(
      const Extension* extension) OVERRIDE;

  virtual DeclarativeUserScriptMaster*
      GetDeclarativeUserScriptMasterByExtension(
          const ExtensionId& extension_id) OVERRIDE;  

 private:
  friend class ExtensionSystemSharedFactory;

  
  
  class Shared : public KeyedService {
   public:
    explicit Shared(Profile* profile);
    virtual ~Shared();

    
    virtual void InitPrefs();
    
    void RegisterManagementPolicyProviders();
    void Init(bool extensions_enabled);

    
    virtual void Shutdown() OVERRIDE;

    StateStore* state_store();
    StateStore* rules_store();
    ExtensionService* extension_service();
    RuntimeData* runtime_data();
    ManagementPolicy* management_policy();
    SharedUserScriptMaster* shared_user_script_master();
    Blacklist* blacklist();
    InfoMap* info_map();
    LazyBackgroundTaskQueue* lazy_background_task_queue();
    EventRouter* event_router();
    WarningService* warning_service();
    ErrorConsole* error_console();
    InstallVerifier* install_verifier();
    QuotaService* quota_service();
    const OneShotEvent& ready() const { return ready_; }
    ContentVerifier* content_verifier();

    DeclarativeUserScriptMaster* GetDeclarativeUserScriptMasterByExtension(
        const ExtensionId& extension_id);

   private:
    Profile* profile_;

    

    scoped_ptr<StateStore> state_store_;
    scoped_ptr<StateStoreNotificationObserver>
        state_store_notification_observer_;
    scoped_ptr<StateStore> rules_store_;
    
    
    scoped_ptr<LazyBackgroundTaskQueue> lazy_background_task_queue_;
    scoped_ptr<EventRouter> event_router_;
    scoped_ptr<NavigationObserver> navigation_observer_;
    
    
    scoped_ptr<SharedUserScriptMaster> shared_user_script_master_;
    
    
    
    ScopedVector<DeclarativeUserScriptMaster> declarative_user_script_masters_;
    scoped_ptr<Blacklist> blacklist_;
    scoped_ptr<RuntimeData> runtime_data_;
    
    scoped_ptr<ExtensionService> extension_service_;
    scoped_ptr<ManagementPolicy> management_policy_;
    
    scoped_refptr<InfoMap> extension_info_map_;
    scoped_ptr<WarningService> warning_service_;
    scoped_ptr<ExtensionWarningBadgeService> extension_warning_badge_service_;
    scoped_ptr<ErrorConsole> error_console_;
    scoped_ptr<InstallVerifier> install_verifier_;
    scoped_ptr<QuotaService> quota_service_;

    
    scoped_refptr<ContentVerifier> content_verifier_;

#if defined(OS_CHROMEOS)
    scoped_ptr<chromeos::DeviceLocalAccountManagementPolicyProvider>
        device_local_account_management_policy_provider_;
#endif

    OneShotEvent ready_;
  };

  Profile* profile_;

  Shared* shared_;

  
  
  
  
  scoped_ptr<ProcessManager> process_manager_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionSystemImpl);
};

}  

#endif  
