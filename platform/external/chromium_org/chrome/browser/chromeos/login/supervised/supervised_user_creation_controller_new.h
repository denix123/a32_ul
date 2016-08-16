// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_CONTROLLER_NEW_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_CONTROLLER_NEW_H_

#include <string>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "chrome/browser/chromeos/login/supervised/supervised_user_creation_controller.h"
#include "chrome/browser/supervised_user/supervised_user_registration_utility.h"
#include "chromeos/login/auth/extended_authenticator.h"

class Profile;

namespace chromeos {

class UserContext;

class SupervisedUserCreationControllerNew
    : public SupervisedUserCreationController,
      public ExtendedAuthenticator::NewAuthStatusConsumer {
 public:
  
  
  
  SupervisedUserCreationControllerNew(StatusConsumer* consumer,
                                      const std::string& manager_id);
  virtual ~SupervisedUserCreationControllerNew();

  
  static SupervisedUserCreationControllerNew* current_controller() {
    return current_controller_;
  }

  
  
  
  virtual void StartCreation(const base::string16& display_name,
                             const std::string& password,
                             int avatar_index) OVERRIDE;

  
  
  
  
  
  virtual void StartImport(const base::string16& display_name,
                           const std::string& password,
                           int avatar_index,
                           const std::string& sync_id,
                           const std::string& master_key) OVERRIDE;

  
  
  
  
  
  virtual void StartImport(const base::string16& display_name,
                           int avatar_index,
                           const std::string& sync_id,
                           const std::string& master_key,
                           const base::DictionaryValue* password_data,
                           const std::string& encryption_key,
                           const std::string& signature_key) OVERRIDE;

  virtual void SetManagerProfile(Profile* manager_profile) OVERRIDE;
  virtual Profile* GetManagerProfile() OVERRIDE;

  virtual void CancelCreation() OVERRIDE;
  virtual void FinishCreation() OVERRIDE;
  virtual std::string GetSupervisedUserId() OVERRIDE;

 private:
  enum Stage {
    
    STAGE_INITIAL,

    
    TRANSACTION_STARTED,
    
    KEYS_GENERATED,
    
    CRYPTOHOME_CREATED,
    
    DASHBOARD_CREATED,
    // Managed user's sync token is written.
    TOKEN_WRITTEN,
    
    TRANSACTION_COMMITTED,
    
    STAGE_ERROR,
  };

  
  enum CreationType { NEW_USER, USER_IMPORT_OLD, USER_IMPORT_NEW, };

  
  struct UserCreationContext {
    UserCreationContext();
    ~UserCreationContext();

    base::string16 display_name;
    int avatar_index;

    std::string manager_id;

    std::string local_user_id;  
    std::string sync_user_id;   

    
    std::string master_key;       
    std::string signature_key;    
    std::string encryption_key;   
    std::string salted_password;  

    std::string password;

    std::string salted_master_key;  
    std::string mount_hash;

    std::string token;

    CreationType creation_type;

    base::DictionaryValue password_data;

    Profile* manager_profile;
    scoped_ptr<SupervisedUserRegistrationUtility> registration_utility;
  };

  
  virtual void OnAuthenticationFailure(ExtendedAuthenticator::AuthState error)
      OVERRIDE;

  
  void OnMountSuccess(const std::string& mount_hash);
  void OnAddKeySuccess();
  void OnKeyTransformedIfNeeded(const UserContext& user_context);

  void StartCreationImpl();

  
  void CreationTimedOut();
  
  void RegistrationCallback(const GoogleServiceAuthError& error,
                            const std::string& token);

  
  
  void OnSupervisedUserFilesStored(bool success);

  
  
  static SupervisedUserCreationControllerNew* current_controller_;

  
  Stage stage_;

  
  scoped_refptr<ExtendedAuthenticator> authenticator_;

  
  scoped_ptr<UserCreationContext> creation_context_;

  
  base::OneShotTimer<SupervisedUserCreationControllerNew> timeout_timer_;

  
  base::WeakPtrFactory<SupervisedUserCreationControllerNew> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserCreationControllerNew);
};

}  

#endif  
