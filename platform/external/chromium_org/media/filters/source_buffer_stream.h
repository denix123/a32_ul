// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_FILTERS_SOURCE_BUFFER_STREAM_H_
#define MEDIA_FILTERS_SOURCE_BUFFER_STREAM_H_

#include <deque>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/ref_counted.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/media_export.h"
#include "media/base/media_log.h"
#include "media/base/ranges.h"
#include "media/base/stream_parser_buffer.h"
#include "media/base/text_track_config.h"
#include "media/base/video_decoder_config.h"

namespace media {

class SourceBufferRange;

class MEDIA_EXPORT SourceBufferStream {
 public:
  typedef StreamParser::BufferQueue BufferQueue;

  
  
  
  
  
  enum Status {
    kSuccess,
    kNeedBuffer,
    kConfigChange,
    kEndOfStream
  };

  enum Type {
    kAudio,
    kVideo,
    kText
  };

  SourceBufferStream(const AudioDecoderConfig& audio_config,
                     const LogCB& log_cb,
                     bool splice_frames_enabled);
  SourceBufferStream(const VideoDecoderConfig& video_config,
                     const LogCB& log_cb,
                     bool splice_frames_enabled);
  SourceBufferStream(const TextTrackConfig& text_config,
                     const LogCB& log_cb,
                     bool splice_frames_enabled);

  ~SourceBufferStream();

  
  
  
  
  void OnNewMediaSegment(DecodeTimestamp media_segment_start_time);

  
  
  
  
  
  
  bool Append(const BufferQueue& buffers);

  
  
  
  
  
  
  
  void Remove(base::TimeDelta start, base::TimeDelta end,
              base::TimeDelta duration);

  
  
  void Seek(base::TimeDelta timestamp);

  
  
  bool IsSeekPending() const;

  
  
  void OnSetDuration(base::TimeDelta duration);

  
  
  
  
  
  
  
  
  Status GetNextBuffer(scoped_refptr<StreamParserBuffer>* out_buffer);

  
  Ranges<base::TimeDelta> GetBufferedTime() const;

  
  
  
  base::TimeDelta GetBufferedDuration() const;

  
  void MarkEndOfStream();

  
  void UnmarkEndOfStream();

  const AudioDecoderConfig& GetCurrentAudioDecoderConfig();
  const VideoDecoderConfig& GetCurrentVideoDecoderConfig();
  const TextTrackConfig& GetCurrentTextTrackConfig();

  
  
  bool UpdateAudioConfig(const AudioDecoderConfig& config);

  
  
  bool UpdateVideoConfig(const VideoDecoderConfig& config);

  
  
  
  base::TimeDelta GetMaxInterbufferDistance() const;

  void set_memory_limit(int memory_limit) {
    memory_limit_ = memory_limit;
  }

 private:
  friend class SourceBufferStreamTest;

  typedef std::list<SourceBufferRange*> RangeList;

  
  void GarbageCollectIfNeeded();

  
  
  
  
  int FreeBuffers(int total_bytes_to_free, bool reverse_direction);

  
  
  
  int FreeBuffersAfterLastAppended(int total_bytes_to_free);

  
  
  
  
  
  int GetRemovalRange(DecodeTimestamp start_timestamp,
      DecodeTimestamp end_timestamp, int byte_to_free,
      DecodeTimestamp* removal_end_timestamp);

  
  
  
  
  
  
  void PrepareRangesForNextAppend(const BufferQueue& new_buffers,
                                  BufferQueue* deleted_buffers);

  
  void PruneTrackBuffer(const DecodeTimestamp timestamp);

  
  
  void MergeWithAdjacentRangeIfNecessary(
      const RangeList::iterator& range_with_new_buffers_itr);

  
  
