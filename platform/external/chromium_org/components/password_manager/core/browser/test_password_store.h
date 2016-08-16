// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_TEST_PASSWORD_STORE_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_TEST_PASSWORD_STORE_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "components/password_manager/core/browser/password_store.h"

namespace content {
class BrowserContext;
}

namespace password_manager {

class TestPasswordStore : public PasswordStore {
 public:
  TestPasswordStore();

  typedef std::map<std::string ,
                   std::vector<autofill::PasswordForm> > PasswordMap;

  const PasswordMap& stored_passwords() const;
  void Clear();

  
  
  
  bool IsEmpty() const;

 protected:
  virtual ~TestPasswordStore();

  
  bool FormsAreEquivalent(const autofill::PasswordForm& lhs,
                          const autofill::PasswordForm& rhs);

  
  virtual PasswordStoreChangeList AddLoginImpl(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual PasswordStoreChangeList UpdateLoginImpl(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual PasswordStoreChangeList RemoveLoginImpl(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual void GetLoginsImpl(
      const autofill::PasswordForm& form,
      PasswordStore::AuthorizationPromptPolicy prompt_policy,
      const ConsumerCallbackRunner& runner) OVERRIDE;
  virtual void WrapModificationTask(ModificationTask task) OVERRIDE;

  
  virtual void ReportMetricsImpl(const std::string& sync_username) OVERRIDE {}
  virtual PasswordStoreChangeList RemoveLoginsCreatedBetweenImpl(
      base::Time begin,
      base::Time end) OVERRIDE;
  virtual PasswordStoreChangeList RemoveLoginsSyncedBetweenImpl(
      base::Time delete_begin,
      base::Time delete_end) OVERRIDE;
  virtual void GetAutofillableLoginsImpl(
      PasswordStore::GetLoginsRequest* request) OVERRIDE {}
  virtual void GetBlacklistLoginsImpl(
      PasswordStore::GetLoginsRequest* request) OVERRIDE {}
  virtual bool FillAutofillableLogins(
      std::vector<autofill::PasswordForm*>* forms) OVERRIDE;
  virtual bool FillBlacklistLogins(
      std::vector<autofill::PasswordForm*>* forms) OVERRIDE;

 private:
  PasswordMap stored_passwords_;

  DISALLOW_COPY_AND_ASSIGN(TestPasswordStore);
};

}  

#endif  
