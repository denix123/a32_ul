// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SESSION_SESSION_STATE_DELEGATE_H_
#define ASH_SESSION_SESSION_STATE_DELEGATE_H_

#include <string>
#include <vector>

#include "ash/ash_export.h"
#include "base/strings/string16.h"

namespace aura {
class Window;
}  

namespace content {
class BrowserContext;
}

namespace gfx {
class ImageSkia;
}  

namespace user_manager {
class UserInfo;
}  

namespace ash {

class SessionStateObserver;

typedef int MultiProfileIndex;

typedef std::vector<std::string> UserIdList;

class ASH_EXPORT SessionStateDelegate {
 public:
  
  enum CycleUser {
    CYCLE_TO_NEXT_USER = 0,  
    CYCLE_TO_PREVIOUS_USER,  
  };

  enum AddUserError {
    ADD_USER_ERROR_NOT_ALLOWED_PRIMARY_USER = 0,
    ADD_USER_ERROR_OUT_OF_USERS,
    ADD_USER_ERROR_MAXIMUM_USERS_REACHED,
  };

  
  
  enum SessionState {
    
    
    SESSION_STATE_LOGIN_PRIMARY = 0,

    
    
    SESSION_STATE_ACTIVE,

    
    
    SESSION_STATE_LOGIN_SECONDARY,
  };

  virtual ~SessionStateDelegate() {};

  
  virtual content::BrowserContext* GetBrowserContextByIndex(
      MultiProfileIndex index) = 0;

  
  virtual content::BrowserContext* GetBrowserContextForWindow(
      aura::Window* window) = 0;

  
  virtual int GetMaximumNumberOfLoggedInUsers() const = 0;

  
  
  virtual int NumberOfLoggedInUsers() const = 0;

  
  
  
  virtual bool CanAddUserToMultiProfile(AddUserError* error) const;

  
  
  
  
  virtual bool IsActiveUserSessionStarted() const = 0;

  
  virtual bool CanLockScreen() const = 0;

  
  virtual bool IsScreenLocked() const = 0;

  
  
  virtual bool ShouldLockScreenBeforeSuspending() const = 0;

  
  virtual void LockScreen() = 0;

  
  virtual void UnlockScreen() = 0;

  
  
  
  virtual bool IsUserSessionBlocked() const = 0;

  
  virtual SessionState GetSessionState() const = 0;

  

  
  
  virtual const user_manager::UserInfo* GetUserInfo(
      MultiProfileIndex index) const = 0;

  
  virtual const user_manager::UserInfo* GetUserInfo(
      content::BrowserContext* context) const = 0;

  
  virtual bool ShouldShowAvatar(aura::Window* window) const = 0;

  
  
  virtual void SwitchActiveUser(const std::string& user_id) = 0;

  
  
  virtual void CycleActiveUser(CycleUser cycle_user) = 0;

  
  virtual bool IsMultiProfileAllowedByPrimaryUserPolicy() const = 0;

  
  virtual void AddSessionStateObserver(SessionStateObserver* observer) = 0;
  virtual void RemoveSessionStateObserver(SessionStateObserver* observer) = 0;

  bool IsInSecondaryLoginScreen() const;
};

}  

#endif  
