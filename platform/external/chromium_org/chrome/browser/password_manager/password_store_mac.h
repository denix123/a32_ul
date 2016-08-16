// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PASSWORD_MANAGER_PASSWORD_STORE_MAC_H_
#define CHROME_BROWSER_PASSWORD_MANAGER_PASSWORD_STORE_MAC_H_

#include <vector>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread.h"
#include "components/password_manager/core/browser/login_database.h"
#include "components/password_manager/core/browser/password_store.h"

namespace crypto {
class AppleKeychain;
}

namespace password_manager {
class LoginDatabase;
}

class PasswordStoreMac : public password_manager::PasswordStore {
 public:
  
  
  PasswordStoreMac(
      scoped_refptr<base::SingleThreadTaskRunner> main_thread_runner,
      scoped_refptr<base::SingleThreadTaskRunner> db_thread_runner,
      crypto::AppleKeychain* keychain,
      password_manager::LoginDatabase* login_db);

  
  virtual bool Init(
      const syncer::SyncableService::StartSyncFlare& flare,
      const std::string& sync_username) OVERRIDE;

  
  virtual void Shutdown() OVERRIDE;

 protected:
  virtual ~PasswordStoreMac();

  virtual scoped_refptr<base::SingleThreadTaskRunner>
      GetBackgroundTaskRunner() OVERRIDE;

 private:
  virtual void ReportMetricsImpl(const std::string& sync_username) OVERRIDE;
  virtual password_manager::PasswordStoreChangeList AddLoginImpl(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual password_manager::PasswordStoreChangeList UpdateLoginImpl(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual password_manager::PasswordStoreChangeList RemoveLoginImpl(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual password_manager::PasswordStoreChangeList
      RemoveLoginsCreatedBetweenImpl(base::Time delete_begin,
                                     base::Time delete_end) OVERRIDE;
  virtual password_manager::PasswordStoreChangeList
      RemoveLoginsSyncedBetweenImpl(base::Time delete_begin,
                                    base::Time delete_end) OVERRIDE;
  virtual void GetLoginsImpl(
      const autofill::PasswordForm& form,
      AuthorizationPromptPolicy prompt_policy,
      const ConsumerCallbackRunner& callback_runner) OVERRIDE;
  virtual void GetAutofillableLoginsImpl(GetLoginsRequest* request) OVERRIDE;
  virtual void GetBlacklistLoginsImpl(GetLoginsRequest* request) OVERRIDE;
  virtual bool FillAutofillableLogins(
      std::vector<autofill::PasswordForm*>* forms) OVERRIDE;
  virtual bool FillBlacklistLogins(
      std::vector<autofill::PasswordForm*>* forms) OVERRIDE;

  
  
  
  bool AddToKeychainIfNecessary(const autofill::PasswordForm& form);

  
  
  bool DatabaseHasFormMatchingKeychainForm(
      const autofill::PasswordForm& form);

  
  void RemoveDatabaseForms(
      const std::vector<autofill::PasswordForm*>& forms);

  
  void RemoveKeychainForms(
      const std::vector<autofill::PasswordForm*>& forms);

  
  
  
  void CleanOrphanedForms(std::vector<autofill::PasswordForm*>* forms);

  scoped_ptr<crypto::AppleKeychain> keychain_;
  scoped_ptr<password_manager::LoginDatabase> login_metadata_db_;

  
  scoped_ptr<base::Thread> thread_;

  DISALLOW_COPY_AND_ASSIGN(PasswordStoreMac);
};

#endif  
