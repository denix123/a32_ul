// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PROFILES_USER_MANAGER_MAC_H_
#define CHROME_BROWSER_UI_COCOA_PROFILES_USER_MANAGER_MAC_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_window.h"

@class UserManagerWindowController;

namespace content {
class NavigationController;
class WebContents;
}

class UserManagerMac {
 public:
  
  
  void WindowWasClosed();

  
  
  static void OnGuestProfileCreated(Profile* guest_profile,
                                    const std::string& url);

  UserManagerWindowController* window_controller() {
    return window_controller_.get();
  }

 private:
  explicit UserManagerMac(Profile* profile);
  virtual ~UserManagerMac();

  
  base::scoped_nsobject<UserManagerWindowController> window_controller_;

  DISALLOW_COPY_AND_ASSIGN(UserManagerMac);
};

#endif  
