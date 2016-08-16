// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_TEST_H_
#define CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_TEST_H_

#include "base/metrics/histogram_samples.h"
#include "base/test/histogram_tester.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "components/autofill/core/common/password_form.h"
#include "testing/gtest/include/gtest/gtest.h"

class ManagePasswordsUIControllerMock;
class ManagePasswordsIcon;

class ManagePasswordsTest : public InProcessBrowserTest {
 public:
  ManagePasswordsTest() {}

  
  virtual void SetUpOnMainThread() OVERRIDE;

  
  ManagePasswordsUIControllerMock* controller();

  
  virtual ManagePasswordsIcon* view() = 0;

  
  void ExecuteManagePasswordsCommand();

  
  void SetupManagingPasswords();

  
  void SetupAutomaticPassword();

  
  void SetupPendingPassword();

  
  void SetupBlackistedPassword();

  
  base::HistogramSamples* GetSamples(const char* histogram);

  autofill::PasswordForm* test_form() { return &test_form_; }

 private:
  autofill::PasswordForm test_form_;
  base::HistogramTester histogram_tester_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordsTest);
};

#endif  
