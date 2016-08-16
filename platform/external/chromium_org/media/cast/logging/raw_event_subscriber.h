// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_RAW_EVENT_SUBSCRIBER_H_
#define MEDIA_CAST_LOGGING_RAW_EVENT_SUBSCRIBER_H_

#include "media/cast/logging/logging_defines.h"

namespace media {
namespace cast {

class RawEventSubscriber {
 public:
  virtual ~RawEventSubscriber() {}

  
  virtual void OnReceiveFrameEvent(const FrameEvent& frame_event) = 0;

  
  
  virtual void OnReceivePacketEvent(const PacketEvent& packet_event) = 0;
};

}  
}  

#endif  
