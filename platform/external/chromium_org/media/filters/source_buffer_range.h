// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_SOURCE_BUFFER_RANGE_H_
#define MEDIA_FILTERS_SOURCE_BUFFER_RANGE_H_

#include <map>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "media/base/stream_parser_buffer.h"

namespace media {

class SourceBufferRange {
 public:
  
  
  
  typedef base::Callback<base::TimeDelta()> InterbufferDistanceCB;

  typedef StreamParser::BufferQueue BufferQueue;

  
  
  
  
  enum GapPolicy {
    NO_GAPS_ALLOWED,
    ALLOW_GAPS
  };

  
  
  
  
  
  
  
  
  
  static bool AllowSameTimestamp(bool prev_is_keyframe,
                                 bool current_is_keyframe);

  
  
  
  
  SourceBufferRange(GapPolicy gap_policy,
                    const BufferQueue& new_buffers,
                    DecodeTimestamp media_segment_start_time,
                    const InterbufferDistanceCB& interbuffer_distance_cb);

  ~SourceBufferRange();

  
  
  
  void AppendBuffersToEnd(const BufferQueue& buffers);
  bool CanAppendBuffersToEnd(const BufferQueue& buffers) const;

  
  
  
  
  
  void AppendRangeToEnd(const SourceBufferRange& range,
                        bool transfer_current_position);
  bool CanAppendRangeToEnd(const SourceBufferRange& range) const;

  
  
  void Seek(DecodeTimestamp timestamp);

  
  
  void SeekAheadTo(DecodeTimestamp timestamp);

  
  
  void SeekAheadPast(DecodeTimestamp timestamp);

  
  void SeekToStart();

  
  
  
  
  
  
  SourceBufferRange* SplitRange(DecodeTimestamp timestamp, bool is_exclusive);

  
  
  
  
  
  
  
  
  
  bool TruncateAt(DecodeTimestamp timestamp,
                  BufferQueue* deleted_buffers, bool is_exclusive);
  
  void DeleteAll(BufferQueue* deleted_buffers);

  
  
  
  int DeleteGOPFromFront(BufferQueue* deleted_buffers);
  int DeleteGOPFromBack(BufferQueue* deleted_buffers);

  
  
  
  
  
  int GetRemovalGOP(
      DecodeTimestamp start_timestamp, DecodeTimestamp end_timestamp,
      int bytes_to_free, DecodeTimestamp* end_removal_timestamp);

  
  
  bool FirstGOPContainsNextBufferPosition() const;
  bool LastGOPContainsNextBufferPosition() const;

  
  
  
  
  
  bool GetNextBuffer(scoped_refptr<StreamParserBuffer>* out_buffer);
  bool HasNextBuffer() const;

  
  
  int GetNextConfigId() const;

  
  
  
  bool HasNextBufferPosition() const;

  
  void ResetNextBufferPosition();

  
  
  DecodeTimestamp GetNextTimestamp() const;

  
  DecodeTimestamp GetStartTimestamp() const;

  
  DecodeTimestamp GetEndTimestamp() const;

  
  
  
  DecodeTimestamp GetBufferedEndTimestamp() const;

  
  
  
  
  
  DecodeTimestamp NextKeyframeTimestamp(DecodeTimestamp timestamp);

  
  
  
  DecodeTimestamp KeyframeBeforeTimestamp(DecodeTimestamp timestamp);

  
  
  
  bool BelongsToRange(DecodeTimestamp timestamp) const;

  
  
  bool CanSeekTo(DecodeTimestamp timestamp) const;

  
  
  bool CompletelyOverlaps(const SourceBufferRange& range) const;

  
  
  bool EndOverlaps(const SourceBufferRange& range) const;

  
  
  bool IsNextInSequence(DecodeTimestamp timestamp, bool is_keyframe) const;

  
  
  bool GetBuffersInRange(DecodeTimestamp start, DecodeTimestamp end,
                         BufferQueue* buffers);

  int size_in_bytes() const { return size_in_bytes_; }

 private:
  typedef std::map<DecodeTimestamp, int> KeyframeMap;

  
  
  
  void SeekAhead(DecodeTimestamp timestamp, bool skip_given_timestamp);

  
  
  
  BufferQueue::iterator GetBufferItrAt(
      DecodeTimestamp timestamp, bool skip_given_timestamp);

  
  
  
  KeyframeMap::iterator GetFirstKeyframeAt(
      DecodeTimestamp timestamp, bool skip_given_timestamp);

  
  
  KeyframeMap::iterator GetFirstKeyframeBefore(DecodeTimestamp timestamp);

  
  
  
  
  bool TruncateAt(const BufferQueue::iterator& starting_point,
                  BufferQueue* deleted_buffers);

  
  
  void FreeBufferRange(const BufferQueue::iterator& starting_point,
                       const BufferQueue::iterator& ending_point);

  
  
  base::TimeDelta GetFudgeRoom() const;

  
  base::TimeDelta GetApproximateDuration() const;

  
  const GapPolicy gap_policy_;

  
  BufferQueue buffers_;

  
  KeyframeMap keyframe_map_;

  
  
  
  int keyframe_map_index_base_;

  
  
  int next_buffer_index_;

  
  
  
  
  
  
  
  
  DecodeTimestamp media_segment_start_time_;

  
  InterbufferDistanceCB interbuffer_distance_cb_;

  
  int size_in_bytes_;

  DISALLOW_COPY_AND_ASSIGN(SourceBufferRange);
};

}  

#endif  
