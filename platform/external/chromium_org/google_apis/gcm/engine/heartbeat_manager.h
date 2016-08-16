// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_HEARTBEAT_MANAGER_H_
#define GOOGLE_APIS_GCM_ENGINE_HEARTBEAT_MANAGER_H_

#include "base/callback.h"
#include "base/logging.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "google_apis/gcm/base/gcm_export.h"

namespace mcs_proto {
class HeartbeatConfig;
}

namespace gcm {

class GCM_EXPORT HeartbeatManager {
 public:
  HeartbeatManager();
  ~HeartbeatManager();

  
  
  
  void Start(const base::Closure& send_heartbeat_callback,
             const base::Closure& trigger_reconnect_callback);

  
  
  void Stop();

  
  
  
  void OnHeartbeatAcked();

  
  void UpdateHeartbeatConfig(const mcs_proto::HeartbeatConfig& config);

  
  
  
  
  base::TimeTicks GetNextHeartbeatTime() const;

 protected:
  
  void OnHeartbeatTriggered();

 private:
  
  void RestartTimer();

  
  bool waiting_for_ack_;

  
  int heartbeat_interval_ms_;
  
  
  int server_interval_ms_;

  
  base::Timer heartbeat_timer_;

  
  base::Closure send_heartbeat_callback_;
  base::Closure trigger_reconnect_callback_;

  base::WeakPtrFactory<HeartbeatManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HeartbeatManager);
};

}  

#endif  
