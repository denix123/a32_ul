// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_ENCODING_EVENT_SUBSCRIBER_H_
#define MEDIA_CAST_LOGGING_ENCODING_EVENT_SUBSCRIBER_H_

#include <map>

#include "base/memory/linked_ptr.h"
#include "base/threading/thread_checker.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/proto/raw_events.pb.h"
#include "media/cast/logging/raw_event_subscriber.h"

namespace media {
namespace cast {

static const int kMaxPacketsPerFrame = 64;
static const int kMaxEventsPerProto = 16;

typedef std::vector<linked_ptr<media::cast::proto::AggregatedFrameEvent> >
    FrameEventList;
typedef std::vector<linked_ptr<media::cast::proto::AggregatedPacketEvent> >
    PacketEventList;

class EncodingEventSubscriber : public RawEventSubscriber {
 public:
  
  
  
  
  
  
  
  
  EncodingEventSubscriber(EventMediaType event_media_type, size_t max_frames);

  virtual ~EncodingEventSubscriber();

  
  virtual void OnReceiveFrameEvent(const FrameEvent& frame_event) OVERRIDE;
  virtual void OnReceivePacketEvent(const PacketEvent& packet_event) OVERRIDE;

  
  
  
  
  
  void GetEventsAndReset(media::cast::proto::LogMetadata* metadata,
                         FrameEventList* frame_events,
                         PacketEventList* packet_events);

 private:
  typedef std::map<RtpTimestamp,
                   linked_ptr<media::cast::proto::AggregatedFrameEvent> >
      FrameEventMap;
  typedef std::map<RtpTimestamp,
                   linked_ptr<media::cast::proto::AggregatedPacketEvent> >
      PacketEventMap;

  
  
  
  void TransferFrameEvents(size_t max_num_entries);
  
  void TransferPacketEvents(size_t max_num_entries);

  void AddFrameEventToStorage(
      const linked_ptr<media::cast::proto::AggregatedFrameEvent>&
          frame_event_proto);
  void AddPacketEventToStorage(
      const linked_ptr<media::cast::proto::AggregatedPacketEvent>&
          packet_event_proto);

  
  
  RtpTimestamp GetRelativeRtpTimestamp(RtpTimestamp rtp_timestamp);

  
  void Reset();

  const EventMediaType event_media_type_;
  const size_t max_frames_;

  FrameEventMap frame_event_map_;
  FrameEventList frame_event_storage_;
  int frame_event_storage_index_;

  PacketEventMap packet_event_map_;
  PacketEventList packet_event_storage_;
  int packet_event_storage_index_;

  
  base::ThreadChecker thread_checker_;

  
  bool seen_first_rtp_timestamp_;

  
  RtpTimestamp first_rtp_timestamp_;

  DISALLOW_COPY_AND_ASSIGN(EncodingEventSubscriber);
};

}  
}  

#endif  
