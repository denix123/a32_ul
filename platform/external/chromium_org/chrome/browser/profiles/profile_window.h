// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILE_WINDOW_H_
#define CHROME_BROWSER_PROFILES_PROFILE_WINDOW_H_

#include "base/callback_forward.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/profiles/profile_metrics.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/host_desktop.h"
#include "chrome/browser/ui/profile_chooser_constants.h"
#include "chrome/browser/ui/startup/startup_types.h"

class Profile;
namespace base { class FilePath; }

namespace profiles {

enum UserManagerTutorialMode {
  USER_MANAGER_NO_TUTORIAL,        
  USER_MANAGER_TUTORIAL_OVERVIEW,  
  USER_MANAGER_TUTORIAL_LOCK,      
};

enum UserManagerProfileSelected {
  USER_MANAGER_SELECT_PROFILE_NO_ACTION,
  USER_MANAGER_SELECT_PROFILE_TASK_MANAGER,
  USER_MANAGER_SELECT_PROFILE_ABOUT_CHROME,
};

extern const char kUserManagerDisplayTutorial[];
extern const char kUserManagerSelectProfileTaskManager[];
extern const char kUserManagerSelectProfileAboutChrome[];

void FindOrCreateNewWindowForProfile(
    Profile* profile,
    chrome::startup::IsProcessStartup process_startup,
    chrome::startup::IsFirstRun is_first_run,
    chrome::HostDesktopType desktop_type,
    bool always_create);


void SwitchToProfile(const base::FilePath& path,
                     chrome::HostDesktopType desktop_type,
                     bool always_create,
                     ProfileManager::CreateCallback callback,
                     ProfileMetrics::ProfileOpen metric);

void SwitchToGuestProfile(chrome::HostDesktopType desktop_type,
                          ProfileManager::CreateCallback callback);

void CreateAndSwitchToNewProfile(chrome::HostDesktopType desktop_type,
                                 ProfileManager::CreateCallback callback,
                                 ProfileMetrics::ProfileAdd metric);

void CloseGuestProfileWindows();

void LockProfile(Profile* profile);

void CreateGuestProfileForUserManager(
    const base::FilePath& profile_path_to_focus,
    profiles::UserManagerTutorialMode tutorial_mode,
    profiles::UserManagerProfileSelected profile_open_action,
    const base::Callback<void(Profile*, const std::string&)>& callback);

void ShowUserManagerMaybeWithTutorial(Profile* profile);

void EnableNewProfileManagementPreview(Profile* profile);

void DisableNewProfileManagementPreview(Profile* profile);

void BubbleViewModeFromAvatarBubbleMode(
    BrowserWindow::AvatarBubbleMode mode,
    BubbleViewMode* bubble_view_mode,
    TutorialMode* tutorial_mode);

}  

#endif  
