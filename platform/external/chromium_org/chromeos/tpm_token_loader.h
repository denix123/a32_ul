// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_TPM_TOKEN_LOADER_H_
#define CHROMEOS_TPM_TOKEN_LOADER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_method_call_status.h"
#include "chromeos/login/login_state.h"

namespace base {
class SequencedTaskRunner;
}

namespace chromeos {

class CHROMEOS_EXPORT TPMTokenLoader : public LoginState::Observer {
 public:
  enum TPMTokenStatus {
    TPM_TOKEN_STATUS_UNDETERMINED,
    TPM_TOKEN_STATUS_ENABLED,
    TPM_TOKEN_STATUS_DISABLED
  };

  typedef base::Callback<void(bool)> TPMReadyCallback;
  typedef std::vector<TPMReadyCallback> TPMReadyCallbackList;

  
  
  static void Initialize();

  
  static void InitializeForTest();

  
  static void Shutdown();

  
  static TPMTokenLoader* Get();

  
  static bool IsInitialized();

  
  
  
  
  void SetCryptoTaskRunner(
      const scoped_refptr<base::SequencedTaskRunner>& crypto_task_runner);

  
  
  TPMTokenStatus IsTPMTokenEnabled(const TPMReadyCallback& callback);

  std::string tpm_user_pin() const { return tpm_user_pin_; }

 private:
  explicit TPMTokenLoader(bool for_test);
  virtual ~TPMTokenLoader();

  bool IsTPMLoadingEnabled() const;

  
  
  void MaybeStartTokenInitialization();

  
  void ContinueTokenInitialization();
  void OnTPMTokenEnabledForNSS();
  void OnTpmIsEnabled(DBusMethodCallStatus call_status,
                      bool tpm_is_enabled);
  void OnPkcs11IsTpmTokenReady(DBusMethodCallStatus call_status,
                               bool is_tpm_token_ready);
  void OnPkcs11GetTpmTokenInfo(DBusMethodCallStatus call_status,
                               const std::string& token_name,
                               const std::string& user_pin,
                               int token_slot_id);
  void OnTPMTokenInitialized(bool success);

  
  
  void RetryTokenInitializationLater();

  
  void NotifyTPMTokenReady();

  
  virtual void LoggedInStateChanged() OVERRIDE;

  bool initialized_for_test_;

  TPMReadyCallbackList tpm_ready_callback_list_;

  
  
  enum TPMTokenState {
    TPM_STATE_UNKNOWN,
    TPM_INITIALIZATION_STARTED,
    TPM_TOKEN_ENABLED_FOR_NSS,
    TPM_DISABLED,
    TPM_ENABLED,
    TPM_TOKEN_READY,
    TPM_TOKEN_INFO_RECEIVED,
    TPM_TOKEN_INITIALIZED,
  };
  TPMTokenState tpm_token_state_;

  
  
  base::TimeDelta tpm_request_delay_;

  
  int tpm_token_slot_id_;
  std::string tpm_user_pin_;

  base::ThreadChecker thread_checker_;

  
  scoped_refptr<base::SequencedTaskRunner> crypto_task_runner_;

  base::WeakPtrFactory<TPMTokenLoader> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(TPMTokenLoader);
};

}  

#endif  
