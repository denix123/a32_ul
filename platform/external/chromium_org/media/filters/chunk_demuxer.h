// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_CHUNK_DEMUXER_H_
#define MEDIA_FILTERS_CHUNK_DEMUXER_H_

#include <deque>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/synchronization/lock.h"
#include "media/base/byte_queue.h"
#include "media/base/demuxer.h"
#include "media/base/ranges.h"
#include "media/base/stream_parser.h"
#include "media/filters/source_buffer_stream.h"

namespace media {

class FFmpegURLProtocol;
class SourceState;

class MEDIA_EXPORT ChunkDemuxerStream : public DemuxerStream {
 public:
  typedef std::deque<scoped_refptr<StreamParserBuffer> > BufferQueue;

  explicit ChunkDemuxerStream(Type type, bool splice_frames_enabled);
  virtual ~ChunkDemuxerStream();

  
  void StartReturningData();
  void AbortReads();
  void CompletePendingReadIfPossible();
  void Shutdown();

  
  void Seek(base::TimeDelta time);
  bool IsSeekWaitingForData() const;

  
  
  
  bool Append(const StreamParser::BufferQueue& buffers);

  
  
  
  
  
  
  
  void Remove(base::TimeDelta start, base::TimeDelta end,
              base::TimeDelta duration);

  
  void OnSetDuration(base::TimeDelta duration);

  
  Ranges<base::TimeDelta> GetBufferedRanges(base::TimeDelta duration) const;

  
  
  base::TimeDelta GetBufferedDuration() const;

  
  
  void OnNewMediaSegment(DecodeTimestamp start_timestamp);

  
  
  
  bool UpdateAudioConfig(const AudioDecoderConfig& config, const LogCB& log_cb);
  bool UpdateVideoConfig(const VideoDecoderConfig& config, const LogCB& log_cb);
  void UpdateTextConfig(const TextTrackConfig& config, const LogCB& log_cb);

  void MarkEndOfStream();
  void UnmarkEndOfStream();

  
  virtual void Read(const ReadCB& read_cb) OVERRIDE;
  virtual Type type() OVERRIDE;
  virtual AudioDecoderConfig audio_decoder_config() OVERRIDE;
  virtual VideoDecoderConfig video_decoder_config() OVERRIDE;
  virtual bool SupportsConfigChanges() OVERRIDE;
  virtual VideoRotation video_rotation() OVERRIDE;

  
  
  TextTrackConfig text_track_config();

  
  void set_memory_limit(int memory_limit) {
    stream_->set_memory_limit(memory_limit);
  }

  bool supports_partial_append_window_trimming() const {
    return partial_append_window_trimming_enabled_;
  }

 private:
  enum State {
    UNINITIALIZED,
    RETURNING_DATA_FOR_READS,
    RETURNING_ABORT_FOR_READS,
    SHUTDOWN,
  };

  
  void ChangeState_Locked(State state);

  void CompletePendingReadIfPossible_Locked();

  
  Type type_;

  scoped_ptr<SourceBufferStream> stream_;

  mutable base::Lock lock_;
  State state_;
  ReadCB read_cb_;
  bool splice_frames_enabled_;
  bool partial_append_window_trimming_enabled_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(ChunkDemuxerStream);
};

class MEDIA_EXPORT ChunkDemuxer : public Demuxer {
 public:
  enum Status {
    kOk,              
    kNotSupported,    
    kReachedIdLimit,  
  };

  typedef base::Closure InitSegmentReceivedCB;

  
  
  
  
  
  
  
  
  
  
  
  ChunkDemuxer(const base::Closure& open_cb,
               const NeedKeyCB& need_key_cb,
               const LogCB& log_cb,
               bool splice_frames_enabled);
  virtual ~ChunkDemuxer();

  
  virtual void Initialize(DemuxerHost* host,
                          const PipelineStatusCB& cb,
                          bool enable_text_tracks) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual void Seek(base::TimeDelta time, const PipelineStatusCB&  cb) OVERRIDE;
  virtual base::Time GetTimelineOffset() const OVERRIDE;
  virtual DemuxerStream* GetStream(DemuxerStream::Type type) OVERRIDE;
  virtual base::TimeDelta GetStartTime() const OVERRIDE;
  virtual Liveness GetLiveness() const OVERRIDE;

  
  
  
  
  
  
  
  
  
  
  
  void StartWaitingForSeek(base::TimeDelta seek_time);

  
  
  
  
  
  
  
  
  
  
