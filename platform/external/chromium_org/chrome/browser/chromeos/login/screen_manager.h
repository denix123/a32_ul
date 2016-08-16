// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREEN_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREEN_MANAGER_H_

#include <map>
#include <string>

#include "base/macros.h"
#include "base/memory/linked_ptr.h"
#include "chrome/browser/chromeos/login/screens/wizard_screen.h"

namespace chromeos {

class ScreenManager {
 public:
  ScreenManager();
  virtual ~ScreenManager();

  
  WizardScreen* GetScreen(const std::string& screen_name);

  
  virtual WizardScreen* CreateScreen(const std::string& screen_name) = 0;

  bool HasScreen(const std::string& screen_name);

 private:
  FRIEND_TEST_ALL_PREFIXES(EnrollmentScreenTest, TestCancel);
  FRIEND_TEST_ALL_PREFIXES(WizardControllerFlowTest, Accelerators);
  friend class WizardControllerFlowTest;
  friend class WizardControllerOobeResumeTest;
  friend class WizardInProcessBrowserTest;
  friend class WizardControllerBrokenLocalStateTest;

  
  typedef std::map<std::string, linked_ptr<WizardScreen> > ScreenMap;
  ScreenMap screens_;

  DISALLOW_COPY_AND_ASSIGN(ScreenManager);
};

}  

#endif  
