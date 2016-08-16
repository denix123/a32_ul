// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PASSWORD_MANAGER_PASSWORD_STORE_X_H_
#define CHROME_BROWSER_PASSWORD_MANAGER_PASSWORD_STORE_X_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "components/password_manager/core/browser/password_store_default.h"

class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace password_manager {
class LoginDatabase;
}

class PasswordStoreX : public password_manager::PasswordStoreDefault {
 public:
  
  
  class NativeBackend {
   public:
    typedef std::vector<autofill::PasswordForm*> PasswordFormList;

    virtual ~NativeBackend() {}

    virtual bool Init() = 0;

    virtual password_manager::PasswordStoreChangeList AddLogin(
        const autofill::PasswordForm& form) = 0;
    virtual bool UpdateLogin(
        const autofill::PasswordForm& form,
        password_manager::PasswordStoreChangeList* changes) = 0;
    virtual bool RemoveLogin(const autofill::PasswordForm& form) = 0;

    
    
    
    virtual bool RemoveLoginsCreatedBetween(
        base::Time delete_begin,
        base::Time delete_end,
        password_manager::PasswordStoreChangeList* changes) = 0;
    virtual bool RemoveLoginsSyncedBetween(
        base::Time delete_begin,
        base::Time delete_end,
        password_manager::PasswordStoreChangeList* changes) = 0;

    virtual bool GetLogins(const autofill::PasswordForm& form,
                           PasswordFormList* forms) = 0;
    virtual bool GetAutofillableLogins(PasswordFormList* forms) = 0;
    virtual bool GetBlacklistLogins(PasswordFormList* forms) = 0;
  };

  
  
  PasswordStoreX(scoped_refptr<base::SingleThreadTaskRunner> main_thread_runner,
                 scoped_refptr<base::SingleThreadTaskRunner> db_thread_runner,
                 password_manager::LoginDatabase* login_db,
                 NativeBackend* backend);

 private:
  friend class PasswordStoreXTest;

  virtual ~PasswordStoreX();

  
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

  
  void SortLoginsByOrigin(NativeBackend::PasswordFormList* list);

  
  void CheckMigration();

  
  bool use_native_backend() { return !!backend_.get(); }

  
  
  bool allow_default_store();

  
  
  
  
  ssize_t MigrateLogins();

  
  scoped_ptr<NativeBackend> backend_;
  
  bool migration_checked_;
  
  
  
  
  bool allow_fallback_;

  DISALLOW_COPY_AND_ASSIGN(PasswordStoreX);
};

#endif  
