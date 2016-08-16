// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PROFILE_CHOOSER_CONSTANTS_H_
#define CHROME_BROWSER_UI_PROFILE_CHOOSER_CONSTANTS_H_

namespace profiles {

enum BubbleViewMode {
  
  BUBBLE_VIEW_MODE_PROFILE_CHOOSER,
  
  BUBBLE_VIEW_MODE_ACCOUNT_MANAGEMENT,
  
  BUBBLE_VIEW_MODE_GAIA_SIGNIN,
  
  BUBBLE_VIEW_MODE_GAIA_ADD_ACCOUNT,
  
  BUBBLE_VIEW_MODE_GAIA_REAUTH,
  
  BUBBLE_VIEW_MODE_ACCOUNT_REMOVAL,
  
  BUBBLE_VIEW_MODE_SWITCH_USER,
};

enum TutorialMode {
  
  TUTORIAL_MODE_NONE,
  
  TUTORIAL_MODE_CONFIRM_SIGNIN,
  
  TUTORIAL_MODE_WELCOME_UPGRADE,
  
  TUTORIAL_MODE_SHOW_ERROR,
};

};  

#endif  
