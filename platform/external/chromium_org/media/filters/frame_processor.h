// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_FRAME_PROCESSOR_H_
#define MEDIA_FILTERS_FRAME_PROCESSOR_H_

#include <map>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/base/stream_parser.h"
#include "media/filters/chunk_demuxer.h"

namespace media {

class MseTrackBuffer;

class MEDIA_EXPORT FrameProcessor {
 public:
  typedef base::Callback<void(base::TimeDelta)> UpdateDurationCB;

  
  
  
  
  enum {
    kAudioTrackId = -2,
    kVideoTrackId = -3
  };

  explicit FrameProcessor(const UpdateDurationCB& update_duration_cb);
  ~FrameProcessor();

  
  
  
  bool sequence_mode() { return sequence_mode_; }
  void SetSequenceMode(bool sequence_mode);

  
  
  
  
  
  
  
  
  
  
  bool ProcessFrames(const StreamParser::BufferQueue& audio_buffers,
                     const StreamParser::BufferQueue& video_buffers,
                     const StreamParser::TextBufferQueueMap& text_map,
                     base::TimeDelta append_window_start,
                     base::TimeDelta append_window_end,
                     bool* new_media_segment,
                     base::TimeDelta* timestamp_offset);

  
  
  void SetGroupStartTimestampIfInSequenceMode(base::TimeDelta timestamp_offset);

  
  
  
  
  bool AddTrack(StreamParser::TrackId id, ChunkDemuxerStream* stream);

  
  
  
  
  
  bool UpdateTrack(StreamParser::TrackId old_id, StreamParser::TrackId new_id);

  
  void SetAllTrackBuffersNeedRandomAccessPoint();

  
  
  
  void Reset();

  
  
  
  void OnPossibleAudioConfigUpdate(const AudioDecoderConfig& config);

 private:
  typedef std::map<StreamParser::TrackId, MseTrackBuffer*> TrackBufferMap;

  
  
  MseTrackBuffer* FindTrack(StreamParser::TrackId id);

  
  
  void NotifyNewMediaSegmentStarting(DecodeTimestamp segment_timestamp);

  
  
  
  bool FlushProcessedFrames();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool HandlePartialAppendWindowTrimming(
      base::TimeDelta append_window_start,
      base::TimeDelta append_window_end,
      const scoped_refptr<StreamParserBuffer>& buffer);

  
  
  bool ProcessFrame(const scoped_refptr<StreamParserBuffer>& frame,
                    base::TimeDelta append_window_start,
                    base::TimeDelta append_window_end,
                    base::TimeDelta* timestamp_offset,
                    bool* new_media_segment);

  
  TrackBufferMap track_buffers_;

  
  
  scoped_refptr<StreamParserBuffer> audio_preroll_buffer_;

  
  AudioDecoderConfig current_audio_config_;
  base::TimeDelta sample_duration_;

  
  
  
  
  
  bool sequence_mode_;

  
  
  base::TimeDelta group_start_timestamp_;

  
  
  
  
  base::TimeDelta group_end_timestamp_;

  UpdateDurationCB update_duration_cb_;

  DISALLOW_COPY_AND_ASSIGN(FrameProcessor);
};

}  

#endif  
