// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SERVICES_GCM_PUSH_MESSAGING_SERVICE_IMPL_H_
#define CHROME_BROWSER_SERVICES_GCM_PUSH_MESSAGING_SERVICE_IMPL_H_

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "components/gcm_driver/gcm_app_handler.h"
#include "components/gcm_driver/gcm_client.h"
#include "content/public/browser/push_messaging_service.h"
#include "content/public/common/push_messaging_status.h"

class Profile;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace gcm {

class GCMProfileService;
struct PushMessagingApplicationId;

class PushMessagingServiceImpl : public content::PushMessagingService,
                                 public GCMAppHandler {
 public:
  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  static void InitializeForProfile(Profile* profile);

  PushMessagingServiceImpl(GCMProfileService* gcm_profile_service,
                           Profile* profile);
  virtual ~PushMessagingServiceImpl();

  
  virtual void ShutdownHandler() OVERRIDE;
  virtual void OnMessage(const std::string& app_id,
                         const GCMClient::IncomingMessage& message) OVERRIDE;
  virtual void OnMessagesDeleted(const std::string& app_id) OVERRIDE;
  virtual void OnSendError(
      const std::string& app_id,
      const GCMClient::SendErrorDetails& send_error_details) OVERRIDE;
  virtual void OnSendAcknowledged(const std::string& app_id,
                                  const std::string& message_id) OVERRIDE;
  virtual bool CanHandle(const std::string& app_id) const OVERRIDE;

  
  virtual void Register(
      const GURL& origin,
      int64 service_worker_registration_id,
      const std::string& sender_id,
      int renderer_id,
      int render_frame_id,
      bool user_gesture,
      const content::PushMessagingService::RegisterCallback& callback) OVERRIDE;

 private:
  void DeliverMessageCallback(const PushMessagingApplicationId& application_id,
                              const GCMClient::IncomingMessage& message,
                              content::PushMessagingStatus status);

  void RegisterEnd(
      const content::PushMessagingService::RegisterCallback& callback,
      const std::string& registration_id,
      content::PushMessagingStatus status);

  void DidRegister(
      const content::PushMessagingService::RegisterCallback& callback,
      const std::string& registration_id,
      GCMClient::Result result);

  void DidRequestPermission(
      const PushMessagingApplicationId& application_id,
      const std::string& sender_id,
      const content::PushMessagingService::RegisterCallback& callback,
      bool allow);

  GCMProfileService* gcm_profile_service_;  

  Profile* profile_;  

  base::WeakPtrFactory<PushMessagingServiceImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PushMessagingServiceImpl);
};

}  

#endif  
