// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREENSHOT_TESTING_MIXIN_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREENSHOT_TESTING_MIXIN_H_

#include <string>

#include "base/command_line.h"
#include "base/timer/timer.h"
#include "chrome/browser/chromeos/login/mixin_based_browser_test.h"
#include "chrome/browser/chromeos/login/screenshot_tester.h"
#include "content/public/test/browser_test_base.h"

namespace chromeos {

class ScreenshotTestingMixin : public MixinBasedBrowserTest::Mixin {
 public:
  ScreenshotTestingMixin();
  virtual ~ScreenshotTestingMixin();

  
  virtual void SetUpInProcessBrowserTestFixture() OVERRIDE;

  
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

  
  void RunScreenshotTesting(const std::string& test_name);

 private:
  
  
  
  
  
  void SynchronizeAnimationLoadWithCompositor();

  
  
  void HandleAnimationLoad();

  
  
  base::OneShotTimer<ScreenshotTestingMixin> timer_;
  base::Closure animation_waiter_quitter_;

  
  bool enable_test_screenshots_;

  
  
  ScreenshotTester screenshot_tester_;
};

}  

#endif  
