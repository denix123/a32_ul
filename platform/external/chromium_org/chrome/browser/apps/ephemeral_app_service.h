// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_EPHEMERAL_APP_SERVICE_H_
#define CHROME_BROWSER_APPS_EPHEMERAL_APP_SERVICE_H_

#include <map>
#include <set>

#include "apps/app_lifetime_monitor.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "base/timer/timer.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"

class Profile;

namespace extensions {
class Extension;
class ExtensionRegistry;
}  

class EphemeralAppService : public KeyedService,
                            public content::NotificationObserver,
                            public extensions::ExtensionRegistryObserver,
                            public apps::AppLifetimeMonitor::Observer {
 public:
  
  
  static EphemeralAppService* Get(Profile* profile);

  explicit EphemeralAppService(Profile* profile);
  virtual ~EphemeralAppService();

  
  void ClearCachedApps();

  int ephemeral_app_count() const { return ephemeral_app_count_; }

  void set_disable_delay_for_test(int delay) {
    disable_idle_app_delay_ = delay;
  }

  

  
  static const int kAppInactiveThreshold;
  
  
  static const int kAppKeepThreshold;
  
  static const int kMaxEphemeralAppsCount;

 private:
  
  typedef std::multimap<base::Time, std::string> LaunchTimeAppMap;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionWillBeInstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      bool is_update,
      bool from_ephemeral,
      const std::string& old_name) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  virtual void OnAppStop(Profile* profile, const std::string& app_id) OVERRIDE;
  virtual void OnChromeTerminating() OVERRIDE;

  void Init();
  void InitEphemeralAppCount();

  void DisableEphemeralApp(const std::string& app_id);
  void DisableEphemeralAppsOnStartup();

  void HandleEphemeralAppPromoted(const extensions::Extension* app);

  
  void TriggerGarbageCollect(const base::TimeDelta& delay);
  void GarbageCollectApps();
  static void GetAppsToRemove(int app_count,
                              const LaunchTimeAppMap& app_launch_times,
                              std::set<std::string>* remove_app_ids);

  Profile* profile_;

  content::NotificationRegistrar registrar_;
  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;
  ScopedObserver<apps::AppLifetimeMonitor, apps::AppLifetimeMonitor::Observer>
      app_lifetime_monitor_observer_;

  base::OneShotTimer<EphemeralAppService> garbage_collect_apps_timer_;

  
  int ephemeral_app_count_;

  
  
  int disable_idle_app_delay_;

  base::WeakPtrFactory<EphemeralAppService> weak_ptr_factory_;

  friend class EphemeralAppServiceTest;
  friend class EphemeralAppServiceBrowserTest;

  DISALLOW_COPY_AND_ASSIGN(EphemeralAppService);
};

#endif  
