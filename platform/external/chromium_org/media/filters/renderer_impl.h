// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_RENDERER_IMPL_H_
#define MEDIA_FILTERS_RENDERER_IMPL_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "base/time/clock.h"
#include "base/time/default_tick_clock.h"
#include "base/time/time.h"
#include "media/base/buffering_state.h"
#include "media/base/media_export.h"
#include "media/base/pipeline_status.h"
#include "media/base/renderer.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class AudioRenderer;
class DemuxerStreamProvider;
class TimeSource;
class VideoRenderer;
class WallClockTimeSource;

class MEDIA_EXPORT RendererImpl : public Renderer {
 public:
  
  
  
  
  RendererImpl(const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
               DemuxerStreamProvider* demuxer_stream_provider,
               scoped_ptr<AudioRenderer> audio_renderer,
               scoped_ptr<VideoRenderer> video_renderer);

  virtual ~RendererImpl();

  
  virtual void Initialize(const base::Closure& init_cb,
                          const StatisticsCB& statistics_cb,
                          const base::Closure& ended_cb,
                          const PipelineStatusCB& error_cb,
                          const BufferingStateCB& buffering_state_cb) OVERRIDE;
  virtual void Flush(const base::Closure& flush_cb) OVERRIDE;
  virtual void StartPlayingFrom(base::TimeDelta time) OVERRIDE;
  virtual void SetPlaybackRate(float playback_rate) OVERRIDE;
  virtual void SetVolume(float volume) OVERRIDE;
  virtual base::TimeDelta GetMediaTime() OVERRIDE;
  virtual bool HasAudio() OVERRIDE;
  virtual bool HasVideo() OVERRIDE;
  virtual void SetCdm(MediaKeys* cdm) OVERRIDE;

  
  void DisableUnderflowForTesting();
  void EnableClocklessVideoPlaybackForTesting();

 private:
  enum State {
    STATE_UNINITIALIZED,
    STATE_INITIALIZING,
    STATE_FLUSHING,
    STATE_PLAYING,
    STATE_ERROR
  };

  base::TimeDelta GetMediaTimeForSyncingVideo();

  
  void InitializeAudioRenderer();
  void OnAudioRendererInitializeDone(PipelineStatus status);
  void InitializeVideoRenderer();
  void OnVideoRendererInitializeDone(PipelineStatus status);

  
  void FlushAudioRenderer();
  void OnAudioRendererFlushDone();
  void FlushVideoRenderer();
  void OnVideoRendererFlushDone();

  
  void OnUpdateStatistics(const PipelineStatistics& stats);

  
  
  
  
  
  
  
  
  
  void OnBufferingStateChanged(BufferingState* buffering_state,
                               BufferingState new_buffering_state);
  bool WaitingForEnoughData() const;
  void PausePlayback();
  void StartPlayback();

  
  void OnAudioRendererEnded();
  void OnVideoRendererEnded();
  bool PlaybackHasEnded() const;
  void RunEndedCallbackIfNeeded();

  
  void OnError(PipelineStatus error);

  void FireAllPendingCallbacks();

  State state_;

  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  DemuxerStreamProvider* demuxer_stream_provider_;

  
  StatisticsCB statistics_cb_;
  base::Closure ended_cb_;
  PipelineStatusCB error_cb_;
  BufferingStateCB buffering_state_cb_;

  
  base::Closure init_cb_;
  base::Closure flush_cb_;

  scoped_ptr<AudioRenderer> audio_renderer_;
  scoped_ptr<VideoRenderer> video_renderer_;

  
  TimeSource* time_source_;
  scoped_ptr<WallClockTimeSource> wall_clock_time_source_;
  bool time_ticking_;

  
  base::TimeDelta start_time_;

  BufferingState audio_buffering_state_;
  BufferingState video_buffering_state_;

  
  bool audio_ended_;
  bool video_ended_;

  bool underflow_disabled_for_testing_;
  bool clockless_video_playback_enabled_for_testing_;

  
  base::WeakPtrFactory<RendererImpl> weak_factory_;
  base::WeakPtr<RendererImpl> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(RendererImpl);
};

}  

#endif  
