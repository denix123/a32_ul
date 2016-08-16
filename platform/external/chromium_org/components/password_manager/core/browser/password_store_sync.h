// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_SYNC_INTERFACE_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_SYNC_INTERFACE_H_

#include <vector>

#include "components/password_manager/core/browser/password_store_change.h"

namespace password_manager {

class PasswordStoreSync {
 public:
  
  virtual bool FillAutofillableLogins(
      std::vector<autofill::PasswordForm*>* forms) = 0;

  
  virtual bool FillBlacklistLogins(
      std::vector<autofill::PasswordForm*>* forms) = 0;

  
  virtual PasswordStoreChangeList AddLoginImpl(
      const autofill::PasswordForm& form) = 0;

  
  virtual PasswordStoreChangeList UpdateLoginImpl(
      const autofill::PasswordForm& form) = 0;

  
  virtual PasswordStoreChangeList RemoveLoginImpl(
      const autofill::PasswordForm& form) = 0;

  
  virtual void NotifyLoginsChanged(const PasswordStoreChangeList& changes) = 0;

 protected:
  virtual ~PasswordStoreSync();
};

}  

#endif  
