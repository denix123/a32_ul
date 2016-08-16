// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOGIN_DISPLAY_HOST_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOGIN_DISPLAY_HOST_H_

#include <string>

#include "base/callback.h"
#include "base/callback_list.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "chrome/browser/chromeos/customization_document.h"
#include "chrome/browser/chromeos/login/ui/login_display.h"
#include "ui/gfx/native_widget_types.h"

namespace views {
class Widget;
}  

namespace chromeos {

class AppLaunchController;
class AutoEnrollmentController;
class LoginScreenContext;
class WebUILoginView;
class WizardController;

class LoginDisplayHost {
 public:
  virtual ~LoginDisplayHost() {}

  
  
  virtual LoginDisplay* CreateLoginDisplay(
      LoginDisplay::Delegate* delegate) = 0;

  
  virtual gfx::NativeWindow GetNativeWindow() const = 0;

  
  virtual WebUILoginView* GetWebUILoginView() const = 0;

  
  virtual void BeforeSessionStart() = 0;

  
  
  virtual void Finalize() = 0;

  
  virtual void OnCompleteLogin() = 0;

  
  virtual void OpenProxySettings() = 0;

  
  virtual void SetStatusAreaVisible(bool visible) = 0;

  
  virtual AutoEnrollmentController* GetAutoEnrollmentController() = 0;

  
  
  
  
  virtual void StartWizard(
      const std::string& first_screen_name,
      scoped_ptr<base::DictionaryValue> screen_parameters) = 0;

  
  
  virtual WizardController* GetWizardController() = 0;

  
  
  virtual AppLaunchController* GetAppLaunchController() = 0;

  
  
  
  virtual void StartUserAdding(const base::Closure& completion_callback) = 0;

  
  virtual void StartSignInScreen(const LoginScreenContext& context) = 0;

  
  virtual void ResumeSignInScreen() = 0;

  
  virtual void OnPreferencesChanged() = 0;

  
  virtual void PrewarmAuthentication() = 0;

  
  virtual void StartAppLaunch(const std::string& app_id,
                              bool diagnostic_mode) = 0;

  
  virtual void StartDemoAppLaunch() = 0;
};

}  

#endif  
