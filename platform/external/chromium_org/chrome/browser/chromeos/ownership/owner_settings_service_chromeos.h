// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_OWNERSHIP_OWNER_SETTINGS_SERVICE_CHROMEOS_H_
#define CHROME_BROWSER_CHROMEOS_OWNERSHIP_OWNER_SETTINGS_SERVICE_CHROMEOS_H_

#include <deque>
#include <vector>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#include "chromeos/dbus/session_manager_client.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/ownership/owner_key_util.h"
#include "components/ownership/owner_settings_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class Profile;

namespace ownership {
class OwnerKeyUtil;
}

namespace chromeos {

class SessionManagerOperation;

class OwnerSettingsServiceChromeOS : public ownership::OwnerSettingsService,
                                     public content::NotificationObserver,
                                     public SessionManagerClient::Observer {
 public:
  virtual ~OwnerSettingsServiceChromeOS();

  void OnTPMTokenReady(bool tpm_token_enabled);

  
  virtual void SignAndStorePolicyAsync(
      scoped_ptr<enterprise_management::PolicyData> policy,
      const base::Closure& callback) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OwnerKeySet(bool success) OVERRIDE;

  
  
  static void IsOwnerForSafeModeAsync(
      const std::string& user_hash,
      const scoped_refptr<ownership::OwnerKeyUtil>& owner_key_util,
      const IsOwnerCallback& callback);

  static void SetDeviceSettingsServiceForTesting(
      DeviceSettingsService* device_settings_service);

 private:
  friend class OwnerSettingsServiceChromeOSFactory;

  OwnerSettingsServiceChromeOS(
      Profile* profile,
      const scoped_refptr<ownership::OwnerKeyUtil>& owner_key_util);

  

  
  virtual void ReloadKeypairImpl(const base::Callback<
      void(const scoped_refptr<ownership::PublicKey>& public_key,
           const scoped_refptr<ownership::PrivateKey>& private_key)>& callback)
      OVERRIDE;

  
  virtual void OnPostKeypairLoadedActions() OVERRIDE;

  
  void StartNextOperation();

  
  void HandleCompletedOperation(const base::Closure& callback,
                                SessionManagerOperation* operation,
                                DeviceSettingsService::Status status);

  
  Profile* profile_;

  
  std::string user_id_;

  
  bool waiting_for_profile_creation_;

  
  bool waiting_for_tpm_token_;

  
  
  std::deque<SessionManagerOperation*> pending_operations_;

  content::NotificationRegistrar registrar_;

  base::WeakPtrFactory<OwnerSettingsServiceChromeOS> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(OwnerSettingsServiceChromeOS);
};

}  

#endif  
