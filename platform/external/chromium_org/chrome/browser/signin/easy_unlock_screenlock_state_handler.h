// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SCREENLOCK_STATE_HANDLER_H_
#define CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SCREENLOCK_STATE_HANDLER_H_

#include <string>

#include "base/strings/string16.h"
#include "base/timer/timer.h"
#include "chrome/browser/signin/screenlock_bridge.h"

class PrefService;

class EasyUnlockScreenlockStateHandler : public ScreenlockBridge::Observer {
 public:
  
  enum State {
    
    STATE_INACTIVE,
    
    STATE_NO_BLUETOOTH,
    
    STATE_BLUETOOTH_CONNECTING,
    
    STATE_NO_PHONE,
    
    
    STATE_PHONE_NOT_AUTHENTICATED,
    
    STATE_PHONE_LOCKED,
    
    
    STATE_PHONE_UNLOCKABLE,
    
    
    STATE_PHONE_NOT_NEARBY,
    
    
    STATE_PHONE_UNSUPPORTED,
    
    STATE_AUTHENTICATED
  };

  
  enum HardlockState {
    NO_HARDLOCK = 0,           
    USER_HARDLOCK = 1 << 0,    
    PAIRING_CHANGED = 1 << 1,  
    NO_PAIRING = 1 << 2,       
    LOGIN_FAILED = 1 << 3,     
                               
    PAIRING_ADDED = 1 << 4,    
                               
  };

  
  
  
  
  
  EasyUnlockScreenlockStateHandler(const std::string& user_email,
                                   HardlockState initial_hardlock_state,
                                   ScreenlockBridge* screenlock_bridge);
  virtual ~EasyUnlockScreenlockStateHandler();

  
  bool IsActive() const;

  
  
  void ChangeState(State new_state);

  
  void SetHardlockState(HardlockState new_state);

  
  void MaybeShowHardlockUI();

  
  void SetTrialRun();

  State state() const { return state_; }

 private:
  
  virtual void OnScreenDidLock() OVERRIDE;
  virtual void OnScreenDidUnlock() OVERRIDE;
  virtual void OnFocusedUserChanged(const std::string& user_id) OVERRIDE;

  
  void RefreshScreenlockState();

  void ShowHardlockUI();

  
  
  void UpdateTooltipOptions(
      bool trial_run,
      ScreenlockBridge::UserPodCustomIconOptions* icon_options);

  
  
  base::string16 GetDeviceName();

  
  void UpdateScreenlockAuthType();

  State state_;
  std::string user_email_;
  ScreenlockBridge* screenlock_bridge_;

  
  HardlockState hardlock_state_;
  bool hardlock_ui_shown_;

  
  
  
  bool is_trial_run_;

  DISALLOW_COPY_AND_ASSIGN(EasyUnlockScreenlockStateHandler);
};

#endif  
