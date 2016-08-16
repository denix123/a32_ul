// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_LOG_DESERIALIZER_H_
#define MEDIA_CAST_LOGGING_LOG_DESERIALIZER_H_

#include <map>
#include <string>

#include "base/memory/linked_ptr.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/proto/raw_events.pb.h"

namespace media {
namespace cast {

typedef std::map<RtpTimestamp,
                 linked_ptr<media::cast::proto::AggregatedFrameEvent> >
    FrameEventMap;
typedef std::map<RtpTimestamp,
                 linked_ptr<media::cast::proto::AggregatedPacketEvent> >
    PacketEventMap;

struct DeserializedLog {
  DeserializedLog();
  ~DeserializedLog();
  proto::LogMetadata metadata;
  FrameEventMap frame_events;
  PacketEventMap packet_events;
};

bool DeserializeEvents(const char* data,
                       int data_bytes,
                       bool compressed,
                       DeserializedLog* audio_log,
                       DeserializedLog* video_log);

}  
}  

#endif  
