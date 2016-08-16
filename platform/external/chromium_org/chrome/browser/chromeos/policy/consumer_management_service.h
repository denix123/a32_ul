// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_CONSUMER_MANAGEMENT_SERVICE_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_CONSUMER_MANAGEMENT_SERVICE_H_

#include <string>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#include "chromeos/dbus/dbus_method_call_status.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "google_apis/gaia/oauth2_token_service.h"

class PrefRegistrySimple;
class Profile;

namespace chromeos {
class CryptohomeClient;
}

namespace cryptohome {
class BaseReply;
}

namespace policy {

class EnrollmentStatus;

class ConsumerManagementService
    : public chromeos::DeviceSettingsService::Observer,
      public content::NotificationObserver,
      public OAuth2TokenService::Consumer,
      public OAuth2TokenService::Observer {
 public:
  
  
  
  
  enum Status {
    
    STATUS_UNKNOWN = 0,

    STATUS_ENROLLED,
    STATUS_ENROLLING,
    STATUS_UNENROLLED,
    STATUS_UNENROLLING,

    
    STATUS_LAST,
  };

  
  enum EnrollmentStage {
    
    ENROLLMENT_STAGE_NONE = 0,
    
    ENROLLMENT_STAGE_REQUESTED,
    
    ENROLLMENT_STAGE_OWNER_STORED,
    
    ENROLLMENT_STAGE_SUCCESS,

    
    
    ENROLLMENT_STAGE_CANCELED,
    
    ENROLLMENT_STAGE_BOOT_LOCKBOX_FAILED,
    
    ENROLLMENT_STAGE_GET_TOKEN_FAILED,
    
    ENROLLMENT_STAGE_DM_SERVER_FAILED,

    
    ENROLLMENT_STAGE_LAST,
  };

  class Observer {
   public:
    
    virtual void OnConsumerManagementStatusChanged() = 0;
  };

  
  
  typedef base::Callback<void(const std::string&)> GetOwnerCallback;

  
  typedef base::Callback<void(bool)> SetOwnerCallback;

  
  ConsumerManagementService(
      chromeos::CryptohomeClient* client,
      chromeos::DeviceSettingsService* device_settings_service);

  virtual ~ConsumerManagementService();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  Status GetStatus() const;

  
  std::string GetStatusString() const;

  
  EnrollmentStage GetEnrollmentStage() const;

  
  void SetEnrollmentStage(EnrollmentStage stage);

  
  void GetOwner(const GetOwnerCallback& callback);

  
  
  void SetOwner(const std::string& user_id, const SetOwnerCallback& callback);

  
  virtual void OwnershipStatusChanged() OVERRIDE;
  virtual void DeviceSettingsUpdated() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;

  
  virtual void OnGetTokenSuccess(
      const OAuth2TokenService::Request* request,
      const std::string& access_token,
      const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(
      const OAuth2TokenService::Request* request,
      const GoogleServiceAuthError& error) OVERRIDE;

  OAuth2TokenService::Request* GetTokenRequestForTesting() {
    return token_request_.get();
  }

 private:
  void OnGetBootAttributeDone(
      const GetOwnerCallback& callback,
      chromeos::DBusMethodCallStatus call_status,
      bool dbus_success,
      const cryptohome::BaseReply& reply);

  void OnSetBootAttributeDone(const SetOwnerCallback& callback,
                              chromeos::DBusMethodCallStatus call_status,
                              bool dbus_success,
                              const cryptohome::BaseReply& reply);

  void OnFlushAndSignBootAttributesDone(
      const SetOwnerCallback& callback,
      chromeos::DBusMethodCallStatus call_status,
      bool dbus_success,
      const cryptohome::BaseReply& reply);

  
  void OnOwnerSignin(Profile* profile);

  
  
  void ContinueEnrollmentProcess(Profile* profile);

  
  void OnOwnerRefreshTokenAvailable();

  
  void OnOwnerAccessTokenAvailable(const std::string& access_token);

  
  void OnEnrollmentCompleted(EnrollmentStatus status);

  
  
  void EndEnrollment(EnrollmentStage stage);

  
  void ShowDesktopNotificationAndResetStage(
      EnrollmentStage stage,
      Profile* profile);

  
  void OpenSettingsPage(Profile* profile) const;

  
  void TryEnrollmentAgain(Profile* profile) const;

  void NotifyStatusChanged();

  chromeos::CryptohomeClient* client_;
  chromeos::DeviceSettingsService* device_settings_service_;

  Profile* enrolling_profile_;
  scoped_ptr<OAuth2TokenService::Request> token_request_;
  content::NotificationRegistrar registrar_;
  ObserverList<Observer, true> observers_;
  base::WeakPtrFactory<ConsumerManagementService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ConsumerManagementService);
};

}  

#endif  