  void CancelPendingSeek(base::TimeDelta seek_time);

  
  
  
  
  
  
  
  Status AddId(const std::string& id, const std::string& type,
               std::vector<std::string>& codecs);

  
  
  void RemoveId(const std::string& id);

  
  Ranges<base::TimeDelta> GetBufferedRanges(const std::string& id) const;

  
  
  
  
  
  
  
  void AppendData(const std::string& id, const uint8* data, size_t length,
                  base::TimeDelta append_window_start,
                  base::TimeDelta append_window_end,
                  base::TimeDelta* timestamp_offset,
                  const InitSegmentReceivedCB& init_segment_received_cb);

  
  
  
  
  void Abort(const std::string& id,
             base::TimeDelta append_window_start,
             base::TimeDelta append_window_end,
             base::TimeDelta* timestamp_offset);

  
  
  void Remove(const std::string& id, base::TimeDelta start,
              base::TimeDelta end);

  
  double GetDuration();
  double GetDuration_Locked();

  
  
  void SetDuration(double duration);

  
  
  bool IsParsingMediaSegment(const std::string& id);

  
  
  
  
  void SetSequenceMode(const std::string& id, bool sequence_mode);

  
  
  
  void SetGroupStartTimestampIfInSequenceMode(const std::string& id,
                                              base::TimeDelta timestamp_offset);

  
  
  
  void MarkEndOfStream(PipelineStatus status);
  void UnmarkEndOfStream();

  void Shutdown();

  
  
  
  void SetMemoryLimits(DemuxerStream::Type type, int memory_limit);

  
  
  
  
  Ranges<base::TimeDelta> GetBufferedRanges() const;

 private:
  enum State {
    WAITING_FOR_INIT,
    INITIALIZING,
    INITIALIZED,
    ENDED,
    PARSE_ERROR,
    SHUTDOWN,
  };

  void ChangeState_Locked(State new_state);

  
  
  void ReportError_Locked(PipelineStatus error);

  
  bool IsSeekWaitingForData_Locked() const;

  
  
  bool CanEndOfStream_Locked() const;

  
  void OnSourceInitDone(bool success,
                        const StreamParser::InitParameters& params);

  
  
  
  ChunkDemuxerStream* CreateDemuxerStream(DemuxerStream::Type type);

  void OnNewTextTrack(ChunkDemuxerStream* text_stream,
                      const TextTrackConfig& config);

  
  bool IsValidId(const std::string& source_id) const;

  
  void IncreaseDurationIfNecessary(base::TimeDelta new_duration);

  
  
  void DecreaseDurationIfNecessary();

  
  
  void UpdateDuration(base::TimeDelta new_duration);

  
  Ranges<base::TimeDelta> GetBufferedRanges_Locked() const;

  
  void StartReturningData();

  
  void AbortPendingReads();

  
  void CompletePendingReadsIfPossible();

  
  void SeekAllSources(base::TimeDelta seek_time);

  
  
  void ShutdownAllStreams();

  mutable base::Lock lock_;
  State state_;
  bool cancel_next_seek_;

  DemuxerHost* host_;
  base::Closure open_cb_;
  NeedKeyCB need_key_cb_;
  bool enable_text_;
  
  
  LogCB log_cb_;

  PipelineStatusCB init_cb_;
  
  
  
  
  PipelineStatusCB seek_cb_;

  scoped_ptr<ChunkDemuxerStream> audio_;
  scoped_ptr<ChunkDemuxerStream> video_;

  base::TimeDelta duration_;

  
  
  
  
  
  double user_specified_duration_;

  base::Time timeline_offset_;
  Liveness liveness_;

  typedef std::map<std::string, SourceState*> SourceStateMap;
  SourceStateMap source_state_map_;

  
  
  
  std::string source_id_audio_;
  std::string source_id_video_;

  
  const bool splice_frames_enabled_;

  DISALLOW_COPY_AND_ASSIGN(ChunkDemuxer);
};

}  

#endif  
