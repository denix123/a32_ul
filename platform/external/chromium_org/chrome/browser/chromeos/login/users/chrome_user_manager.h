// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_CHROME_USER_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_CHROME_USER_MANAGER_H_

#include "base/basictypes.h"
#include "components/user_manager/user_manager_base.h"

namespace base {
class TaskRunner;
}

namespace chromeos {

class MultiProfileUserController;
class SupervisedUserManager;
class UserFlow;
class UserImageManager;

class ChromeUserManager : public user_manager::UserManagerBase {
 public:
  ChromeUserManager(scoped_refptr<base::TaskRunner> task_runner,
                    scoped_refptr<base::TaskRunner> blocking_task_runner);
  virtual ~ChromeUserManager();

  
  
  static ChromeUserManager* Get();

  virtual MultiProfileUserController* GetMultiProfileUserController() = 0;
  virtual UserImageManager* GetUserImageManager(const std::string& user_id) = 0;
  virtual SupervisedUserManager* GetSupervisedUserManager() = 0;

  
  
  
  
  virtual void SetUserFlow(const std::string& user_id, UserFlow* flow) = 0;

  
  
  
  virtual UserFlow* GetCurrentUserFlow() const = 0;

  
  
  
  virtual UserFlow* GetUserFlow(const std::string& user_id) const = 0;

  
  virtual void ResetUserFlow(const std::string& user_id) = 0;

  DISALLOW_COPY_AND_ASSIGN(ChromeUserManager);
};

}  

#endif  
