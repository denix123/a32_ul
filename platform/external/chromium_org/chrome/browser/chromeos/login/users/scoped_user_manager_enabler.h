// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_SCOPED_USER_MANAGER_ENABLER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_SCOPED_USER_MANAGER_ENABLER_H_

#include "base/basictypes.h"

namespace user_manager {
class UserManager;
}

namespace chromeos {

class ScopedUserManagerEnabler {
 public:
  
  explicit ScopedUserManagerEnabler(user_manager::UserManager* user_manager);
  ~ScopedUserManagerEnabler();

 private:
  user_manager::UserManager* previous_user_manager_;

  DISALLOW_COPY_AND_ASSIGN(ScopedUserManagerEnabler);
};

}  

#endif  
