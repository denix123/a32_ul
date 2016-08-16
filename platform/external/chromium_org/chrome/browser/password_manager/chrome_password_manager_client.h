// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PASSWORD_MANAGER_CHROME_PASSWORD_MANAGER_CLIENT_H_
#define CHROME_BROWSER_PASSWORD_MANAGER_CHROME_PASSWORD_MANAGER_CLIENT_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "components/password_manager/content/browser/content_password_manager_driver.h"
#include "components/password_manager/core/browser/password_manager_client.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "ui/gfx/rect.h"

class Profile;

namespace autofill {
class PasswordGenerationPopupObserver;
class PasswordGenerationPopupControllerImpl;
}

namespace content {
class WebContents;
}

namespace password_manager {
struct CredentialInfo;
class PasswordGenerationManager;
class PasswordManager;
}

class ChromePasswordManagerClient
    : public password_manager::PasswordManagerClient,
      public content::WebContentsObserver,
      public content::WebContentsUserData<ChromePasswordManagerClient> {
 public:
  virtual ~ChromePasswordManagerClient();

  
  virtual bool IsAutomaticPasswordSavingEnabled() const OVERRIDE;
  virtual bool IsPasswordManagerEnabledForCurrentPage() const OVERRIDE;
  virtual bool ShouldFilterAutofillResult(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual bool IsSyncAccountCredential(
      const std::string& username, const std::string& origin) const OVERRIDE;
  virtual void AutofillResultsComputed() OVERRIDE;
  virtual bool PromptUserToSavePassword(
      scoped_ptr<password_manager::PasswordFormManager> form_to_save) OVERRIDE;
  virtual void AutomaticPasswordSave(
      scoped_ptr<password_manager::PasswordFormManager> saved_form_manager)
      OVERRIDE;
  virtual void PasswordWasAutofilled(
      const autofill::PasswordFormMap& best_matches) const OVERRIDE;
  virtual void PasswordAutofillWasBlocked(
      const autofill::PasswordFormMap& best_matches) const OVERRIDE;
  virtual void AuthenticateAutofillAndFillForm(
      scoped_ptr<autofill::PasswordFormFillData> fill_data) OVERRIDE;
  virtual PrefService* GetPrefs() OVERRIDE;
  virtual password_manager::PasswordStore* GetPasswordStore() OVERRIDE;
  virtual password_manager::PasswordManagerDriver* GetDriver() OVERRIDE;
  virtual base::FieldTrial::Probability GetProbabilityForExperiment(
      const std::string& experiment_name) OVERRIDE;
  virtual bool IsPasswordSyncEnabled() OVERRIDE;
  virtual void OnLogRouterAvailabilityChanged(bool router_can_be_used) OVERRIDE;
  virtual void LogSavePasswordProgress(const std::string& text) OVERRIDE;
  virtual bool IsLoggingActive() const OVERRIDE;
  virtual void OnNotifyFailedSignIn(
      int request_id,
      const password_manager::CredentialInfo&) OVERRIDE;
  virtual void OnNotifySignedIn(
      int request_id,
      const password_manager::CredentialInfo&) OVERRIDE;
  virtual void OnNotifySignedOut(int request_id) OVERRIDE;
  virtual void OnRequestCredential(
      int request_id,
      bool zero_click_only,
      const std::vector<GURL>& federations) OVERRIDE;

  
  void HidePasswordGenerationPopup();

  static void CreateForWebContentsWithAutofillClient(
      content::WebContents* contents,
      autofill::AutofillClient* autofill_client);

  
  
  static password_manager::PasswordManager* GetManagerFromWebContents(
      content::WebContents* contents);

  
  
  static password_manager::PasswordGenerationManager*
      GetGenerationManagerFromWebContents(content::WebContents* contents);

  
  void SetTestObserver(autofill::PasswordGenerationPopupObserver* observer);

  
  
  static bool IsTheHotNewBubbleUIEnabled();

  
  static bool EnabledForSyncSignin();

 protected:
  
  ChromePasswordManagerClient(content::WebContents* web_contents,
                              autofill::AutofillClient* autofill_client);

 private:
  enum AutofillForSyncCredentialsState {
    ALLOW_SYNC_CREDENTIALS,
    DISALLOW_SYNC_CREDENTIALS_FOR_REAUTH,
    DISALLOW_SYNC_CREDENTIALS,
  };

  friend class content::WebContentsUserData<ChromePasswordManagerClient>;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  
  
  void CommitFillPasswordForm(autofill::PasswordFormFillData* fill_data);

  
  
  gfx::RectF GetBoundsInScreenSpace(const gfx::RectF& bounds);

  
  
  
  void ShowPasswordGenerationPopup(const gfx::RectF& bounds,
                                   int max_length,
                                   const autofill::PasswordForm& form);

  
  void ShowPasswordEditingPopup(
      const gfx::RectF& bounds, const autofill::PasswordForm& form);

  
  
  void NotifyRendererOfLoggingAvailability();

  
  
  bool LastLoadWasTransactionalReauthPage() const;

  
  
  bool IsURLPasswordWebsiteReauth(const GURL& url) const;

  
  void SetUpAutofillSyncState();

  Profile* const profile_;

  password_manager::ContentPasswordManagerDriver driver_;

  
  autofill::PasswordGenerationPopupObserver* observer_;

  
  base::WeakPtr<
    autofill::PasswordGenerationPopupControllerImpl> popup_controller_;

  
  bool can_use_log_router_;

  
  AutofillForSyncCredentialsState autofill_sync_state_;

  
  
  bool sync_credential_was_filtered_;

  
  base::WeakPtrFactory<ChromePasswordManagerClient> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromePasswordManagerClient);
};

#endif  
