// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_DRIVER_H_
#define COMPONENTS_GCM_DRIVER_GCM_DRIVER_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/macros.h"
#include "base/threading/thread_checker.h"
#include "components/gcm_driver/default_gcm_app_handler.h"
#include "components/gcm_driver/gcm_client.h"

namespace gcm {

class GCMAppHandler;
class GCMConnectionObserver;
struct AccountMapping;

class GCMDriver {
 public:
  typedef std::map<std::string, GCMAppHandler*> GCMAppHandlerMap;
  typedef base::Callback<void(const std::string& registration_id,
                              GCMClient::Result result)> RegisterCallback;
  typedef base::Callback<void(const std::string& message_id,
                              GCMClient::Result result)> SendCallback;
  typedef base::Callback<void(GCMClient::Result result)> UnregisterCallback;
  typedef base::Callback<void(const GCMClient::GCMStatistics& stats)>
      GetGCMStatisticsCallback;

  
  static bool IsAllowedForAllUsers();

  GCMDriver();
  virtual ~GCMDriver();

  
  
  
  
  
  
  
  void Register(const std::string& app_id,
                const std::vector<std::string>& sender_ids,
                const RegisterCallback& callback);

  
  
  
  void Unregister(const std::string& app_id,
                  const UnregisterCallback& callback);

  
  
  
  
  
  void Send(const std::string& app_id,
            const std::string& receiver_id,
            const GCMClient::OutgoingMessage& message,
            const SendCallback& callback);

  const GCMAppHandlerMap& app_handlers() const { return app_handlers_; }

  
  
  virtual void Shutdown();

  
  virtual void OnSignedIn() = 0;
  virtual void OnSignedOut() = 0;

  
  
  virtual void Purge() = 0;

  
  virtual void AddAppHandler(const std::string& app_id, GCMAppHandler* handler);

  
  virtual void RemoveAppHandler(const std::string& app_id);

  
  GCMAppHandler* GetAppHandler(const std::string& app_id);

  
  virtual void AddConnectionObserver(GCMConnectionObserver* observer) = 0;

  
  virtual void RemoveConnectionObserver(GCMConnectionObserver* observer) = 0;

  
  virtual void Enable() = 0;
  virtual void Disable() = 0;

  
  virtual GCMClient* GetGCMClientForTesting() const = 0;

  
  virtual bool IsStarted() const = 0;

  
  virtual bool IsConnected() const = 0;

  
  
  
  virtual void GetGCMStatistics(const GetGCMStatisticsCallback& callback,
                                bool clear_logs) = 0;

  
  virtual void SetGCMRecording(const GetGCMStatisticsCallback& callback,
                               bool recording) = 0;

  
  virtual void UpdateAccountMapping(const AccountMapping& account_mapping) = 0;

  
  
  virtual void RemoveAccountMapping(const std::string& account_id) = 0;

 protected:
  
  virtual GCMClient::Result EnsureStarted() = 0;

  
  virtual void RegisterImpl(const std::string& app_id,
                            const std::vector<std::string>& sender_ids) = 0;

  
  virtual void UnregisterImpl(const std::string& app_id) = 0;

  
  virtual void SendImpl(const std::string& app_id,
                        const std::string& receiver_id,
                        const GCMClient::OutgoingMessage& message) = 0;

  
  void RegisterFinished(const std::string& app_id,
                        const std::string& registration_id,
                        GCMClient::Result result);

  
  void UnregisterFinished(const std::string& app_id,
                          GCMClient::Result result);

  
  void SendFinished(const std::string& app_id,
                    const std::string& message_id,
                    GCMClient::Result result);

  bool HasRegisterCallback(const std::string& app_id);

  void ClearCallbacks();

 private:
  
  
  bool IsAsyncOperationPending(const std::string& app_id) const;

  
  std::map<std::string, RegisterCallback> register_callbacks_;

  
  std::map<std::string, UnregisterCallback> unregister_callbacks_;

  
  std::map<std::pair<std::string, std::string>, SendCallback> send_callbacks_;

  
  
  GCMAppHandlerMap app_handlers_;

  
  DefaultGCMAppHandler default_app_handler_;

  DISALLOW_COPY_AND_ASSIGN(GCMDriver);
};

}  

#endif  
