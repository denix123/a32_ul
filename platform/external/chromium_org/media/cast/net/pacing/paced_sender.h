// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_NET_PACING_PACED_SENDER_H_
#define MEDIA_CAST_NET_PACING_PACED_SENDER_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/single_thread_task_runner.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/default_tick_clock.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/net/cast_transport_config.h"

namespace media {
namespace cast {

static const size_t kTargetBurstSize = 10;
static const size_t kMaxBurstSize = 20;

class LoggingImpl;

typedef std::pair<base::TimeTicks, std::pair<uint32, uint16> > PacketKey;
typedef std::vector<std::pair<PacketKey, PacketRef> > SendPacketVector;

struct DedupInfo {
  DedupInfo();
  base::TimeDelta resend_interval;
  int64 last_byte_acked_for_audio;
};

class PacedPacketSender {
 public:
  virtual bool SendPackets(const SendPacketVector& packets) = 0;
  virtual bool ResendPackets(const SendPacketVector& packets,
                             const DedupInfo& dedup_info) = 0;
  virtual bool SendRtcpPacket(uint32 ssrc, PacketRef packet) = 0;
  virtual void CancelSendingPacket(const PacketKey& packet_key) = 0;

  virtual ~PacedPacketSender() {}

  static PacketKey MakePacketKey(const base::TimeTicks& ticks,
                                 uint32 ssrc,
                                 uint16 packet_id);
};

class PacedSender : public PacedPacketSender,
                    public base::NonThreadSafe,
                    public base::SupportsWeakPtr<PacedSender> {
 public:
  
  
  PacedSender(
      size_t target_burst_size,  
      size_t max_burst_size,     
      base::TickClock* clock,
      LoggingImpl* logging,
      PacketSender* external_transport,
      const scoped_refptr<base::SingleThreadTaskRunner>& transport_task_runner);

  virtual ~PacedSender();

  
  void RegisterAudioSsrc(uint32 audio_ssrc);
  void RegisterVideoSsrc(uint32 video_ssrc);

  
  
  
  
  void RegisterPrioritySsrc(uint32 ssrc);

  
  
  
  int64 GetLastByteSentForPacket(const PacketKey& packet_key);

  
  
  int64 GetLastByteSentForSsrc(uint32 ssrc);

  
  virtual bool SendPackets(const SendPacketVector& packets) OVERRIDE;
  virtual bool ResendPackets(const SendPacketVector& packets,
                             const DedupInfo& dedup_info) OVERRIDE;
  virtual bool SendRtcpPacket(uint32 ssrc, PacketRef packet) OVERRIDE;
  virtual void CancelSendingPacket(const PacketKey& packet_key) OVERRIDE;

 private:
  
  void SendStoredPackets();
  void LogPacketEvent(const Packet& packet, CastLoggingEvent event);

  
  
  
  
  bool ShouldResend(const PacketKey& packet_key,
                    const DedupInfo& dedup_info,
                    const base::TimeTicks& now);

  enum PacketType {
    PacketType_RTCP,
    PacketType_Resend,
    PacketType_Normal
  };
  enum State {
    
    
    
    State_Unblocked,
    
    
    
    
    State_TransportBlocked,
    // Once we've written enough packets for a time slice, we go into this
    
    
    State_BurstFull
  };

  bool empty() const;
  size_t size() const;

  
  
  
  PacketRef PopNextPacket(PacketType* packet_type,
                          PacketKey* packet_key);

  
  bool IsHighPriority(const PacketKey& packet_key) const;

  base::TickClock* const clock_;  
  LoggingImpl* const logging_;    
  PacketSender* transport_;       
  scoped_refptr<base::SingleThreadTaskRunner> transport_task_runner_;
  uint32 audio_ssrc_;
  uint32 video_ssrc_;

  
  
  std::vector<uint32> priority_ssrcs_;
  typedef std::map<PacketKey, std::pair<PacketType, PacketRef> > PacketList;
  PacketList packet_list_;
  PacketList priority_packet_list_;

  struct PacketSendRecord {
    PacketSendRecord();
    base::TimeTicks time;  
    int64 last_byte_sent;  
                           
    int64 last_byte_sent_for_audio;  
                                     
  };
  typedef std::map<PacketKey, PacketSendRecord> PacketSendHistory;
  PacketSendHistory send_history_;
  PacketSendHistory send_history_buffer_;
  
  std::map<uint32, int64> last_byte_sent_;

  size_t target_burst_size_;
  size_t max_burst_size_;

  
  size_t current_max_burst_size_;
  size_t next_max_burst_size_;
  size_t next_next_max_burst_size_;
  
  size_t current_burst_size_;
  
  base::TimeTicks burst_end_;

  State state_;

  bool has_reached_upper_bound_once_;

  
  base::WeakPtrFactory<PacedSender> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PacedSender);
};

}  
}  

#endif  
