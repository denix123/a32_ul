// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_AUTH_CRYPTOHOME_AUTHENTICATOR_H_
#define CHROMEOS_LOGIN_AUTH_CRYPTOHOME_AUTHENTICATOR_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "base/task_runner.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/login/auth/auth_attempt_state.h"
#include "chromeos/login/auth/auth_attempt_state_resolver.h"
#include "chromeos/login/auth/authenticator.h"
#include "chromeos/login/auth/test_attempt_state.h"
#include "google_apis/gaia/gaia_auth_consumer.h"

class AuthFailure;
class Profile;

namespace chromeos {

class AuthStatusConsumer;

class CHROMEOS_EXPORT CryptohomeAuthenticator
    : public Authenticator,
      public AuthAttemptStateResolver {
 public:
  enum AuthState {
    CONTINUE = 0,            
    NO_MOUNT = 1,            
    FAILED_MOUNT = 2,        
    FAILED_REMOVE = 3,       
    FAILED_TMPFS = 4,        
    FAILED_TPM = 5,          
    CREATE_NEW = 6,          
    RECOVER_MOUNT = 7,       
    POSSIBLE_PW_CHANGE = 8,  
    NEED_NEW_PW = 9,         
                             
    NEED_OLD_PW = 10,        
                             
    HAVE_NEW_PW = 11,        
                             
    OFFLINE_LOGIN = 12,      
    DEMO_LOGIN = 13,         
    ONLINE_LOGIN = 14,       
    UNLOCK = 15,             
    ONLINE_FAILED = 16,      
                             
    GUEST_LOGIN = 17,        
    PUBLIC_ACCOUNT_LOGIN = 18,        
    SUPERVISED_USER_LOGIN = 19,       
    LOGIN_FAILED = 20,                
    OWNER_REQUIRED = 21,              
    FAILED_USERNAME_HASH = 22,        
    KIOSK_ACCOUNT_LOGIN = 23,         
    REMOVED_DATA_AFTER_FAILURE = 24,  
                                      
  };

  CryptohomeAuthenticator(scoped_refptr<base::TaskRunner> task_runner,
                          AuthStatusConsumer* consumer);

  
  virtual void CompleteLogin(Profile* profile,
                             const UserContext& user_context) OVERRIDE;

  
  
  
  
  
  
  
  
  virtual void AuthenticateToLogin(Profile* profile,
                                   const UserContext& user_context) OVERRIDE;

  
  
  
  
  virtual void AuthenticateToUnlock(const UserContext& user_context) OVERRIDE;

  
  
  
  virtual void LoginAsSupervisedUser(const UserContext& user_context) OVERRIDE;

  
  
  virtual void LoginRetailMode() OVERRIDE;

  
  
  virtual void LoginOffTheRecord() OVERRIDE;

  
  
  
  virtual void LoginAsPublicSession(const UserContext& user_context) OVERRIDE;

  
  
  
  
  
  virtual void LoginAsKioskAccount(const std::string& app_user_id,
                                   bool use_guest_mount) OVERRIDE;

  
  
  virtual void OnRetailModeAuthSuccess() OVERRIDE;
  virtual void OnAuthSuccess() OVERRIDE;
  virtual void OnAuthFailure(const AuthFailure& error) OVERRIDE;
  virtual void RecoverEncryptedData(const std::string& old_password) OVERRIDE;
  virtual void ResyncEncryptedData() OVERRIDE;

  
  
  
  
  
  
  
  virtual void Resolve() OVERRIDE;

  void OnOffTheRecordAuthSuccess();
  void OnPasswordChangeDetected();

 protected:
  virtual ~CryptohomeAuthenticator();

  typedef base::Callback<void(bool is_owner)> IsOwnerCallback;

  
  
  virtual bool IsKnownUser(const UserContext& context) = 0;

  
  
  virtual bool IsSafeMode() = 0;

  
  
  
  virtual void CheckSafeModeOwnership(const UserContext& context,
                                      const IsOwnerCallback& callback) = 0;

 private:
  friend class CryptohomeAuthenticatorTest;
  FRIEND_TEST_ALL_PREFIXES(CryptohomeAuthenticatorTest,
                           ResolveOwnerNeededDirectFailedMount);
  FRIEND_TEST_ALL_PREFIXES(CryptohomeAuthenticatorTest,
                           ResolveOwnerNeededMount);
  FRIEND_TEST_ALL_PREFIXES(CryptohomeAuthenticatorTest,
                           ResolveOwnerNeededFailedMount);

  
  void RemoveEncryptedData();

  
  
  
  AuthState ResolveState();

  
  
  
  
  AuthState ResolveCryptohomeFailureState();

  
  
  
  
  AuthState ResolveCryptohomeSuccessState();

  
  
  
  
  AuthState ResolveOnlineSuccessState(AuthState offline_state);

  
  void set_attempt_state(TestAttemptState* new_state) {  
    current_state_.reset(new_state);
  }

  
  void SetOwnerState(bool owner_check_finished, bool check_result);

  
  
  
  bool VerifyOwner();

  
  void OnOwnershipChecked(bool is_owner);

  
  
  void ResolveLoginCompletionStatus();

  scoped_refptr<base::TaskRunner> task_runner_;

  scoped_ptr<AuthAttemptState> current_state_;
  bool migrate_attempted_;
  bool remove_attempted_;
  bool resync_attempted_;
  bool ephemeral_mount_attempted_;
  bool check_key_attempted_;

  
  
  
  
  bool already_reported_success_;
  base::Lock success_lock_;  

  
  
  bool owner_is_verified_;
  bool user_can_login_;

  
  bool remove_user_data_on_failure_;

  
  
  const AuthFailure* delayed_login_failure_;

  DISALLOW_COPY_AND_ASSIGN(CryptohomeAuthenticator);
};

}  

#endif  
