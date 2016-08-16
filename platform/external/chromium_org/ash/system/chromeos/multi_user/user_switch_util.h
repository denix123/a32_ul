// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_MULTI_USER_MULTI_USER_SWITCH_UTIL_H_
#define ASH_SYSTEM_CHROMEOS_MULTI_USER_MULTI_USER_SWITCH_UTIL_H_

#include "ash/ash_export.h"
#include "base/callback.h"

namespace ash {

void ASH_EXPORT TrySwitchingActiveUser(
    const base::Callback<void()> switch_user);

bool ASH_EXPORT TestAndTerminateDesktopCastingWarningForTest(bool accept);

}  

#endif  
