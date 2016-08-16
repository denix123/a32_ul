// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_LOG_SERIALIZER_H_
#define MEDIA_CAST_LOGGING_LOG_SERIALIZER_H_

#include <string>

#include "media/cast/logging/encoding_event_subscriber.h"

namespace media {
namespace cast {

// Result is written to |output|, which can hold |max_output_bytes| of data.
// |output_bytes| will be set to number of bytes written.
bool SerializeEvents(const media::cast::proto::LogMetadata& log_metadata,
                     const FrameEventList& frame_events,
                     const PacketEventList& packet_events,
                     bool compress,
                     int max_output_bytes,
                     char* output,
                     int* output_bytes);

}  
}  

#endif  
