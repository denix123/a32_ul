// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILES_STATE_H_
#define CHROME_BROWSER_PROFILES_PROFILES_STATE_H_

#include <vector>
#include "base/strings/string16.h"

class Browser;
class PrefRegistrySimple;
class Profile;
class SigninErrorController;
namespace base { class FilePath; }

namespace profiles {

bool IsMultipleProfilesEnabled();

base::FilePath GetDefaultProfileDir(const base::FilePath& user_data_dir);

void RegisterPrefs(PrefRegistrySimple* registry);

base::string16 GetAvatarNameForProfile(const base::FilePath& profile_path);

base::string16 GetAvatarButtonTextForProfile(Profile* profile);

void UpdateProfileName(Profile* profile,
                       const base::string16& new_profile_name);

std::vector<std::string> GetSecondaryAccountsForProfile(
    Profile* profile,
    const std::string& primary_account);

bool IsRegularOrGuestSession(Browser* browser);

void UpdateGaiaProfilePhotoIfNeeded(Profile* profile);

SigninErrorController* GetSigninErrorController(Profile* profile);

Profile* SetActiveProfileToGuestIfLocked();

}  

#endif  
