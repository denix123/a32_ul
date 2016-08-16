// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_CAST_DEFINES_H_
#define MEDIA_CAST_CAST_DEFINES_H_

#include <stdint.h>

#include <map>
#include <set>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/time/time.h"
#include "media/cast/net/cast_transport_config.h"

namespace media {
namespace cast {

const int64 kDontShowTimeoutMs = 33;
const float kDefaultCongestionControlBackOff = 0.875f;
const uint32 kVideoFrequency = 90000;
const uint32 kStartFrameId = UINT32_C(0xffffffff);

const int kMaxUnackedFrames = 120;

const int64 kCastMessageUpdateIntervalMs = 33;
const int64 kNackRepeatIntervalMs = 30;

enum CastInitializationStatus {
  STATUS_AUDIO_UNINITIALIZED,
  STATUS_VIDEO_UNINITIALIZED,
  STATUS_AUDIO_INITIALIZED,
  STATUS_VIDEO_INITIALIZED,
  STATUS_INVALID_CAST_ENVIRONMENT,
  STATUS_INVALID_CRYPTO_CONFIGURATION,
  STATUS_UNSUPPORTED_AUDIO_CODEC,
  STATUS_UNSUPPORTED_VIDEO_CODEC,
  STATUS_INVALID_AUDIO_CONFIGURATION,
  STATUS_INVALID_VIDEO_CONFIGURATION,
  STATUS_HW_VIDEO_ENCODER_NOT_SUPPORTED,
};

enum DefaultSettings {
  kDefaultAudioEncoderBitrate = 0,  
  kDefaultAudioSamplingRate = 48000,
  kDefaultMaxQp = 56,
  kDefaultMinQp = 4,
  kDefaultMaxFrameRate = 30,
  kDefaultNumberOfVideoBuffers = 1,
  kDefaultRtcpIntervalMs = 500,
  kDefaultRtpHistoryMs = 1000,
  kDefaultRtpMaxDelayMs = 100,
};

enum PacketType {
  kNewPacket,
  kNewPacketCompletingFrame,
  kDuplicatePacket,
  kTooOldPacket,
};

const uint16 kRtcpCastAllPacketsLost = 0xffff;

const uint16 kRtcpCastLastPacket = 0xfffe;

const size_t kMinLengthOfRtcp = 8;

const size_t kMinLengthOfRtp = 12 + 6;

typedef std::set<uint16> PacketIdSet;
typedef std::map<uint8, PacketIdSet> MissingFramesAndPacketsMap;


static const int64 kUnixEpochInNtpSeconds = INT64_C(2208988800);

static const double kMagicFractionalUnit = 4.294967296E3;

static const size_t kReceiverRtcpEventHistorySize = 512;

inline bool IsNewerFrameId(uint32 frame_id, uint32 prev_frame_id) {
  return (frame_id != prev_frame_id) &&
         static_cast<uint32>(frame_id - prev_frame_id) < 0x80000000;
}

inline bool IsNewerRtpTimestamp(uint32 timestamp, uint32 prev_timestamp) {
  return (timestamp != prev_timestamp) &&
         static_cast<uint32>(timestamp - prev_timestamp) < 0x80000000;
}

inline bool IsOlderFrameId(uint32 frame_id, uint32 prev_frame_id) {
  return (frame_id == prev_frame_id) || IsNewerFrameId(prev_frame_id, frame_id);
}

inline bool IsNewerPacketId(uint16 packet_id, uint16 prev_packet_id) {
  return (packet_id != prev_packet_id) &&
         static_cast<uint16>(packet_id - prev_packet_id) < 0x8000;
}

inline bool IsNewerSequenceNumber(uint16 sequence_number,
                                  uint16 prev_sequence_number) {
  
  return IsNewerPacketId(sequence_number, prev_sequence_number);
}

inline uint32 ConvertToNtpDiff(uint32 delay_seconds, uint32 delay_fraction) {
  return ((delay_seconds & 0x0000FFFF) << 16) +
         ((delay_fraction & 0xFFFF0000) >> 16);
}

inline base::TimeDelta ConvertFromNtpDiff(uint32 ntp_delay) {
  uint32 delay_ms = (ntp_delay & 0x0000ffff) * 1000;
  delay_ms >>= 16;
  delay_ms += ((ntp_delay & 0xffff0000) >> 16) * 1000;
  return base::TimeDelta::FromMilliseconds(delay_ms);
}

inline void ConvertTimeToFractions(int64 ntp_time_us,
                                   uint32* seconds,
                                   uint32* fractions) {
  DCHECK_GE(ntp_time_us, 0) << "Time must NOT be negative";
  const int64 seconds_component =
      ntp_time_us / base::Time::kMicrosecondsPerSecond;
  
  
  
  
  DCHECK_LT(seconds_component, INT64_C(4263431296))
      << "One year left to fix the NTP year 2036 wrap-around issue!";
  *seconds = static_cast<uint32>(seconds_component);
  *fractions = static_cast<uint32>(
      (ntp_time_us % base::Time::kMicrosecondsPerSecond) *
          kMagicFractionalUnit);
}

inline void ConvertTimeTicksToNtp(const base::TimeTicks& time,
                                  uint32* ntp_seconds,
                                  uint32* ntp_fractions) {
  base::TimeDelta elapsed_since_unix_epoch =
      time - base::TimeTicks::UnixEpoch();

  int64 ntp_time_us =
      elapsed_since_unix_epoch.InMicroseconds() +
      (kUnixEpochInNtpSeconds * base::Time::kMicrosecondsPerSecond);

  ConvertTimeToFractions(ntp_time_us, ntp_seconds, ntp_fractions);
}

inline base::TimeTicks ConvertNtpToTimeTicks(uint32 ntp_seconds,
                                             uint32 ntp_fractions) {
  int64 ntp_time_us =
      static_cast<int64>(ntp_seconds) * base::Time::kMicrosecondsPerSecond +
      static_cast<int64>(ntp_fractions) / kMagicFractionalUnit;

  base::TimeDelta elapsed_since_unix_epoch = base::TimeDelta::FromMicroseconds(
      ntp_time_us -
      (kUnixEpochInNtpSeconds * base::Time::kMicrosecondsPerSecond));
  return base::TimeTicks::UnixEpoch() + elapsed_since_unix_epoch;
}

inline base::TimeDelta RtpDeltaToTimeDelta(int64 rtp_delta, int rtp_timebase) {
  DCHECK_GT(rtp_timebase, 0);
  return rtp_delta * base::TimeDelta::FromSeconds(1) / rtp_timebase;
}

inline int64 TimeDeltaToRtpDelta(base::TimeDelta delta, int rtp_timebase) {
  DCHECK_GT(rtp_timebase, 0);
  return delta * rtp_timebase / base::TimeDelta::FromSeconds(1);
}

}  
}  

#endif  