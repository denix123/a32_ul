// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PASSWORDS_PASSWORD_MANAGER_PRESENTER_H_
#define CHROME_BROWSER_UI_PASSWORDS_PASSWORD_MANAGER_PRESENTER_H_

#include <string>
#include <vector>

#include "base/memory/scoped_vector.h"
#include "base/prefs/pref_member.h"
#include "components/password_manager/core/browser/password_store.h"
#include "components/password_manager/core/browser/password_store_consumer.h"

namespace autofill {
struct PasswordForm;
}

class PasswordUIView;

class Profile;

class PasswordManagerPresenter
    : public password_manager::PasswordStore::Observer {
 public:
  
  explicit PasswordManagerPresenter(PasswordUIView* password_view);
  virtual ~PasswordManagerPresenter();

  
  virtual void OnLoginsChanged(
      const password_manager::PasswordStoreChangeList& changes) OVERRIDE;

  
  void UpdatePasswordLists();

  void Initialize();

  
  const autofill::PasswordForm* GetPassword(size_t index);

  
  const autofill::PasswordForm* GetPasswordException(size_t index);

  
  
  void RemoveSavedPassword(size_t index);

  
  
  void RemovePasswordException(size_t index);

  
  
  void RequestShowPassword(size_t index);

 private:
  friend class PasswordManagerPresenterTest;

  
  password_manager::PasswordStore* GetPasswordStore();

  
  
  bool IsAuthenticationRequired();

  
  void SetPasswordList();
  void SetPasswordExceptionList();

  
  class ListPopulater : public password_manager::PasswordStoreConsumer {
   public:
    explicit ListPopulater(PasswordManagerPresenter* page);
    virtual ~ListPopulater();

    
    virtual void Populate() = 0;

   protected:
    PasswordManagerPresenter* page_;
  };

  
  class PasswordListPopulater : public ListPopulater {
   public:
    explicit PasswordListPopulater(PasswordManagerPresenter* page);

    
    virtual void Populate() OVERRIDE;

    
    virtual void OnGetPasswordStoreResults(
        const std::vector<autofill::PasswordForm*>& results) OVERRIDE;
  };

  
  class PasswordExceptionListPopulater : public ListPopulater {
   public:
    explicit PasswordExceptionListPopulater(PasswordManagerPresenter* page);

    
    virtual void Populate() OVERRIDE;

    
    virtual void OnGetPasswordStoreResults(
        const std::vector<autofill::PasswordForm*>& results) OVERRIDE;
  };

  
  PasswordListPopulater populater_;
  PasswordExceptionListPopulater exception_populater_;

  ScopedVector<autofill::PasswordForm> password_list_;
  ScopedVector<autofill::PasswordForm> password_exception_list_;

  
  BooleanPrefMember show_passwords_;

  
  
  bool require_reauthentication_;

  
  
  base::TimeTicks last_authentication_time_;

  
  PasswordUIView* password_view_;

  DISALLOW_COPY_AND_ASSIGN(PasswordManagerPresenter);
};

#endif  
