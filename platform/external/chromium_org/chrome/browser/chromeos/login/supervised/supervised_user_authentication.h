// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_AUTHENTICATION_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_AUTHENTICATION_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/values.h"
#include "chrome/browser/chromeos/login/supervised/supervised_user_login_flow.h"
#include "chromeos/login/auth/user_context.h"

namespace chromeos {

class SupervisedUserManager;

class SupervisedUserAuthentication {
 public:
  enum Schema {
    SCHEMA_PLAIN = 1,
    SCHEMA_SALT_HASHED = 2
  };

  enum SupervisedUserPasswordChangeResult {
    PASSWORD_CHANGED_IN_MANAGER_SESSION = 0,
    PASSWORD_CHANGED_IN_USER_SESSION = 1,
    PASSWORD_CHANGE_FAILED_NO_MASTER_KEY = 2,
    PASSWORD_CHANGE_FAILED_NO_SIGNATURE_KEY = 3,
    PASSWORD_CHANGE_FAILED_NO_PASSWORD_DATA = 4,
    PASSWORD_CHANGE_FAILED_MASTER_KEY_FAILURE = 5,
    PASSWORD_CHANGE_FAILED_LOADING_DATA = 6,
    PASSWORD_CHANGE_FAILED_INCOMPLETE_DATA = 7,
    PASSWORD_CHANGE_FAILED_AUTHENTICATION_FAILURE = 8,
    PASSWORD_CHANGE_FAILED_STORE_DATA = 9,
    PASSWORD_CHANGE_RESULT_MAX_VALUE = 10
  };

  typedef base::Callback<void(const base::DictionaryValue* password_data)>
      PasswordDataCallback;

  explicit SupervisedUserAuthentication(SupervisedUserManager* owner);
  virtual ~SupervisedUserAuthentication();

  
  
  Schema GetStableSchema();

  
  UserContext TransformKey(const UserContext& context);

  
  
  bool FillDataForNewUser(const std::string& user_id,
                          const std::string& password,
                          base::DictionaryValue* password_data,
                          base::DictionaryValue* extra_data);

  
  
  void StorePasswordData(const std::string& user_id,
                         const base::DictionaryValue& password_data);

  bool NeedPasswordChange(const std::string& user_id,
                          const base::DictionaryValue* password_data);

  
  bool HasScheduledPasswordUpdate(const std::string& user_id);
  void ClearScheduledPasswordUpdate(const std::string& user_id);

  
  
  
  bool HasIncompleteKey(const std::string& user_id);
  void MarkKeyIncomplete(const std::string& user_id, bool incomplete);

  
  void LoadPasswordUpdateData(const std::string& user_id,
                              const PasswordDataCallback& success_callback,
                              const base::Closure& failure_callback);

  
  
  std::string GenerateMasterKey();

  
  void ScheduleSupervisedPasswordChange(
      const std::string& supervised_user_id,
      const base::DictionaryValue* password_data);

  
  Schema GetPasswordSchema(const std::string& user_id);

  static std::string BuildPasswordSignature(
      const std::string& password,
      int revision,
      const std::string& base64_signature_key);

 private:
  SupervisedUserManager* owner_;

  
  bool migration_enabled_;

  
  Schema stable_schema_;


  DISALLOW_COPY_AND_ASSIGN(SupervisedUserAuthentication);
};

} 

#endif  
