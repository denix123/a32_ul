// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_PIPELINE_H_
#define MEDIA_BASE_PIPELINE_H_

#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "base/time/default_tick_clock.h"
#include "media/base/buffering_state.h"
#include "media/base/demuxer.h"
#include "media/base/media_export.h"
#include "media/base/pipeline_status.h"
#include "media/base/ranges.h"
#include "media/base/serial_runner.h"
#include "media/base/text_track.h"
#include "media/base/video_rotation.h"
#include "ui/gfx/size.h"

namespace base {
class SingleThreadTaskRunner;
class TimeDelta;
}

namespace media {

class MediaLog;
class Renderer;
class TextRenderer;
class TextTrackConfig;
class TimeDeltaInterpolator;

struct PipelineMetadata {
  PipelineMetadata()
      : has_audio(false), has_video(false), video_rotation(VIDEO_ROTATION_0) {}

  bool has_audio;
  bool has_video;
  gfx::Size natural_size;
  VideoRotation video_rotation;
  base::Time timeline_offset;
};

typedef base::Callback<void(PipelineMetadata)> PipelineMetadataCB;

class MEDIA_EXPORT Pipeline : public DemuxerHost {
 public:
  
  Pipeline(const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
           MediaLog* media_log);
  virtual ~Pipeline();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void Start(Demuxer* demuxer,
             scoped_ptr<Renderer> renderer,
             const base::Closure& ended_cb,
             const PipelineStatusCB& error_cb,
             const PipelineStatusCB& seek_cb,
             const PipelineMetadataCB& metadata_cb,
             const BufferingStateCB& buffering_state_cb,
             const base::Closure& duration_change_cb,
             const AddTextTrackCB& add_text_track_cb);

  
  
  
  
  
  
  
  void Stop(const base::Closure& stop_cb);

  
  
  
  
  
  
  
  void Seek(base::TimeDelta time, const PipelineStatusCB& seek_cb);

  
  
  
  bool IsRunning() const;

  
  
  
  
  float GetPlaybackRate() const;

  
  
  
  
  
  void SetPlaybackRate(float playback_rate);

  
  
  
  float GetVolume() const;

  
  
  
  void SetVolume(float volume);

  
  
  base::TimeDelta GetMediaTime() const;

  
  Ranges<base::TimeDelta> GetBufferedTimeRanges() const;

  
  
  base::TimeDelta GetMediaDuration() const;

  
  
  bool DidLoadingProgress();

  
  PipelineStatistics GetStatistics() const;

  void SetErrorForTesting(PipelineStatus status);
  bool HasWeakPtrsForTesting() const;

 private:
  FRIEND_TEST_ALL_PREFIXES(PipelineTest, GetBufferedTimeRanges);
  FRIEND_TEST_ALL_PREFIXES(PipelineTest, EndedCallback);
  FRIEND_TEST_ALL_PREFIXES(PipelineTest, AudioStreamShorterThanVideo);
  friend class MediaLog;

  
  enum State {
    kCreated,
    kInitDemuxer,
    kInitRenderer,
    kSeeking,
    kPlaying,
    kStopping,
    kStopped,
  };

  
  void SetState(State next_state);

  static const char* GetStateString(State state);
  State GetNextState() const;

  
  
  void FinishSeek();

  
  virtual void AddBufferedTimeRange(base::TimeDelta start,
                                    base::TimeDelta end) OVERRIDE;
  virtual void SetDuration(base::TimeDelta duration) OVERRIDE;
  virtual void OnDemuxerError(PipelineStatus error) OVERRIDE;
  virtual void AddTextStream(DemuxerStream* text_stream,
                             const TextTrackConfig& config) OVERRIDE;
  virtual void RemoveTextStream(DemuxerStream* text_stream) OVERRIDE;

  
  
  void OnError(PipelineStatus error);

  
  void OnUpdateStatistics(const PipelineStatistics& stats);

  
  
  
  void StartTask();

  
  void StopTask(const base::Closure& stop_cb);

  
  
  void ErrorChangedTask(PipelineStatus error);

  
  void PlaybackRateChangedTask(float playback_rate);

  
  void VolumeChangedTask(float volume);

  
  void SeekTask(base::TimeDelta time, const PipelineStatusCB& seek_cb);

  
  void OnRendererEnded();
  void OnTextRendererEnded();
  void RunEndedCallbackIfNeeded();

  scoped_ptr<TextRenderer> CreateTextRenderer();

  
  void AddTextStreamTask(DemuxerStream* text_stream,
                         const TextTrackConfig& config);

  
  void RemoveTextStreamTask(DemuxerStream* text_stream);

  
  void OnAddTextTrack(const TextTrackConfig& config,
                      const AddTextTrackDoneCB& done_cb);

  
  
  void InitializeDemuxer(const PipelineStatusCB& done_cb);
  void InitializeRenderer(const base::Closure& done_cb);

  void OnStateTransition(PipelineStatus status);
  void StateTransitionTask(PipelineStatus status);

  
  
  void DoSeek(base::TimeDelta seek_timestamp, const PipelineStatusCB& done_cb);

  
  
  void DoStop(const PipelineStatusCB& done_cb);
  void OnStopCompleted(PipelineStatus status);

  void ReportMetadata();

  void BufferingStateChanged(BufferingState new_buffering_state);

  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  
  scoped_refptr<MediaLog> media_log_;

  
  mutable base::Lock lock_;

  
  bool running_;

  
  Ranges<base::TimeDelta> buffered_time_ranges_;

  
  
  bool did_loading_progress_;

  
  
  
  float volume_;

  
  
  
  float playback_rate_;

  
  base::TimeDelta duration_;

  
  
  
  
  PipelineStatus status_;

  
  

  bool is_initialized_;

  
  State state_;

  
  base::TimeDelta start_timestamp_;

  
  bool renderer_ended_;
  bool text_renderer_ended_;

  
  PipelineStatusCB seek_cb_;

  
  base::Closure stop_cb_;

  
  base::Closure ended_cb_;
  PipelineStatusCB error_cb_;
  PipelineMetadataCB metadata_cb_;
  BufferingStateCB buffering_state_cb_;
  base::Closure duration_change_cb_;
  AddTextTrackCB add_text_track_cb_;

  
  Demuxer* demuxer_;

  
  
  scoped_ptr<Renderer> renderer_;
  scoped_ptr<TextRenderer> text_renderer_;

  PipelineStatistics statistics_;

  scoped_ptr<SerialRunner> pending_callbacks_;

  base::ThreadChecker thread_checker_;

  
  base::WeakPtrFactory<Pipeline> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(Pipeline);
};

}  

#endif  
