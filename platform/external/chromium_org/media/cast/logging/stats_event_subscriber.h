// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_STATS_EVENT_SUBSCRIBER_H_
#define MEDIA_CAST_LOGGING_STATS_EVENT_SUBSCRIBER_H_

#include "base/gtest_prod_util.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/tick_clock.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/raw_event_subscriber.h"
#include "media/cast/logging/receiver_time_offset_estimator.h"

namespace base {
class DictionaryValue;
class ListValue;
}

namespace media {
namespace cast {

class StatsEventSubscriberTest;

class StatsEventSubscriber : public RawEventSubscriber {
 public:
  StatsEventSubscriber(EventMediaType event_media_type,
                       base::TickClock* clock,
                       ReceiverTimeOffsetEstimator* offset_estimator);

  virtual ~StatsEventSubscriber();

  
  virtual void OnReceiveFrameEvent(const FrameEvent& frame_event) OVERRIDE;
  virtual void OnReceivePacketEvent(const PacketEvent& packet_event) OVERRIDE;

  
  
  
  
  
  scoped_ptr<base::DictionaryValue> GetStats() const;

  
  void Reset();

 private:
  friend class StatsEventSubscriberTest;
  FRIEND_TEST_ALL_PREFIXES(StatsEventSubscriberTest, EmptyStats);
  FRIEND_TEST_ALL_PREFIXES(StatsEventSubscriberTest, CaptureEncode);
  FRIEND_TEST_ALL_PREFIXES(StatsEventSubscriberTest, Encode);
  FRIEND_TEST_ALL_PREFIXES(StatsEventSubscriberTest, Decode);
  FRIEND_TEST_ALL_PREFIXES(StatsEventSubscriberTest, PlayoutDelay);
  FRIEND_TEST_ALL_PREFIXES(StatsEventSubscriberTest, E2ELatency);
  FRIEND_TEST_ALL_PREFIXES(StatsEventSubscriberTest, Packets);

  static const size_t kMaxFrameInfoMapSize = 100;

  
  
  
  struct FrameLogStats {
    FrameLogStats();
    ~FrameLogStats();
    int event_counter;
    size_t sum_size;
    base::TimeDelta sum_delay;
  };

  struct PacketLogStats {
    PacketLogStats();
    ~PacketLogStats();
    int event_counter;
    size_t sum_size;
  };

  class SimpleHistogram {
   public:
    
    
    
    
    
    
    
    
    
    SimpleHistogram(int64 min, int64 max, int64 width);

    ~SimpleHistogram();

    void Add(int64 sample);

    void Reset();

    scoped_ptr<base::ListValue> GetHistogram() const;

   private:
    int64 min_;
    int64 max_;
    int64 width_;
    std::vector<int> buckets_;
  };

  enum CastStat {
    
    CAPTURE_FPS,
    
    ENCODE_FPS,
    
    DECODE_FPS,
    
    
    
    AVG_ENCODE_TIME_MS,
    
    AVG_PLAYOUT_DELAY_MS,
    
    
    AVG_NETWORK_LATENCY_MS,
    
    AVG_E2E_LATENCY_MS,
    
    ENCODE_KBPS,
    
    TRANSMISSION_KBPS,
    
    RETRANSMISSION_KBPS,
    
    PACKET_LOSS_FRACTION,
    
    MS_SINCE_LAST_RECEIVER_RESPONSE,
    
    NUM_FRAMES_CAPTURED,
    
    NUM_FRAMES_DROPPED_BY_ENCODER,
    
    NUM_FRAMES_LATE,
    
    NUM_PACKETS_SENT,
    
    NUM_PACKETS_RETRANSMITTED,
    
    NUM_PACKETS_RTX_REJECTED,
    
    FIRST_EVENT_TIME_MS,
    
