// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_UI_CONTROLLER_H_
#define CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_UI_CONTROLLER_H_

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_vector.h"
#include "base/timer/elapsed_timer.h"
#include "components/autofill/core/common/password_form.h"
#include "components/password_manager/core/browser/password_form_manager.h"
#include "components/password_manager/core/browser/password_store.h"
#include "components/password_manager/core/browser/password_store_change.h"
#include "components/password_manager/core/common/password_manager_ui.h"
#include "content/public/browser/navigation_details.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
}

class ManagePasswordsIcon;

class ManagePasswordsUIController
    : public content::WebContentsObserver,
      public content::WebContentsUserData<ManagePasswordsUIController>,
      public password_manager::PasswordStore::Observer {
 public:
  virtual ~ManagePasswordsUIController();

  
  
  
  
  void OnPasswordSubmitted(
      scoped_ptr<password_manager::PasswordFormManager> form_manager);

  
  
  void OnAutomaticPasswordSave(
      scoped_ptr<password_manager::PasswordFormManager> form_manager);

  
  
  
  
  void OnPasswordAutofilled(const autofill::PasswordFormMap& password_form_map);

  
  
  
  void OnBlacklistBlockedAutofill(
      const autofill::PasswordFormMap& password_form_map);

  
  virtual void OnLoginsChanged(
      const password_manager::PasswordStoreChangeList& changes) OVERRIDE;

  
  
  
  virtual void SavePassword();

  
  
  
  virtual void NeverSavePassword();

  
  
  
  virtual void UnblacklistSite();

  
  virtual void NavigateToPasswordManagerSettingsPage();

  virtual const autofill::PasswordForm& PendingCredentials() const;

  
  
  virtual void UpdateIconAndBubbleState(ManagePasswordsIcon* icon);

  password_manager::ui::State state() const { return state_; }

  
  
  bool PasswordPendingUserDecision() const;

  const autofill::ConstPasswordFormMap& best_matches() const {
    return password_form_map_;
  }

  const GURL& origin() const { return origin_; }

 protected:
  explicit ManagePasswordsUIController(
      content::WebContents* web_contents);

  
  
  virtual void SavePasswordInternal();
  virtual void NeverSavePasswordInternal();

  
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;
  virtual void WasHidden() OVERRIDE;

  
  
  
  
  ScopedVector<autofill::PasswordForm> new_password_forms_;

  
  
  
  autofill::ConstPasswordFormMap password_form_map_;

  
  
  password_manager::ui::State state_;

  
  
  
  scoped_ptr<base::ElapsedTimer> timer_;

 private:
  friend class content::WebContentsUserData<ManagePasswordsUIController>;

  
  
  void ShowBubbleWithoutUserInteraction();

  
  
  
  void UpdateBubbleAndIconVisibility();

  
  virtual void WebContentsDestroyed() OVERRIDE;

  
  
  
  
  scoped_ptr<password_manager::PasswordFormManager> form_manager_;

  
  
  bool autofill_blocked_;

  
  
  
  GURL origin_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordsUIController);
};

#endif  
