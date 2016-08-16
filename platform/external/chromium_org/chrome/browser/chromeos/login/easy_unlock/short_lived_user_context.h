// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_EASY_UNLOCK_SHORT_LIVED_USER_CONTEXT_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_EASY_UNLOCK_SHORT_LIVED_USER_CONTEXT_H_

#include "apps/app_lifetime_monitor.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"

namespace base {
class TaskRunner;
}

namespace chromeos {

class UserContext;

class ShortLivedUserContext : public apps::AppLifetimeMonitor::Observer {
 public:
  ShortLivedUserContext(const UserContext& user_context,
                        apps::AppLifetimeMonitor* app_lifetime_monitor,
                        base::TaskRunner* task_runner);
  virtual ~ShortLivedUserContext();

  
  UserContext* user_context() { return user_context_.get(); }

 private:
  void Reset();

  
  virtual void OnAppDeactivated(Profile* profile,
                                const std::string& app_id) override;

  scoped_ptr<UserContext> user_context_;

  apps::AppLifetimeMonitor* app_lifetime_monitor_;

  base::WeakPtrFactory<ShortLivedUserContext> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ShortLivedUserContext);
};

}  

#endif  
