// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_CAST_CHANNEL_LOGGER_H_
#define EXTENSIONS_BROWSER_API_CAST_CHANNEL_LOGGER_H_

#include <deque>
#include <map>

#include "base/basictypes.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "extensions/browser/api/cast_channel/cast_socket.h"
#include "extensions/browser/api/cast_channel/logger_util.h"
#include "extensions/common/api/cast_channel/logging.pb.h"
#include "net/base/ip_endpoint.h"

namespace base {
class TickClock;
}

namespace extensions {
namespace core_api {
namespace cast_channel {

struct AuthResult;

static const int kMaxSocketsToLog = 50;
static const int kMaxEventsPerSocket = 2000;

class Logger : public base::RefCounted<Logger> {
 public:
  
  
  
  Logger(scoped_ptr<base::TickClock> clock,
         base::TimeTicks unix_epoch_time_ticks);

  
  
  void LogNewSocketEvent(const CastSocket& cast_socket);

  void LogSocketEvent(int channel_id, proto::EventType event_type);
  void LogSocketEventWithDetails(int channel_id,
                                 proto::EventType event_type,
                                 const std::string& details);

  
  void LogSocketEventWithRv(int channel_id,
                            proto::EventType event_type,
                            int rv);

  
  void LogSocketReadyState(int channel_id, proto::ReadyState new_state);
  void LogSocketConnectState(int channel_id, proto::ConnectionState new_state);
  void LogSocketReadState(int channel_id, proto::ReadState new_state);
  void LogSocketWriteState(int channel_id, proto::WriteState new_state);
  void LogSocketErrorState(int channel_id, proto::ErrorState new_state);

  
  void LogSocketChallengeReplyEvent(int channel_id,
                                    const AuthResult& auth_result);

  void LogSocketEventForMessage(int channel_id,
                                proto::EventType event_type,
                                const std::string& message_namespace,
                                const std::string& details);

  
  
  
  
  scoped_ptr<char[]> GetLogs(size_t* length) const;

  
  void Reset();

  
  
  
  
  LastErrors GetLastErrors(int channel_id) const;

 private:
  friend class base::RefCounted<Logger>;
  ~Logger();

  struct AggregatedSocketEventLog {
   public:
    AggregatedSocketEventLog();
    ~AggregatedSocketEventLog();

    
    
    
    proto::AggregatedSocketEvent aggregated_socket_event;
    
    
    
    std::deque<proto::SocketEvent> socket_events;

    
    LastErrors last_errors;
  };

  typedef std::map<int, linked_ptr<AggregatedSocketEventLog> >
      AggregatedSocketEventLogMap;

  
  
  proto::SocketEvent CreateEvent(proto::EventType event_type);

  
  
  
  
  proto::AggregatedSocketEvent& LogSocketEvent(
      int channel_id,
      const proto::SocketEvent& socket_event);

  scoped_ptr<base::TickClock> clock_;
  AggregatedSocketEventLogMap aggregated_socket_events_;
  base::TimeTicks unix_epoch_time_ticks_;

  
  proto::Log log_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(Logger);
};
}  
}  
}  

#endif  
