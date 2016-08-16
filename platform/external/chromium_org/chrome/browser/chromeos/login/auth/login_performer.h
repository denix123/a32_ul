// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_AUTH_LOGIN_PERFORMER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_AUTH_LOGIN_PERFORMER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/policy/wildcard_login_checker.h"
#include "chromeos/login/auth/auth_status_consumer.h"
#include "chromeos/login/auth/authenticator.h"
#include "chromeos/login/auth/extended_authenticator.h"
#include "chromeos/login/auth/online_attempt_host.h"
#include "chromeos/login/auth/user_context.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "google_apis/gaia/google_service_auth_error.h"

namespace policy {
class WildcardLoginChecker;
}

namespace chromeos {

class LoginPerformer : public AuthStatusConsumer,
                       public OnlineAttemptHost::Delegate {
 public:
  typedef enum AuthorizationMode {
    
    AUTH_MODE_INTERNAL,
    
    AUTH_MODE_EXTENSION
  } AuthorizationMode;

  
  class Delegate : public AuthStatusConsumer {
   public:
    virtual ~Delegate() {}
    virtual void WhiteListCheckFailed(const std::string& email) = 0;
    virtual void PolicyLoadFailed() = 0;
    virtual void OnOnlineChecked(const std::string& email, bool success) = 0;
  };

  explicit LoginPerformer(Delegate* delegate);
  virtual ~LoginPerformer();

  
  virtual void OnAuthFailure(const AuthFailure& error) OVERRIDE;
  virtual void OnRetailModeAuthSuccess(
      const UserContext& user_context) OVERRIDE;
  virtual void OnAuthSuccess(const UserContext& user_context) OVERRIDE;
  virtual void OnOffTheRecordAuthSuccess() OVERRIDE;
  virtual void OnPasswordChangeDetected() OVERRIDE;

  
  
  
  void PerformLogin(const UserContext& user_context,
                    AuthorizationMode auth_mode);

  
  void LoginAsSupervisedUser(const UserContext& user_context);

  
  void LoginRetailMode();

  
  void LoginOffTheRecord();

  
  void LoginAsPublicSession(const UserContext& user_context);

  
  void LoginAsKioskAccount(const std::string& app_user_id,
                           bool use_guest_mount);

  
  void RecoverEncryptedData(const std::string& old_password);

  
  void ResyncEncryptedData();

  
  const GoogleServiceAuthError& error() const {
    return last_login_failure_.error();
  }

  
  bool password_changed() { return password_changed_; }

  
  
  
  
  
  int password_changed_callback_count() {
    return password_changed_callback_count_;
  }

  void set_delegate(Delegate* delegate) { delegate_ = delegate; }

  AuthorizationMode auth_mode() const { return auth_mode_; }

 protected:
  
  virtual void OnChecked(const std::string& username, bool success) OVERRIDE;

 private:
  
  void StartLoginCompletion();

  
  void StartAuthentication();

  
  
  
  void OnlineWildcardLoginCheckCompleted(
      policy::WildcardLoginChecker::Result result);

  
  scoped_refptr<Authenticator> authenticator_;
  scoped_refptr<ExtendedAuthenticator> extended_authenticator_;

  
  OnlineAttemptHost online_attempt_host_;

  
  
  AuthFailure last_login_failure_;

  
  UserContext user_context_;

  
  Delegate* delegate_;

  
  
  bool password_changed_;
  int password_changed_callback_count_;

  
  AuthorizationMode auth_mode_;

  
  scoped_ptr<policy::WildcardLoginChecker> wildcard_login_checker_;

  base::WeakPtrFactory<LoginPerformer> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(LoginPerformer);
};

}  

#endif  
