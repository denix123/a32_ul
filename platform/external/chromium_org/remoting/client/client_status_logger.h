// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CLIENT_CLIENT_STATUS_LOGGER_H_
#define REMOTING_CLIENT_CLIENT_STATUS_LOGGER_H_

#include "base/threading/non_thread_safe.h"
#include "base/time/time.h"
#include "remoting/protocol/connection_to_host.h"
#include "remoting/protocol/errors.h"
#include "remoting/signaling/log_to_server.h"

namespace remoting {

class ChromotingStats;

class ClientStatusLogger : public base::NonThreadSafe {
 public:
  ClientStatusLogger(ServerLogEntry::Mode mode,
                     SignalStrategy* signal_strategy,
                     const std::string& directory_bot_jid);
  ~ClientStatusLogger();

  void LogSessionStateChange(protocol::ConnectionToHost::State state,
                             protocol::ErrorCode error);
  void LogStatistics(remoting::ChromotingStats* statistics);

  
  void SetSignalingStateForTest(SignalStrategy::State state);

 private:
  LogToServer log_to_server_;

  
  void GenerateSessionId();

  
  void MaybeExpireSessionId();

  
  
  std::string session_id_;

  
  base::TimeTicks session_start_time_;

  
  base::TimeTicks session_id_generation_time_;

  DISALLOW_COPY_AND_ASSIGN(ClientStatusLogger);
};

}  

#endif  
