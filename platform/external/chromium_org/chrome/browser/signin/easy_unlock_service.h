// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SERVICE_H_
#define CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SERVICE_H_

#include <set>
#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/signin/easy_unlock_screenlock_state_handler.h"
#include "components/keyed_service/core/keyed_service.h"

#if defined(OS_CHROMEOS)
#include "chrome/browser/chromeos/login/easy_unlock/easy_unlock_types.h"
#endif

namespace base {
class DictionaryValue;
class ListValue;
}

namespace user_manager {
class User;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class EasyUnlockAuthAttempt;
class EasyUnlockServiceObserver;
class Profile;
class PrefRegistrySimple;

class EasyUnlockService : public KeyedService {
 public:
  enum TurnOffFlowStatus {
    IDLE,
    PENDING,
    FAIL,
  };

  enum Type {
    TYPE_REGULAR,
    TYPE_SIGNIN
  };

  
  static EasyUnlockService* Get(Profile* profile);

  
  
  static EasyUnlockService* GetForUser(const user_manager::User& user);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  static void ResetLocalStateForUser(const std::string& user_id);

  
  static bool IsSignInEnabled();

  
  virtual Type GetType() const = 0;

  
  virtual std::string GetUserEmail() const = 0;

  
  virtual void LaunchSetup() = 0;

  
  virtual const base::DictionaryValue* GetPermitAccess() const = 0;
  virtual void SetPermitAccess(const base::DictionaryValue& permit) = 0;
  virtual void ClearPermitAccess() = 0;

  
  virtual const base::ListValue* GetRemoteDevices() const = 0;
  virtual void SetRemoteDevices(const base::ListValue& devices) = 0;
  virtual void ClearRemoteDevices() = 0;

  
  virtual void RunTurnOffFlow() = 0;

  
  virtual void ResetTurnOffFlow() = 0;

  
  virtual TurnOffFlowStatus GetTurnOffFlowStatus() const = 0;

  
  
  virtual std::string GetChallenge() const = 0;

  
  
  
  
  virtual std::string GetWrappedSecret() const = 0;

  
  virtual void RecordEasySignInOutcome(const std::string& user_id,
                                       bool success) const = 0;

  
  virtual void RecordPasswordLoginEvent(const std::string& user_id) const = 0;

  
  
  
  bool IsAllowed();

  
  void SetHardlockState(EasyUnlockScreenlockStateHandler::HardlockState state);

  
  EasyUnlockScreenlockStateHandler::HardlockState GetHardlockState() const;

  
  
  
  bool GetPersistedHardlockState(
      EasyUnlockScreenlockStateHandler::HardlockState* state) const;

  
  
  void ShowInitialUserState();

  
  
  bool UpdateScreenlockState(EasyUnlockScreenlockStateHandler::State state);

  
  
  void AttemptAuth(const std::string& user_id);

  
  
  
  void FinalizeUnlock(bool success);

  
  
  
  void FinalizeSignin(const std::string& secret);

  
  
  void CheckCryptohomeKeysAndMaybeHardlock();

  
  
  void SetTrialRun();

  void AddObserver(EasyUnlockServiceObserver* observer);
  void RemoveObserver(EasyUnlockServiceObserver* observer);

 protected:
  explicit EasyUnlockService(Profile* profile);
  virtual ~EasyUnlockService();

  
  virtual void InitializeInternal() = 0;

  
  virtual void ShutdownInternal() = 0;

  
  
  
  virtual bool IsAllowedInternal() = 0;

  
  virtual void Shutdown() OVERRIDE;

  
  Profile* profile() const { return profile_; }

  
  
  void LoadApp();

  
  void DisableAppIfLoaded();

  
  void UnloadApp();

  
  void ReloadApp();

  
  void UpdateAppState();

  
  void NotifyUserUpdated();

  
  void NotifyTurnOffOperationStatusChanged();

  
  void ResetScreenlockState();

  
  void SetScreenlockHardlockedState(
      EasyUnlockScreenlockStateHandler::HardlockState state);

  const EasyUnlockScreenlockStateHandler* screenlock_state_handler() const {
    return screenlock_state_handler_.get();
  }

  
  
  void SetHardlockStateForUser(
      const std::string& user_id,
      EasyUnlockScreenlockStateHandler::HardlockState state);

 private:
  
  class BluetoothDetector;

  
  void Initialize();

  
  
  
  
  EasyUnlockScreenlockStateHandler* GetScreenlockStateHandler();

  
  void OnBluetoothAdapterPresentChanged();

#if defined(OS_CHROMEOS)
  
  void OnCryptohomeKeysFetchedForChecking(
      const std::string& user_id,
      const std::set<std::string> paired_devices,
      bool success,
      const chromeos::EasyUnlockDeviceKeyDataList& key_data_list);
#endif

  
  void PrepareForSuspend();

  Profile* profile_;

  
  scoped_ptr<EasyUnlockScreenlockStateHandler> screenlock_state_handler_;

  
  
  scoped_ptr<EasyUnlockAuthAttempt> auth_attempt_;

  scoped_ptr<BluetoothDetector> bluetooth_detector_;

#if defined(OS_CHROMEOS)
  
  class PowerMonitor;
  scoped_ptr<PowerMonitor> power_monitor_;
#endif

  
  bool shut_down_;

  ObserverList<EasyUnlockServiceObserver> observers_;

  base::WeakPtrFactory<EasyUnlockService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EasyUnlockService);
};

#endif  
