// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_SESSIONS_SESSION_DATA_TYPE_CONTROLLER_H_
#define CHROME_BROWSER_SYNC_SESSIONS_SESSION_DATA_TYPE_CONTROLLER_H_

#include "base/prefs/pref_change_registrar.h"
#include "components/sync_driver/local_device_info_provider.h"
#include "components/sync_driver/ui_data_type_controller.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class Profile;

namespace browser_sync {

class SyncedWindowDelegatesGetter;

class SessionDataTypeController : public sync_driver::UIDataTypeController,
                                  public content::NotificationObserver {
 public:
  SessionDataTypeController(sync_driver::SyncApiComponentFactory* factory,
                            Profile* profile,
                            SyncedWindowDelegatesGetter* synced_window_getter,
                            sync_driver::LocalDeviceInfoProvider* local_device);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual bool StartModels() OVERRIDE;
  virtual void StopModels() OVERRIDE;
  virtual bool ReadyForStart() const OVERRIDE;

 protected:
  virtual ~SessionDataTypeController();

 private:
  bool IsWaiting();
  void MaybeCompleteLoading();
  void OnLocalDeviceInfoInitialized();
  void OnSavingBrowserHistoryPrefChanged();

  Profile* const profile_;

  SyncedWindowDelegatesGetter* synced_window_getter_;
  content::NotificationRegistrar notification_registrar_;

  sync_driver::LocalDeviceInfoProvider* const local_device_;
  scoped_ptr<sync_driver::LocalDeviceInfoProvider::Subscription> subscription_;

  
  bool waiting_on_session_restore_;
  bool waiting_on_local_device_info_;

  PrefChangeRegistrar pref_registrar_;

  DISALLOW_COPY_AND_ASSIGN(SessionDataTypeController);
};

}  

#endif  
