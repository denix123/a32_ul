// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_BACKUP_ROLLBACK_CONTROLLER_H_
#define CHROME_BROWSER_SYNC_BACKUP_ROLLBACK_CONTROLLER_H_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"

class SupervisedUserSigninManagerWrapper;

namespace sync_driver {
class SyncPrefs;
}

namespace browser_sync {

class BackupRollbackController {
 public:
  BackupRollbackController(sync_driver::SyncPrefs* sync_prefs,
                           const SupervisedUserSigninManagerWrapper* signin,
                           base::Closure start_backup,
                           base::Closure start_rollback);
  ~BackupRollbackController();

  
  
  bool StartBackup();

  
  
  bool StartRollback();

  
  void OnRollbackReceived();

  
  void OnRollbackDone();

  
  static bool IsBackupEnabled();

 private:
  sync_driver::SyncPrefs* sync_prefs_;

  
  
  const SupervisedUserSigninManagerWrapper* signin_;

  base::Closure start_backup_;
  base::Closure start_rollback_;

  DISALLOW_COPY_AND_ASSIGN(BackupRollbackController);
};

}  

#endif  
