// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CONSTANTS_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CONSTANTS_H_

#include <string>

namespace chromeos {

extern const char kSupervisedUserTokenFilename[];

extern const char kCryptohomeSupervisedUserKeyLabel[];
extern const char kCryptohomeMasterKeyLabel[];
extern const char kLegacyCryptohomeSupervisedUserKeyLabel[];
extern const char kLegacyCryptohomeMasterKeyLabel[];

extern const int kCryptohomeSupervisedUserKeyPrivileges;

extern const int kCryptohomeSupervisedUserIncompleteKeyPrivileges;

}  

#endif  
