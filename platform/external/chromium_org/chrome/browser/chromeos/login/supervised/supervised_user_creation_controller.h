// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_CONTROLLER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_CONTROLLER_H_

#include <string>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "chrome/browser/chromeos/login/supervised/supervised_user_authenticator.h"
#include "chrome/browser/supervised_user/supervised_user_registration_utility.h"

class Profile;

namespace chromeos {

class SupervisedUserCreationController {
 public:
  
  
  
  static const int kDummyAvatarIndex;

  enum ErrorCode {
    NO_ERROR,
    CRYPTOHOME_NO_MOUNT,
    CRYPTOHOME_FAILED_MOUNT,
    CRYPTOHOME_FAILED_TPM,
    CLOUD_SERVER_ERROR,
    TOKEN_WRITE_FAILED,
  };

  class StatusConsumer {
   public:
    virtual ~StatusConsumer();

    virtual void OnCreationError(ErrorCode code) = 0;
    virtual void OnLongCreationWarning() = 0;
    virtual void OnCreationTimeout() = 0;
    virtual void OnCreationSuccess() = 0;
  };

  
  
  
  explicit SupervisedUserCreationController(StatusConsumer* consumer);
  virtual ~SupervisedUserCreationController();

  
  static SupervisedUserCreationController* current_controller() {
    return current_controller_;
  }

  
  
  
  virtual void StartCreation(const base::string16& display_name,
                             const std::string& password,
                             int avatar_index) = 0;

  
  
  
  virtual void StartImport(const base::string16& display_name,
                           const std::string& password,
                           int avatar_index,
                           const std::string& sync_id,
                           const std::string& master_key) = 0;

  
  
  
  
  
  virtual void StartImport(const base::string16& display_name,
                           int avatar_index,
                           const std::string& sync_id,
                           const std::string& master_key,
                           const base::DictionaryValue* password_data,
                           const std::string& encryption_key,
                           const std::string& signature_key) = 0;

  virtual void SetManagerProfile(Profile* manager_profile) = 0;
  virtual Profile* GetManagerProfile() = 0;
  virtual void CancelCreation() = 0;
  virtual void FinishCreation() = 0;
  virtual std::string GetSupervisedUserId() = 0;

 protected:
  
  
  static SupervisedUserCreationController* current_controller_;

  StatusConsumer* consumer_;

 private:
  DISALLOW_COPY_AND_ASSIGN(SupervisedUserCreationController);
};

}  

#endif  
