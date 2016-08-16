// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_HISTORY_DELETE_DIRECTIVES_DATA_TYPE_CONTROLLER_H_
#define CHROME_BROWSER_SYNC_GLUE_HISTORY_DELETE_DIRECTIVES_DATA_TYPE_CONTROLLER_H_

#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "components/sync_driver/local_device_info_provider.h"
#include "components/sync_driver/ui_data_type_controller.h"

class Profile;
class ProfileSyncService;

namespace browser_sync {

class HistoryDeleteDirectivesDataTypeController
    : public sync_driver::UIDataTypeController,
      public ProfileSyncServiceObserver {
 public:
  HistoryDeleteDirectivesDataTypeController(
      sync_driver::SyncApiComponentFactory* factory,
      ProfileSyncService* sync_service);

  
  virtual bool ReadyForStart() const OVERRIDE;
  virtual bool StartModels() OVERRIDE;
  virtual void StopModels() OVERRIDE;

  
  virtual void OnStateChanged() OVERRIDE;

 private:
  
  virtual ~HistoryDeleteDirectivesDataTypeController();

  
  
  bool DisableTypeIfNecessary();

  ProfileSyncService* sync_service_;

  DISALLOW_COPY_AND_ASSIGN(HistoryDeleteDirectivesDataTypeController);
};

}  

#endif  
