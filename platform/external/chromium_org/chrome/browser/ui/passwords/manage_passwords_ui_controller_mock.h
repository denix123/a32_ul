// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_UI_CONTROLLER_MOCK_H_
#define CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_UI_CONTROLLER_MOCK_H_

#include "base/basictypes.h"
#include "chrome/browser/ui/passwords/manage_passwords_ui_controller.h"
#include "components/password_manager/core/common/password_manager_ui.h"
#include "content/public/browser/navigation_details.h"

namespace content {
class WebContents;
}  

class ManagePasswordsUIControllerMock
    : public ManagePasswordsUIController {
 public:
  explicit ManagePasswordsUIControllerMock(
      content::WebContents* contents);
  virtual ~ManagePasswordsUIControllerMock();

  
  
  
  
  virtual void NavigateToPasswordManagerSettingsPage() OVERRIDE;
  bool navigated_to_settings_page() const {
    return navigated_to_settings_page_;
  }

  
  virtual void SavePasswordInternal() OVERRIDE;
  bool saved_password() const { return saved_password_; }

  virtual void NeverSavePasswordInternal() OVERRIDE;
  bool never_saved_password() const { return never_saved_password_; }

  virtual const autofill::PasswordForm& PendingCredentials() const OVERRIDE;
  void SetPendingCredentials(autofill::PasswordForm pending_credentials);

  
  void SetPasswordFormMap(const autofill::ConstPasswordFormMap& map) {
    password_form_map_ = map;
  }
  void SetState(password_manager::ui::State state) { state_ = state; }

  void SetTimer(base::ElapsedTimer* timer) { timer_.reset(timer); }

  
  bool IsInstalled() const;

  using ManagePasswordsUIController::DidNavigateMainFrame;

 private:
  bool navigated_to_settings_page_;
  bool saved_password_;
  bool never_saved_password_;

  autofill::PasswordForm pending_credentials_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordsUIControllerMock);
};

#endif  