    LAST_EVENT_TIME_MS,

    
    CAPTURE_LATENCY_MS_HISTO,
    ENCODE_LATENCY_MS_HISTO,
    PACKET_LATENCY_MS_HISTO,
    FRAME_LATENCY_MS_HISTO,
    PLAYOUT_DELAY_MS_HISTO
  };

  struct FrameInfo {
    FrameInfo();
    ~FrameInfo();

    base::TimeTicks capture_time;
    base::TimeTicks capture_end_time;
    base::TimeTicks encode_time;
    bool encoded;
  };

  typedef std::map<CastStat, double> StatsMap;
  typedef std::map<CastStat, linked_ptr<SimpleHistogram> > HistogramMap;
  typedef std::map<RtpTimestamp, FrameInfo> FrameInfoMap;
  typedef std::map<
      std::pair<RtpTimestamp, uint16>,
      std::pair<base::TimeTicks, CastLoggingEvent> >
      PacketEventTimeMap;
  typedef std::map<CastLoggingEvent, FrameLogStats> FrameStatsMap;
  typedef std::map<CastLoggingEvent, PacketLogStats> PacketStatsMap;

  static const char* CastStatToString(CastStat stat);

  void InitHistograms();

  
  void GetStatsInternal(StatsMap* stats_map) const;

  void UpdateFirstLastEventTime(base::TimeTicks timestamp,
                                bool is_receiver_event);
  bool GetReceiverOffset(base::TimeDelta* offset);
  void MaybeInsertFrameInfo(RtpTimestamp rtp_timestamp,
                            const FrameInfo& frame_info);
  void RecordFrameCaptureTime(const FrameEvent& frame_event);
  void RecordCaptureLatency(const FrameEvent& frame_event);
  void RecordEncodeLatency(const FrameEvent& frame_event);
  void RecordFrameTxLatency(const FrameEvent& frame_event);
  void RecordE2ELatency(const FrameEvent& frame_event);
  void RecordPacketSentTime(const PacketEvent& packet_event);
  void ErasePacketSentTime(const PacketEvent& packet_event);
  void RecordNetworkLatency(const PacketEvent& packet_event);
  void UpdateLastResponseTime(base::TimeTicks receiver_time);

  void PopulateFpsStat(base::TimeTicks now,
                       CastLoggingEvent event,
                       CastStat stat,
                       StatsMap* stats_map) const;
  void PopulateFrameCountStat(CastLoggingEvent event,
                              CastStat stat,
                              StatsMap* stats_map) const;
  void PopulatePacketCountStat(CastLoggingEvent event,
                               CastStat stat,
                               StatsMap* stats_map) const;
  void PopulatePlayoutDelayStat(StatsMap* stats_map) const;
  void PopulateFrameBitrateStat(base::TimeTicks now, StatsMap* stats_map) const;
  void PopulatePacketBitrateStat(base::TimeTicks now,
                                 CastLoggingEvent event,
                                 CastStat stat,
                                 StatsMap* stats_map) const;
  void PopulatePacketLossPercentageStat(StatsMap* stats_map) const;

  const EventMediaType event_media_type_;

  
  base::TickClock* const clock_;

  
  ReceiverTimeOffsetEstimator* const offset_estimator_;

  FrameStatsMap frame_stats_;
  PacketStatsMap packet_stats_;

  base::TimeDelta total_network_latency_;
  int network_latency_datapoints_;
  base::TimeDelta total_e2e_latency_;
  int e2e_latency_datapoints_;

  base::TimeTicks last_response_received_time_;

  int num_frames_dropped_by_encoder_;
  int num_frames_late_;

  
  FrameInfoMap recent_frame_infos_;

  
  PacketEventTimeMap packet_sent_times_;

  
  base::TimeTicks start_time_;
  base::TimeTicks first_event_time_;
  base::TimeTicks last_event_time_;

  HistogramMap histograms_;

  base::ThreadChecker thread_checker_;
  DISALLOW_COPY_AND_ASSIGN(StatsEventSubscriber);
};

}  
}  

#endif  
