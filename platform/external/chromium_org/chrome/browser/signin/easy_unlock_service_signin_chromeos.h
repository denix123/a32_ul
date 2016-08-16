// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SERVICE_SIGNIN_CHROMEOS_H_
#define CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SERVICE_SIGNIN_CHROMEOS_H_

#include <map>
#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "chrome/browser/chromeos/login/easy_unlock/easy_unlock_types.h"
#include "chrome/browser/signin/easy_unlock_service.h"
#include "chrome/browser/signin/screenlock_bridge.h"
#include "chromeos/login/login_state.h"

class EasyUnlockServiceSignin : public EasyUnlockService,
                                public ScreenlockBridge::Observer,
                                public chromeos::LoginState::Observer {
 public:
  explicit EasyUnlockServiceSignin(Profile* profile);
  virtual ~EasyUnlockServiceSignin();

 private:
  
  enum UserDataState {
    
    USER_DATA_STATE_INITIAL,
    
    USER_DATA_STATE_LOADING,
    
    USER_DATA_STATE_LOADED
  };

  
  struct UserData {
    UserData();
    ~UserData();

    
    UserDataState state;

    
    chromeos::EasyUnlockDeviceKeyDataList devices;

    
    
    base::ListValue remote_devices_value;

   private:
    DISALLOW_COPY_AND_ASSIGN(UserData);
  };

  
  virtual EasyUnlockService::Type GetType() const OVERRIDE;
  virtual std::string GetUserEmail() const OVERRIDE;
  virtual void LaunchSetup() OVERRIDE;
  virtual const base::DictionaryValue* GetPermitAccess() const OVERRIDE;
  virtual void SetPermitAccess(const base::DictionaryValue& permit) OVERRIDE;
  virtual void ClearPermitAccess() OVERRIDE;
  virtual const base::ListValue* GetRemoteDevices() const OVERRIDE;
  virtual void SetRemoteDevices(const base::ListValue& devices) OVERRIDE;
  virtual void ClearRemoteDevices() OVERRIDE;
  virtual void RunTurnOffFlow() OVERRIDE;
  virtual void ResetTurnOffFlow() OVERRIDE;
  virtual TurnOffFlowStatus GetTurnOffFlowStatus() const OVERRIDE;
  virtual std::string GetChallenge() const OVERRIDE;
  virtual std::string GetWrappedSecret() const OVERRIDE;
  virtual void RecordEasySignInOutcome(const std::string& user_id,
                                       bool success) const OVERRIDE;
  virtual void RecordPasswordLoginEvent(
      const std::string& user_id) const OVERRIDE;
  virtual void InitializeInternal() OVERRIDE;
  virtual void ShutdownInternal() OVERRIDE;
  virtual bool IsAllowedInternal() OVERRIDE;

  
  virtual void OnScreenDidLock() OVERRIDE;
  virtual void OnScreenDidUnlock() OVERRIDE;
  virtual void OnFocusedUserChanged(const std::string& user_id) OVERRIDE;

  
  virtual void LoggedInStateChanged() OVERRIDE;

  
  
  void LoadCurrentUserDataIfNeeded();

  
  void OnUserDataLoaded(
      const std::string& user_id,
      bool success,
      const chromeos::EasyUnlockDeviceKeyDataList& data);

  
  
  const UserData* FindLoadedDataForCurrentUser() const;

  
  std::string user_id_;

  
  std::map<std::string, UserData*> user_data_;

  
  
  
  
  bool allow_cryptohome_backoff_;

  
  
  bool service_active_;

  base::WeakPtrFactory<EasyUnlockServiceSignin> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EasyUnlockServiceSignin);
};

#endif  
