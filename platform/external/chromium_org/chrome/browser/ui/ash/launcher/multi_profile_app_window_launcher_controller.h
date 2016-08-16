// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_LAUNCHER_MULTI_PROFILE_APP_WINDOW_LAUNCHER_CONTROLLER_H_
#define CHROME_BROWSER_UI_ASH_LAUNCHER_MULTI_PROFILE_APP_WINDOW_LAUNCHER_CONTROLLER_H_

#include "chrome/browser/ui/ash/launcher/app_window_launcher_controller.h"

class MultiProfileAppWindowLauncherController
    : public AppWindowLauncherController {
 public:
  explicit MultiProfileAppWindowLauncherController(
      ChromeLauncherController* owner);
  virtual ~MultiProfileAppWindowLauncherController();

  
  virtual void ActiveUserChanged(const std::string& user_email) OVERRIDE;
  virtual void AdditionalUserAddedToSession(Profile* profile) OVERRIDE;

  
  virtual void OnAppWindowAdded(extensions::AppWindow* app_window) OVERRIDE;
  virtual void OnAppWindowRemoved(extensions::AppWindow* app_window) OVERRIDE;
  virtual void OnAppWindowShown(extensions::AppWindow* app_window) OVERRIDE;
  virtual void OnAppWindowHidden(extensions::AppWindow* app_window) OVERRIDE;

 private:
  typedef std::vector<extensions::AppWindow*> AppWindowList;
  typedef std::vector<extensions::AppWindowRegistry*> AppWindowRegistryList;

  
  
  bool UserHasAppOnActiveDesktop(extensions::AppWindow* app_window);

  
  AppWindowList app_window_list_;

  
  AppWindowRegistryList multi_user_registry_;

  DISALLOW_COPY_AND_ASSIGN(MultiProfileAppWindowLauncherController);
};

#endif  
