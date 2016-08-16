// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_ENROLLMENT_AUTO_ENROLLMENT_CONTROLLER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_ENROLLMENT_AUTO_ENROLLMENT_CONTROLLER_H_

#include <string>
#include <vector>

#include "base/callback_list.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/policy/auto_enrollment_client.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"

namespace policy {
class ServerBackedStateKeysBroker;
}

namespace chromeos {

class AutoEnrollmentController {
 public:
  typedef base::CallbackList<void(policy::AutoEnrollmentState)>
      ProgressCallbackList;

  
  static const char kForcedReEnrollmentAlways[];
  static const char kForcedReEnrollmentLegacy[];
  static const char kForcedReEnrollmentNever[];
  static const char kForcedReEnrollmentOfficialBuild[];

  
  enum Mode {
    
    MODE_NONE,
    
    MODE_LEGACY_AUTO_ENROLLMENT,
    
    MODE_FORCED_RE_ENROLLMENT,
  };

  
  
  static Mode GetMode();

  AutoEnrollmentController();
  ~AutoEnrollmentController();

  
  void Start();

  
  void Cancel();

  
  void Retry();

  
  scoped_ptr<ProgressCallbackList::Subscription> RegisterProgressCallback(
      const ProgressCallbackList::CallbackType& callback);

  
  bool ShouldEnrollSilently();

  policy::AutoEnrollmentState state() const { return state_; }

 private:
  
  void OnOwnershipStatusCheckDone(
      DeviceSettingsService::OwnershipStatus status);

  
  void StartClient(const std::vector<std::string>& state_keys, bool first_boot);

  
  void UpdateState(policy::AutoEnrollmentState state);

  policy::AutoEnrollmentState state_;
  ProgressCallbackList progress_callbacks_;

  scoped_ptr<policy::AutoEnrollmentClient> client_;

  base::WeakPtrFactory<AutoEnrollmentController> client_start_weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AutoEnrollmentController);
};

}  

#endif  
