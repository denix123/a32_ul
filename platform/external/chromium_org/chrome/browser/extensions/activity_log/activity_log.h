// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_ACTIVITY_LOG_ACTIVITY_LOG_H_
#define CHROME_BROWSER_EXTENSIONS_ACTIVITY_LOG_ACTIVITY_LOG_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/observer_list_threadsafe.h"
#include "base/scoped_observer.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread.h"
#include "chrome/browser/extensions/activity_log/activity_actions.h"
#include "chrome/browser/extensions/activity_log/activity_log_policy.h"
#include "extensions/browser/api_activity_monitor.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/browser/script_execution_observer.h"
#include "extensions/common/dom_action_types.h"

class Profile;

namespace content {
class BrowserContext;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace extensions {
class Extension;
class ExtensionRegistry;

class ActivityLog : public BrowserContextKeyedAPI,
                    public ApiActivityMonitor,
                    public ScriptExecutionObserver,
                    public ExtensionRegistryObserver {
 public:
  
  
  class Observer {
   public:
    virtual void OnExtensionActivity(scoped_refptr<Action> activity) = 0;
  };

  static BrowserContextKeyedAPIFactory<ActivityLog>* GetFactoryInstance();

  
  
  static ActivityLog* GetInstance(content::BrowserContext* context);

  
  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  
  void LogAction(scoped_refptr<Action> action);

  
  
  
  
  void GetFilteredActions(
      const std::string& extension_id,
      const Action::ActionType type,
      const std::string& api_name,
      const std::string& page_url,
      const std::string& arg_url,
      const int days_ago,
      const base::Callback
          <void(scoped_ptr<std::vector<scoped_refptr<Action> > >)>& callback);

  
  
  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  virtual void OnApiEventDispatched(
      const std::string& extension_id,
      const std::string& event_name,
      scoped_ptr<base::ListValue> event_args) OVERRIDE;
  virtual void OnApiFunctionCalled(
      const std::string& extension_id,
      const std::string& api_name,
      scoped_ptr<base::ListValue> event_args) OVERRIDE;

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  void RemoveActions(const std::vector<int64>& action_ids);

  
  
  
  void RemoveURLs(const std::vector<GURL>& restrict_urls);
  void RemoveURLs(const std::set<GURL>& restrict_urls);
  void RemoveURL(const GURL& url);

  
  void DeleteDatabase();

  
  
  void SetWatchdogAppActiveForTesting(bool active);

 private:
  friend class ActivityLogTest;
  friend class BrowserContextKeyedAPIFactory<ActivityLog>;

  explicit ActivityLog(content::BrowserContext* context);
  virtual ~ActivityLog();

  
  
  bool IsWatchdogAppActive();

  
  
  
  bool IsDatabaseEnabled();

  
  
  void StartObserving();

  
  
  virtual void OnScriptsExecuted(
      const content::WebContents* web_contents,
      const ExecutingScriptsMap& extension_ids,
      const GURL& on_url) OVERRIDE;

  
  
  
  
  void ChooseDatabasePolicy();
  void SetDatabasePolicy(ActivityLogPolicy::PolicyType policy_type);

  
  static const char* service_name() { return "ActivityLog"; }
  static const bool kServiceRedirectedInIncognito = true;
  static const bool kServiceIsCreatedWithBrowserContext = false;

  typedef ObserverListThreadSafe<Observer> ObserverList;
  scoped_refptr<ObserverList> observers_;

  
  
  
  

  
  
  
  ActivityLogDatabasePolicy* database_policy_;
  ActivityLogPolicy::PolicyType database_policy_type_;

  
  
  ActivityLogPolicy* uma_policy_;

  Profile* profile_;
  bool db_enabled_;  
  
  
  
  
  
  bool testing_mode_;
  
  
  
  
  bool has_threads_;

  
  
  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;

  
  
  
  int watchdog_apps_active_;

  FRIEND_TEST_ALL_PREFIXES(ActivityLogApiTest, TriggerEvent);
  FRIEND_TEST_ALL_PREFIXES(ActivityLogEnabledTest, AppAndCommandLine);
  FRIEND_TEST_ALL_PREFIXES(ActivityLogEnabledTest, CommandLineSwitch);
  FRIEND_TEST_ALL_PREFIXES(ActivityLogEnabledTest, NoSwitch);
  FRIEND_TEST_ALL_PREFIXES(ActivityLogEnabledTest, PrefSwitch);
  FRIEND_TEST_ALL_PREFIXES(ActivityLogEnabledTest, WatchdogSwitch);
  DISALLOW_COPY_AND_ASSIGN(ActivityLog);
};

template <>
void BrowserContextKeyedAPIFactory<ActivityLog>::DeclareFactoryDependencies();

}  

#endif  
