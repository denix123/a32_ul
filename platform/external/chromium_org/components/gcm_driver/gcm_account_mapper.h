// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_ACCOUNT_MAPPER_H_
#define COMPONENTS_GCM_DRIVER_GCM_ACCOUNT_MAPPER_H_

#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/gcm_driver/gcm_app_handler.h"
#include "components/gcm_driver/gcm_client.h"
#include "google_apis/gcm/engine/account_mapping.h"

namespace base {
class Clock;
}

namespace gcm {

class GCMDriver;

class GCMAccountMapper : public GCMAppHandler {
 public:
  
  typedef std::vector<AccountMapping> AccountMappings;

  explicit GCMAccountMapper(GCMDriver* gcm_driver);
  virtual ~GCMAccountMapper();

  void Initialize(const AccountMappings& account_mappings);

  
  
  void SetAccountTokens(
      const std::vector<GCMClient::AccountTokenInfo> account_tokens);

  
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

 private:
  friend class GCMAccountMapperTest;

  typedef std::map<std::string, GCMClient::OutgoingMessage> OutgoingMessages;

  
  bool IsReady();

  
  void SendAddMappingMessage(AccountMapping& account_mapping);

  
  void SendRemoveMappingMessage(AccountMapping& account_mapping);

  void CreateAndSendMessage(const AccountMapping& account_mapping);

  
  void OnSendFinished(const std::string& account_id,
                      const std::string& message_id,
                      GCMClient::Result result);

  
  void GetRegistration();

  
  void OnRegisterFinished(const std::string& registration_id,
                          GCMClient::Result result);

  
  
  
  bool CanTriggerUpdate(const base::Time& last_update_time) const;

  
  bool IsLastStatusChangeOlderThanTTL(
      const AccountMapping& account_mapping) const;

  
  AccountMapping* FindMappingByAccountId(const std::string& account_id);
  
  
  AccountMappings::iterator FindMappingByMessageId(
      const std::string& message_id);

  
  void SetClockForTesting(scoped_ptr<base::Clock> clock);

  
  GCMDriver* gcm_driver_;

  
  scoped_ptr<base::Clock> clock_;

  
  AccountMappings accounts_;

  std::vector<GCMClient::AccountTokenInfo> pending_account_tokens_;

  
  std::string registration_id_;

  bool initialized_;

  base::WeakPtrFactory<GCMAccountMapper> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GCMAccountMapper);
};

}  

#endif  
