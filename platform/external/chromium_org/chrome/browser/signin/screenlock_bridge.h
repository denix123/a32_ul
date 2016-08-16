// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SCREENLOCK_BRIDGE_H_
#define CHROME_BROWSER_SIGNIN_SCREENLOCK_BRIDGE_H_

#include <string>

#include "base/basictypes.h"
#include "base/lazy_instance.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "base/values.h"


class Profile;

class ScreenlockBridge {
 public:
  class Observer {
   public:
    
    virtual void OnScreenDidLock() = 0;
    
    virtual void OnScreenDidUnlock() = 0;
    
    virtual void OnFocusedUserChanged(const std::string& user_id) = 0;
   protected:
    virtual ~Observer() {}
  };

  
  enum UserPodCustomIcon {
    USER_POD_CUSTOM_ICON_NONE,
    USER_POD_CUSTOM_ICON_HARDLOCKED,
    USER_POD_CUSTOM_ICON_LOCKED,
    USER_POD_CUSTOM_ICON_UNLOCKED,
    USER_POD_CUSTOM_ICON_SPINNER
  };

  
  
  class UserPodCustomIconOptions {
   public:
    UserPodCustomIconOptions();
    ~UserPodCustomIconOptions();

    
    
    scoped_ptr<base::DictionaryValue> ToDictionaryValue() const;

    
    void SetIcon(UserPodCustomIcon icon);

    
    
    void SetTooltip(const base::string16& tooltip, bool autoshow);

    
    
    void SetAriaLabel(const base::string16& aria_label);

    
    
    void SetHardlockOnClick();

   private:
    UserPodCustomIcon icon_;

    base::string16 tooltip_;
    bool autoshow_tooltip_;

    base::string16 aria_label_;

    bool hardlock_on_click_;

    DISALLOW_COPY_AND_ASSIGN(UserPodCustomIconOptions);
  };

  class LockHandler {
   public:
    
    
    enum AuthType {
      OFFLINE_PASSWORD = 0,
      ONLINE_SIGN_IN = 1,
      NUMERIC_PIN = 2,
      USER_CLICK = 3,
      EXPAND_THEN_USER_CLICK = 4,
      FORCE_OFFLINE_PASSWORD = 5
    };

    
    virtual void ShowBannerMessage(const base::string16& message) = 0;

    
    virtual void ShowUserPodCustomIcon(
        const std::string& user_email,
        const UserPodCustomIconOptions& icon) = 0;

    
    virtual void HideUserPodCustomIcon(const std::string& user_email) = 0;

    
    virtual void EnableInput() = 0;

    
    virtual void SetAuthType(const std::string& user_email,
                             AuthType auth_type,
                             const base::string16& auth_value) = 0;

    
    virtual AuthType GetAuthType(const std::string& user_email) const = 0;

    
    virtual void Unlock(const std::string& user_email) = 0;

    
    virtual void AttemptEasySignin(const std::string& user_email,
                                   const std::string& secret,
                                   const std::string& key_label) = 0;

   protected:
    virtual ~LockHandler() {}
  };

  static ScreenlockBridge* Get();
  static std::string GetAuthenticatedUserEmail(Profile* profile);

  void SetLockHandler(LockHandler* lock_handler);
  void SetFocusedUser(const std::string& user_id);

  bool IsLocked() const;
  void Lock(Profile* profile);
  void Unlock(Profile* profile);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  LockHandler* lock_handler() { return lock_handler_; }

  std::string focused_user_id() const { return focused_user_id_; }

 private:
  friend struct base::DefaultLazyInstanceTraits<ScreenlockBridge>;
  friend struct base::DefaultDeleter<ScreenlockBridge>;

  ScreenlockBridge();
  ~ScreenlockBridge();

  LockHandler* lock_handler_;  
  
  std::string focused_user_id_;
  ObserverList<Observer, true> observers_;

  DISALLOW_COPY_AND_ASSIGN(ScreenlockBridge);
};

#endif  
