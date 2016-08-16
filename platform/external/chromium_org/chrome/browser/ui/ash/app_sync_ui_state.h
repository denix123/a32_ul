// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_APP_SYNC_UI_STATE_H_
#define CHROME_BROWSER_UI_ASH_APP_SYNC_UI_STATE_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/observer_list.h"
#include "base/timer/timer.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"

class AppSyncUIStateObserver;
class Profile;
class ProfileSyncService;

namespace extensions {
class ExtensionRegistry;
}

class AppSyncUIState : public KeyedService,
                       public ProfileSyncServiceObserver,
                       public extensions::ExtensionRegistryObserver {
 public:
  enum Status {
    STATUS_NORMAL,
    STATUS_SYNCING,    
    STATUS_TIMED_OUT,  
  };

  
  
  
  static AppSyncUIState* Get(Profile* profile);

  
  static bool ShouldObserveAppSyncForProfile(Profile* profile);

  explicit AppSyncUIState(Profile* profile);
  virtual ~AppSyncUIState();

  void AddObserver(AppSyncUIStateObserver* observer);
  void RemoveObserver(AppSyncUIStateObserver* observer);

  Status status() const { return status_; }

 private:
  void StartObserving();
  void StopObserving();

  void SetStatus(Status status);

  
  
  
  void CheckAppSync();

  
  void OnMaxSyncingTimer();

  
  virtual void OnStateChanged() OVERRIDE;

  
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;

  Profile* profile_;
  ProfileSyncService* sync_service_;

  
  base::OneShotTimer<AppSyncUIState> max_syncing_status_timer_;

  Status status_;
  ObserverList<AppSyncUIStateObserver> observers_;

  extensions::ExtensionRegistry* extension_registry_;

  DISALLOW_COPY_AND_ASSIGN(AppSyncUIState);
};

#endif  
