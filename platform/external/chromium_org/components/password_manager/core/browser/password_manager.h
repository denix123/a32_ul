// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "base/prefs/pref_member.h"
#include "base/stl_util.h"
#include "components/autofill/core/common/password_form.h"
#include "components/autofill/core/common/password_form_fill_data.h"
#include "components/password_manager/core/browser/login_model.h"
#include "components/password_manager/core/browser/password_form_manager.h"

class PrefRegistrySimple;

namespace content {
class WebContents;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace password_manager {

class BrowserSavePasswordProgressLogger;
class PasswordManagerClient;
class PasswordManagerDriver;
class PasswordManagerTest;
class PasswordFormManager;

class PasswordManager : public LoginModel {
 public:
  static const char kOtherPossibleUsernamesExperiment[];

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);
#if defined(OS_WIN)
  static void RegisterLocalPrefs(PrefRegistrySimple* registry);
#endif
  explicit PasswordManager(PasswordManagerClient* client);
  virtual ~PasswordManager();

  typedef base::Callback<void(const autofill::PasswordForm&)>
      PasswordSubmittedCallback;

  
  
  
  void AddSubmissionCallback(const PasswordSubmittedCallback& callback);

  
  
  
  
  bool IsSavingEnabledForCurrentPage() const;

  
  
  virtual void Autofill(const autofill::PasswordForm& form_for_autofill,
                        const autofill::PasswordFormMap& best_matches,
                        const autofill::PasswordForm& preferred_match,
                        bool wait_for_username) const;

  
  virtual void AddObserver(LoginModelObserver* observer) OVERRIDE;
  virtual void RemoveObserver(LoginModelObserver* observer) OVERRIDE;

  
  void SetFormHasGeneratedPassword(const autofill::PasswordForm& form);

  
  
  
  
  
  void ProvisionallySavePassword(const autofill::PasswordForm& form);

  
  void DidNavigateMainFrame(bool is_in_page);

  
  void OnPasswordFormsParsed(
      const std::vector<autofill::PasswordForm>& forms);

  
  void OnPasswordFormsRendered(
      const std::vector<autofill::PasswordForm>& visible_forms,
      bool did_stop_loading);

  
  virtual void OnPasswordFormSubmitted(
      const autofill::PasswordForm& password_form);

  PasswordManagerClient* client() { return client_; }

 private:
  enum ProvisionalSaveFailure {
    SAVING_DISABLED,
    EMPTY_PASSWORD,
    NO_MATCHING_FORM,
    MATCHING_NOT_COMPLETE,
    FORM_BLACKLISTED,
    INVALID_FORM,
    AUTOCOMPLETE_OFF,
    SYNC_CREDENTIAL,
    MAX_FAILURE_VALUE
  };

  
  
  
  bool IsEnabledForCurrentPage() const;

  
  
  
  
  void RecordFailure(ProvisionalSaveFailure failure,
                     const std::string& form_origin,
                     BrowserSavePasswordProgressLogger* logger);

  
  
  
  
  
  
  void PossiblyInitializeUsernamesExperiment(
      const autofill::PasswordFormMap& matches) const;

  
  
  bool OtherPossibleUsernamesEnabled() const;

  
  
  
  
  bool ShouldPromptUserToSavePassword() const;

  
  
  void CreatePendingLoginManagers(
      const std::vector<autofill::PasswordForm>& forms);

  
  
  
  
  
  
  
  
  
  
  
  
  

  ScopedVector<PasswordFormManager> pending_login_managers_;

  
  
  
  
  
  
  scoped_ptr<PasswordFormManager> provisional_save_manager_;

  
  PasswordManagerClient* const client_;

  
  PasswordManagerDriver* const driver_;

  
  
  BooleanPrefMember saving_passwords_enabled_;

  
  
  mutable ObserverList<LoginModelObserver> observers_;

  
  std::vector<PasswordSubmittedCallback> submission_callbacks_;

  
  
  
  
  std::vector<autofill::PasswordForm> all_visible_forms_;

  DISALLOW_COPY_AND_ASSIGN(PasswordManager);
};

}  

#endif  