  bool AreAdjacentInSequence(
      DecodeTimestamp first_timestamp, DecodeTimestamp second_timestamp) const;

  
  
  
  DecodeTimestamp GetNextBufferTimestamp();

  
  
  
  RangeList::iterator FindExistingRangeFor(DecodeTimestamp start_timestamp);

  
  
  RangeList::iterator AddToRanges(SourceBufferRange* new_range);

  
  
  RangeList::iterator GetSelectedRangeItr();

  
  
  void SetSelectedRange(SourceBufferRange* range);

  
  
  void SeekAndSetSelectedRange(SourceBufferRange* range,
                               DecodeTimestamp seek_timestamp);

  
  void ResetSeekState();

  
  
  bool ShouldSeekToStartOfBuffered(base::TimeDelta seek_timestamp) const;

  
  
  bool IsMonotonicallyIncreasing(const BufferQueue& buffers) const;

  
  
  bool IsNextTimestampValid(DecodeTimestamp next_timestamp,
                            bool next_is_keyframe) const;

  
  
  bool OnlySelectedRangeIsSeeked() const;

  
  void UpdateMaxInterbufferDistance(const BufferQueue& buffers);

  
  void SetConfigIds(const BufferQueue& buffers);

  
  
  
  
  void CompleteConfigChange();

  
  
  
  
  void SetSelectedRangeIfNeeded(const DecodeTimestamp timestamp);

  
  
  
  
  DecodeTimestamp FindNewSelectedRangeSeekTimestamp(
      const DecodeTimestamp start_timestamp);

  
  
  
  DecodeTimestamp FindKeyframeAfterTimestamp(const DecodeTimestamp timestamp);

  
  
  std::string GetStreamTypeName() const;

  
  
  bool IsEndSelected() const;

  
  
  
  
  void DeleteAndRemoveRange(RangeList::iterator* itr);

  
  
  
  
  
  
  
  
  void RemoveInternal(
      DecodeTimestamp start, DecodeTimestamp end, bool is_exclusive,
      BufferQueue* deleted_buffers);

  Type GetType() const;

  
  
  Status HandleNextBufferWithSplice(
      scoped_refptr<StreamParserBuffer>* out_buffer);

  
  
  Status HandleNextBufferWithPreroll(
      scoped_refptr<StreamParserBuffer>* out_buffer);

  
  
  
  Status GetNextBufferInternal(scoped_refptr<StreamParserBuffer>* out_buffer);

  
  
  
  
  void GenerateSpliceFrame(const BufferQueue& new_buffers);

  
  
  bool SetPendingBuffer(scoped_refptr<StreamParserBuffer>* out_buffer);

  
  
  LogCB log_cb_;

  
  RangeList ranges_;

  
  
  
  
  int current_config_index_;

  
  
  
  int append_config_index_;

  
  
  std::vector<AudioDecoderConfig> audio_configs_;
  std::vector<VideoDecoderConfig> video_configs_;

  
  TextTrackConfig text_track_config_;

  
  
  bool seek_pending_;

  
  bool end_of_stream_;

  
  base::TimeDelta seek_buffer_timestamp_;

  
  
  
  SourceBufferRange* selected_range_;

  
  
  BufferQueue track_buffer_;

  
  DecodeTimestamp media_segment_start_time_;

  
  RangeList::iterator range_for_next_append_;

  
  bool new_media_segment_;

  
  
  DecodeTimestamp last_appended_buffer_timestamp_;
  bool last_appended_buffer_is_keyframe_;

  
  
  
  DecodeTimestamp last_output_buffer_timestamp_;

  
  base::TimeDelta max_interbuffer_distance_;

  
  int memory_limit_;

  
  
  
  
  bool config_change_pending_;

  
  
  
  scoped_refptr<StreamParserBuffer> pending_buffer_;

  
  
  size_t splice_buffers_index_;

  
  bool pending_buffers_complete_;

  
  const bool splice_frames_enabled_;

  DISALLOW_COPY_AND_ASSIGN(SourceBufferStream);
};

}  

#endif  
