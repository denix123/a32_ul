// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_DRIVER_DESKTOP_H_
#define COMPONENTS_GCM_DRIVER_GCM_DRIVER_DESKTOP_H_

#include <map>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "components/gcm_driver/gcm_channel_status_syncer.h"
#include "components/gcm_driver/gcm_client.h"
#include "components/gcm_driver/gcm_connection_observer.h"
#include "components/gcm_driver/gcm_driver.h"

class PrefService;

namespace base {
class FilePath;
class SequencedTaskRunner;
}

namespace extensions {
class ExtensionGCMAppHandlerTest;
}

namespace net {
class URLRequestContextGetter;
}

namespace gcm {

class GCMAppHandler;
class GCMClientFactory;
class GCMDelayedTaskController;

class GCMDriverDesktop : public GCMDriver {
 public:
  GCMDriverDesktop(
      scoped_ptr<GCMClientFactory> gcm_client_factory,
      const GCMClient::ChromeBuildInfo& chrome_build_info,
      const std::string& channel_status_request_url,
      const std::string& user_agent,
      PrefService* prefs,
      const base::FilePath& store_path,
      const scoped_refptr<net::URLRequestContextGetter>& request_context,
      const scoped_refptr<base::SequencedTaskRunner>& ui_thread,
      const scoped_refptr<base::SequencedTaskRunner>& io_thread,
      const scoped_refptr<base::SequencedTaskRunner>& blocking_task_runner);
  virtual ~GCMDriverDesktop();

  
  virtual void Shutdown() OVERRIDE;
  virtual void OnSignedIn() OVERRIDE;
  virtual void OnSignedOut() OVERRIDE;
  virtual void Purge() OVERRIDE;
  virtual void AddAppHandler(const std::string& app_id,
                             GCMAppHandler* handler) OVERRIDE;
  virtual void RemoveAppHandler(const std::string& app_id) OVERRIDE;
  virtual void AddConnectionObserver(GCMConnectionObserver* observer) OVERRIDE;
  virtual void RemoveConnectionObserver(
      GCMConnectionObserver* observer) OVERRIDE;
  virtual void Enable() OVERRIDE;
  virtual void Disable() OVERRIDE;
  virtual GCMClient* GetGCMClientForTesting() const OVERRIDE;
  virtual bool IsStarted() const OVERRIDE;
  virtual bool IsConnected() const OVERRIDE;
  virtual void GetGCMStatistics(const GetGCMStatisticsCallback& callback,
                                bool clear_logs) OVERRIDE;
  virtual void SetGCMRecording(const GetGCMStatisticsCallback& callback,
                               bool recording) OVERRIDE;
  virtual void UpdateAccountMapping(
      const AccountMapping& account_mapping) OVERRIDE;
  virtual void RemoveAccountMapping(const std::string& account_id) OVERRIDE;

  
  
  
  
  
  
  void SetAccountsForCheckin(
      const std::map<std::string, std::string>& account_tokens);

  
  bool gcm_enabled() const { return gcm_enabled_; }
  GCMChannelStatusSyncer* gcm_channel_status_syncer_for_testing() {
    return gcm_channel_status_syncer_.get();
  }

 protected:
  
  virtual GCMClient::Result EnsureStarted() OVERRIDE;
  virtual void RegisterImpl(
      const std::string& app_id,
      const std::vector<std::string>& sender_ids) OVERRIDE;
  virtual void UnregisterImpl(const std::string& app_id) OVERRIDE;
  virtual void SendImpl(const std::string& app_id,
                        const std::string& receiver_id,
                        const GCMClient::OutgoingMessage& message) OVERRIDE;

 private:
  class IOWorker;

  
  void Stop();

  
  void RemoveCachedData();

  void DoRegister(const std::string& app_id,
                  const std::vector<std::string>& sender_ids);
  void DoUnregister(const std::string& app_id);
  void DoSend(const std::string& app_id,
              const std::string& receiver_id,
              const GCMClient::OutgoingMessage& message);

  
  void MessageReceived(const std::string& app_id,
                       const GCMClient::IncomingMessage& message);
  void MessagesDeleted(const std::string& app_id);
  void MessageSendError(const std::string& app_id,
                        const GCMClient::SendErrorDetails& send_error_details);
  void SendAcknowledged(const std::string& app_id,
                        const std::string& message_id);
  void GCMClientReady(
      const std::vector<AccountMapping>& account_mappings);
  void OnConnected(const net::IPEndPoint& ip_endpoint);
  void OnDisconnected();

  void GetGCMStatisticsFinished(const GCMClient::GCMStatistics& stats);

  scoped_ptr<GCMChannelStatusSyncer> gcm_channel_status_syncer_;

  
  
  bool signed_in_;

  
  bool gcm_started_;

  
  
  bool gcm_enabled_;

  
  
  
  bool connected_;

  
  
  ObserverList<GCMConnectionObserver, true> connection_observer_list_;

  scoped_refptr<base::SequencedTaskRunner> ui_thread_;
  scoped_refptr<base::SequencedTaskRunner> io_thread_;

  scoped_ptr<GCMDelayedTaskController> delayed_task_controller_;

  
  
  scoped_ptr<IOWorker> io_worker_;

  
  GetGCMStatisticsCallback request_gcm_statistics_callback_;

  
  base::WeakPtrFactory<GCMDriverDesktop> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GCMDriverDesktop);
};

}  

#endif  
