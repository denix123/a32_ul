// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_LOGIN_MANAGER_TEST_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_LOGIN_MANAGER_TEST_H_

#include <string>

#include "chrome/browser/chromeos/login/mixin_based_browser_test.h"
#include "chrome/browser/chromeos/login/mock_login_utils.h"
#include "chrome/browser/chromeos/login/test/js_checker.h"

namespace content {
class WebContents;
}  

namespace chromeos {

class UserContext;

class LoginManagerTest : public MixinBasedBrowserTest {
 public:
  explicit LoginManagerTest(bool should_launch_browser);

  
  virtual void TearDownOnMainThread() OVERRIDE;
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
  virtual void SetUpInProcessBrowserTestFixture() OVERRIDE;
  virtual void SetUpOnMainThread() OVERRIDE;

  
  
  
  void RegisterUser(const std::string& user_id);

  
  void SetExpectedCredentials(const UserContext& user_context);

  
  
  bool TryToLogin(const UserContext& user_context);

  
  
  
  
  bool AddUserToSession(const UserContext& user_context);

  
  void LoginUser(const std::string& user_id);

  
  void AddUser(const std::string& user_id);

  
  
  void JSExpect(const std::string& expression);

  MockLoginUtils& login_utils() { return *mock_login_utils_; }

  content::WebContents* web_contents() { return web_contents_; }

  test::JSChecker& js_checker() { return js_checker_; }

 private:
  void InitializeWebContents();

  void set_web_contents(content::WebContents* web_contents) {
    web_contents_ = web_contents;
  }

  MockLoginUtils* mock_login_utils_;
  bool should_launch_browser_;
  content::WebContents* web_contents_;
  test::JSChecker js_checker_;

  DISALLOW_COPY_AND_ASSIGN(LoginManagerTest);
};

}  

#endif  
