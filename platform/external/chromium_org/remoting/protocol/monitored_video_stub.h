// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_MONITORED_VIDEO_STUB_H_
#define REMOTING_PROTOCOL_MONITORED_VIDEO_STUB_H_

#include "base/callback.h"
#include "base/threading/thread_checker.h"
#include "base/timer/timer.h"
#include "remoting/protocol/video_stub.h"

namespace base {
class ThreadChecker;
} 

namespace remoting {
namespace protocol {

class MonitoredVideoStub : public VideoStub {
 public:
  
  
  typedef base::Callback<void(bool connected)> ChannelStateCallback;

  static const int kConnectivityCheckDelaySeconds = 2;

  MonitoredVideoStub(
      VideoStub* video_stub,
      base::TimeDelta connectivity_check_delay,
      const ChannelStateCallback& callback);
  virtual ~MonitoredVideoStub();

  
  virtual void ProcessVideoPacket(scoped_ptr<VideoPacket> packet,
                                  const base::Closure& done) OVERRIDE;

 private:
  void OnConnectivityCheckTimeout();
  void NotifyChannelState(bool connected);

  VideoStub* video_stub_;
  ChannelStateCallback callback_;
  base::ThreadChecker thread_checker_;
  bool is_connected_;
  base::DelayTimer<MonitoredVideoStub> connectivity_check_timer_;

  DISALLOW_COPY_AND_ASSIGN(MonitoredVideoStub);
};

}  
}  

#endif  
