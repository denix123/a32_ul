// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SERVICES_GCM_GCM_PROFILE_SERVICE_H_
#define CHROME_BROWSER_SERVICES_GCM_GCM_PROFILE_SERVICE_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/services/gcm/push_messaging_service_impl.h"
#include "components/gcm_driver/gcm_driver.h"
#include "components/keyed_service/core/keyed_service.h"

class Profile;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace gcm {

class GCMClientFactory;
class GCMDriver;

class GCMProfileService : public KeyedService {
 public:
  
  static bool IsGCMEnabled(Profile* profile);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

#if defined(OS_ANDROID)
  explicit GCMProfileService(Profile* profile);
#else
  GCMProfileService(Profile* profile,
                    scoped_ptr<GCMClientFactory> gcm_client_factory);
#endif
  virtual ~GCMProfileService();

  
  void AddAppHandler(const std::string& app_id, GCMAppHandler* handler);
  void RemoveAppHandler(const std::string& app_id);
  void Register(const std::string& app_id,
                const std::vector<std::string>& sender_ids,
                const GCMDriver::RegisterCallback& callback);

  
  virtual void Shutdown() OVERRIDE;

  
  
  
  std::string SignedInUserName() const;

  
  void SetDriverForTesting(GCMDriver* driver);

  GCMDriver* driver() const { return driver_.get(); }

  content::PushMessagingService* push_messaging_service() {
    return &push_messaging_service_;
  }

 protected:
  
  GCMProfileService();

 private:
  
  Profile* profile_;

  scoped_ptr<GCMDriver> driver_;

  
  PushMessagingServiceImpl push_messaging_service_;

  
#if !defined(OS_ANDROID)
  class IdentityObserver;
  scoped_ptr<IdentityObserver> identity_observer_;
#endif
#if defined(OS_CHROMEOS)
  scoped_ptr<GCMConnectionObserver> chromeos_connection_observer_;
#endif

  DISALLOW_COPY_AND_ASSIGN(GCMProfileService);
};

}  

#endif  
