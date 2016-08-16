// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_TEST_SESSION_STATE_DELEGATE_H_
#define ASH_TEST_TEST_SESSION_STATE_DELEGATE_H_

#include <vector>

#include "ash/session/session_state_delegate.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/gfx/image/image_skia.h"

namespace ash {
namespace test {

class MockUserInfo;

class TestSessionStateDelegate : public SessionStateDelegate {
 public:
  TestSessionStateDelegate();
  virtual ~TestSessionStateDelegate();

  void set_logged_in_users(int users) { logged_in_users_ = users; }
  void AddUser(const std::string user_id);
  const user_manager::UserInfo* GetActiveUserInfo() const;

  
  virtual content::BrowserContext* GetBrowserContextByIndex(
      MultiProfileIndex index) OVERRIDE;
  virtual content::BrowserContext* GetBrowserContextForWindow(
      aura::Window* window) OVERRIDE;
  virtual int GetMaximumNumberOfLoggedInUsers() const OVERRIDE;
  virtual int NumberOfLoggedInUsers() const OVERRIDE;
  virtual bool IsActiveUserSessionStarted() const OVERRIDE;
  virtual bool CanLockScreen() const OVERRIDE;
  virtual bool IsScreenLocked() const OVERRIDE;
  virtual bool ShouldLockScreenBeforeSuspending() const OVERRIDE;
  virtual void LockScreen() OVERRIDE;
  virtual void UnlockScreen() OVERRIDE;
  virtual bool IsUserSessionBlocked() const OVERRIDE;
  virtual SessionState GetSessionState() const OVERRIDE;
  virtual const user_manager::UserInfo* GetUserInfo(
      ash::MultiProfileIndex index) const OVERRIDE;
  virtual const user_manager::UserInfo* GetUserInfo(
      content::BrowserContext* context) const OVERRIDE;
  virtual bool ShouldShowAvatar(aura::Window* window) const OVERRIDE;
  virtual void SwitchActiveUser(const std::string& user_id) OVERRIDE;
  virtual void CycleActiveUser(CycleUser cycle_user) OVERRIDE;
  virtual bool IsMultiProfileAllowedByPrimaryUserPolicy() const OVERRIDE;
  virtual void AddSessionStateObserver(
      ash::SessionStateObserver* observer) OVERRIDE;
  virtual void RemoveSessionStateObserver(
      ash::SessionStateObserver* observer) OVERRIDE;

  

  
  
  
  
  void SetHasActiveUser(bool has_active_user);

  
  
  
  
  void SetActiveUserSessionStarted(bool active_user_session_started);

  
  
  
  void SetCanLockScreen(bool can_lock_screen);

  
  void SetShouldLockScreenBeforeSuspending(bool should_lock);

  
  
  void SetUserAddingScreenRunning(bool user_adding_screen_running);

  
  void SetUserImage(const gfx::ImageSkia& user_image);

 private:
  
  bool has_active_user_;

  
  
  
  bool active_user_session_started_;

  
  
  bool can_lock_screen_;

  
  bool should_lock_screen_before_suspending_;

  
  bool screen_locked_;

  
  bool user_adding_screen_running_;

  
  int logged_in_users_;

  
  int active_user_index_;

  std::vector<MockUserInfo*> user_list_;

  DISALLOW_COPY_AND_ASSIGN(TestSessionStateDelegate);
};

}  
}  

#endif  
