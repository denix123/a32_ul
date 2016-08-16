// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_USER_MANAGER_H_
#define CHROME_BROWSER_UI_USER_MANAGER_H_

#include "chrome/browser/profiles/profile_window.h"

namespace base {
class FilePath;
}

class UserManager {
 public:
  
  
  
  
  
  static void Show(const base::FilePath& profile_path_to_focus,
                   profiles::UserManagerTutorialMode tutorial_mode,
                   profiles::UserManagerProfileSelected profile_open_action);

  
  static void Hide();

  
  static bool IsShowing();

  
  
  static const int kWindowWidth = 800;
  static const int kWindowHeight = 600;

 private:
  DISALLOW_COPY_AND_ASSIGN(UserManager);
};

#endif  
