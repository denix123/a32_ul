// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_LOGIN_DATABASE_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_LOGIN_DATABASE_H_

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/pickle.h"
#include "base/strings/string16.h"
#include "components/password_manager/core/browser/password_store_change.h"
#include "components/password_manager/core/browser/psl_matching_helper.h"
#include "sql/connection.h"
#include "sql/meta_table.h"

namespace password_manager {

class LoginDatabase {
 public:
  LoginDatabase();
  virtual ~LoginDatabase();

  
  
  bool Init(const base::FilePath& db_path);

  
  void ReportMetrics(const std::string& sync_username);

  
  
  
  
  PasswordStoreChangeList AddLogin(const autofill::PasswordForm& form);

  
  
  
  
  PasswordStoreChangeList UpdateLogin(const autofill::PasswordForm& form);

  
  bool RemoveLogin(const autofill::PasswordForm& form);

  
  
  
  bool RemoveLoginsCreatedBetween(base::Time delete_begin,
                                  base::Time delete_end);

  
  
  
  bool RemoveLoginsSyncedBetween(base::Time delete_begin,
                                 base::Time delete_end);

  
  
  
  bool GetLogins(const autofill::PasswordForm& form,
                 std::vector<autofill::PasswordForm*>* forms) const;

  
  
  
  bool GetLoginsCreatedBetween(
      base::Time begin,
      base::Time end,
      std::vector<autofill::PasswordForm*>* forms) const;

  
  
  
  bool GetLoginsSyncedBetween(
      base::Time begin,
      base::Time end,
      std::vector<autofill::PasswordForm*>* forms) const;

  
  
  bool GetAutofillableLogins(
      std::vector<autofill::PasswordForm*>* forms) const;

  
  
  bool GetBlacklistLogins(
      std::vector<autofill::PasswordForm*>* forms) const;

  
  
  
  
  
  bool DeleteAndRecreateDatabaseFile();

 private:
  
  enum EncryptionResult {
    
    ENCRYPTION_RESULT_SUCCESS,
    
    
    
    ENCRYPTION_RESULT_ITEM_FAILURE,
    
    
    
    ENCRYPTION_RESULT_SERVICE_FAILURE,
  };

  
  
  
  
  EncryptionResult EncryptedString(const base::string16& plain_text,
                                   std::string* cipher_text) const;

  
  
  
  
  EncryptionResult DecryptedString(const std::string& cipher_text,
                                   base::string16* plain_text) const;

  bool InitLoginsTable();
  bool MigrateOldVersionsAsNeeded();

  
  
  
  
  EncryptionResult InitPasswordFormFromStatement(autofill::PasswordForm* form,
                                                 sql::Statement& s) const;

  
  
  bool GetAllLoginsWithBlacklistSetting(
      bool blacklisted, std::vector<autofill::PasswordForm*>* forms) const;

  base::FilePath db_path_;
  mutable sql::Connection db_;
  sql::MetaTable meta_table_;

  DISALLOW_COPY_AND_ASSIGN(LoginDatabase);
};

}  

#endif  
