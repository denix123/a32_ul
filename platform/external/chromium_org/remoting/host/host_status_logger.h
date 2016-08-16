// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_HOST_STATUS_LOGGER_H_
#define REMOTING_HOST_HOST_STATUS_LOGGER_H_

#include <map>

#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "remoting/host/host_status_observer.h"
#include "remoting/protocol/transport.h"
#include "remoting/signaling/log_to_server.h"

namespace remoting {

class HostStatusMonitor;

class HostStatusLogger : public HostStatusObserver,
                         public base::NonThreadSafe {
 public:
  HostStatusLogger(base::WeakPtr<HostStatusMonitor> monitor,
                  ServerLogEntry::Mode mode,
                  SignalStrategy* signal_strategy,
                  const std::string& directory_bot_jid);
  virtual ~HostStatusLogger();

  
  
  void LogSessionStateChange(const std::string& jid, bool connected);

  
  virtual void OnClientConnected(const std::string& jid) OVERRIDE;
  virtual void OnClientDisconnected(const std::string& jid) OVERRIDE;
  virtual void OnClientRouteChange(
      const std::string& jid,
      const std::string& channel_name,
      const protocol::TransportRoute& route) OVERRIDE;

  
  void SetSignalingStateForTest(SignalStrategy::State state);

 private:
  LogToServer log_to_server_;

  base::WeakPtr<HostStatusMonitor> monitor_;

  
  
  std::map<std::string, protocol::TransportRoute::RouteType>
      connection_route_type_;

  DISALLOW_COPY_AND_ASSIGN(HostStatusLogger);
};

}  

#endif  
