// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_STARTUP_CONTROLLER_H_
#define CHROME_BROWSER_SYNC_STARTUP_CONTROLLER_H_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "sync/internal_api/public/base/model_type.h"

class ProfileOAuth2TokenService;
class SupervisedUserSigninManagerWrapper;

namespace sync_driver {
class SyncPrefs;
}

namespace browser_sync {

enum ProfileSyncServiceStartBehavior {
  AUTO_START,
  MANUAL_START,
};

class StartupController {
 public:
  StartupController(ProfileSyncServiceStartBehavior start_behavior,
                    const ProfileOAuth2TokenService* token_service,
                    const sync_driver::SyncPrefs* sync_prefs,
                    const SupervisedUserSigninManagerWrapper* signin,
                    base::Closure start_backend);
  ~StartupController();

  
  
  
  bool TryStart();

  
  
  
  
  
  void OnDataTypeRequestsSyncStartup(syncer::ModelType type);

  
  
  
  
  
  
  void Reset(const syncer::ModelTypeSet registered_types);

  void set_setup_in_progress(bool in_progress);
  bool setup_in_progress() const { return setup_in_progress_; }
  bool auto_start_enabled() const { return auto_start_enabled_; }
  base::Time start_backend_time() const { return start_backend_time_; }
  std::string GetBackendInitializationStateString() const;

  void OverrideFallbackTimeoutForTest(const base::TimeDelta& timeout);
 private:
  enum StartUpDeferredOption {
    STARTUP_BACKEND_DEFERRED,
    STARTUP_IMMEDIATE
  };
  
  bool StartUp(StartUpDeferredOption deferred_option);
  void OnFallbackStartupTimerExpired();

  
  void RecordTimeDeferred();

  
  
  bool received_start_request_;

  
  
  
  base::Time start_up_time_;

  
  
  
  
  
  bool setup_in_progress_;

  
  
  
  
  const bool auto_start_enabled_;

  const sync_driver::SyncPrefs* sync_prefs_;

  const ProfileOAuth2TokenService* token_service_;

  const SupervisedUserSigninManagerWrapper* signin_;

  
  
  base::Closure start_backend_;

  
  base::Time start_backend_time_;

  base::TimeDelta fallback_timeout_;

  
  syncer::ModelTypeSet registered_types_;

  
  bool first_start_;

  base::WeakPtrFactory<StartupController> weak_factory_;
};

}  

#endif  
