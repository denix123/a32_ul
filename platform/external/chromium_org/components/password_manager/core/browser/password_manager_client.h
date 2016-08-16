// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_CLIENT_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_CLIENT_H_

#include "base/metrics/field_trial.h"
#include "components/autofill/core/common/password_form.h"
#include "components/autofill/core/common/password_form_fill_data.h"
#include "components/password_manager/core/browser/password_store.h"

class PrefService;

namespace password_manager {

struct CredentialInfo;
class PasswordFormManager;
class PasswordManagerDriver;
class PasswordStore;

class PasswordManagerClient {
 public:
  PasswordManagerClient() {}
  virtual ~PasswordManagerClient() {}

  
  
  
  
  virtual bool IsAutomaticPasswordSavingEnabled() const;

  
  
  virtual bool IsPasswordManagerEnabledForCurrentPage() const;

  
  virtual bool ShouldFilterAutofillResult(
      const autofill::PasswordForm& form) = 0;

  
  
  virtual bool IsSyncAccountCredential(
      const std::string& username, const std::string& origin) const = 0;

  
  
  virtual void AutofillResultsComputed() {}

  
  
  
  
  virtual bool PromptUserToSavePassword(
      scoped_ptr<PasswordFormManager> form_to_save) = 0;

  
  
  virtual void AutomaticPasswordSave(
      scoped_ptr<PasswordFormManager> saved_form_manager) = 0;

  
  
  
  
  virtual void PasswordWasAutofilled(
      const autofill::PasswordFormMap& best_matches) const {}

  
  
  
  
  virtual void PasswordAutofillWasBlocked(
      const autofill::PasswordFormMap& best_matches) const {}

  
  
  virtual void AuthenticateAutofillAndFillForm(
      scoped_ptr<autofill::PasswordFormFillData> fill_data) = 0;

  
  virtual PrefService* GetPrefs() = 0;

  
  virtual PasswordStore* GetPasswordStore() = 0;

  
  virtual PasswordManagerDriver* GetDriver() = 0;

  
  
  virtual base::FieldTrial::Probability GetProbabilityForExperiment(
      const std::string& experiment_name);

  
  
  virtual bool IsPasswordSyncEnabled();

  
  
  
  
  virtual void OnLogRouterAvailabilityChanged(bool router_can_be_used);

  
  virtual void LogSavePasswordProgress(const std::string& text);

  
  
  virtual bool IsLoggingActive() const;

  
  
  virtual PasswordStore::AuthorizationPromptPolicy GetAuthorizationPromptPolicy(
      const autofill::PasswordForm& form);

  
  
  virtual void OnNotifyFailedSignIn(int request_id, const CredentialInfo&) {}

  
  
  virtual void OnNotifySignedIn(int request_id, const CredentialInfo&) {}

  
  
  virtual void OnNotifySignedOut(int request_id) {}

  
  
  virtual void OnRequestCredential(int request_id,
                                   bool zero_click_only,
                                   const std::vector<GURL>& federations) {}

 private:
  DISALLOW_COPY_AND_ASSIGN(PasswordManagerClient);
};

}  

#endif  
