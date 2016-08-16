// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_COMMON_PROFILE_MANAGEMENT_SWITCHES_H_
#define CHROME_COMMON_PROFILE_MANAGEMENT_SWITCHES_H_

namespace base {
class CommandLine;
}

namespace switches {

bool IsEnableAccountConsistency();

bool IsEnableWebBasedSignin();

bool IsExtensionsMultiAccount();

bool IsFastUserSwitching();

bool IsGoogleProfileInfo();

bool IsNewAvatarMenu();

bool IsNewProfileManagement();

bool IsNewProfileManagementPreviewEnabled();

void EnableNewAvatarMenuForTesting(base::CommandLine* command_line);
void DisableNewAvatarMenuForTesting(base::CommandLine* command_line);
void EnableNewProfileManagementForTesting(base::CommandLine* command_line);
void EnableAccountConsistencyForTesting(base::CommandLine* command_line);

}  

#endif  
