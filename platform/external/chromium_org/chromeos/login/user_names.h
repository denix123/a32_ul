// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_USER_NAMES_H_
#define CHROMEOS_LOGIN_USER_NAMES_H_

#include <string>

#include "chromeos/chromeos_export.h"

namespace chromeos {

namespace login {

CHROMEOS_EXPORT extern const char* kStubUser;

CHROMEOS_EXPORT extern const char* kSignInUser;

CHROMEOS_EXPORT extern const char* kGuestUserName;

CHROMEOS_EXPORT extern const char* kSupervisedUserDomain;

CHROMEOS_EXPORT extern const char* kRetailModeUserName;

CHROMEOS_EXPORT std::string CanonicalizeUserID(const std::string& user_id);

}  

}  

#endif  
