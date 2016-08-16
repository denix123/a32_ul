// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_SIMPLE_EVENT_SUBSCRIBER_H_
#define MEDIA_CAST_LOGGING_SIMPLE_EVENT_SUBSCRIBER_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/threading/thread_checker.h"
#include "media/cast/logging/raw_event_subscriber.h"

namespace media {
namespace cast {

class SimpleEventSubscriber : public RawEventSubscriber {
 public:
  SimpleEventSubscriber();

  virtual ~SimpleEventSubscriber();

  
  virtual void OnReceiveFrameEvent(const FrameEvent& frame_event) OVERRIDE;
  virtual void OnReceivePacketEvent(const PacketEvent& packet_event) OVERRIDE;

  
  
  void GetFrameEventsAndReset(std::vector<FrameEvent>* frame_events);

  
  
  void GetPacketEventsAndReset(std::vector<PacketEvent>* packet_events);

 private:
  std::vector<FrameEvent> frame_events_;
  std::vector<PacketEvent> packet_events_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(SimpleEventSubscriber);
};

}  
}  

#endif  
