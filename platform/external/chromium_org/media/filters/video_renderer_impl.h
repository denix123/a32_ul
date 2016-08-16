// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_VIDEO_RENDERER_IMPL_H_
#define MEDIA_FILTERS_VIDEO_RENDERER_IMPL_H_

#include <deque>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/condition_variable.h"
#include "base/synchronization/lock.h"
#include "base/threading/platform_thread.h"
#include "media/base/decryptor.h"
#include "media/base/demuxer_stream.h"
#include "media/base/media_log.h"
#include "media/base/pipeline_status.h"
#include "media/base/video_decoder.h"
#include "media/base/video_frame.h"
#include "media/base/video_renderer.h"
#include "media/filters/decoder_stream.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class MEDIA_EXPORT VideoRendererImpl
    : public VideoRenderer,
      public base::PlatformThread::Delegate {
 public:
  typedef base::Callback<void(const scoped_refptr<VideoFrame>&)> PaintCB;

  
  
  
  
  
  
  
  
  
  
  VideoRendererImpl(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      ScopedVector<VideoDecoder> decoders,
      const SetDecryptorReadyCB& set_decryptor_ready_cb,
      const PaintCB& paint_cb,
      bool drop_frames,
      const scoped_refptr<MediaLog>& media_log);
  virtual ~VideoRendererImpl();

  
  virtual void Initialize(DemuxerStream* stream,
                          bool low_delay,
                          const PipelineStatusCB& init_cb,
                          const StatisticsCB& statistics_cb,
                          const BufferingStateCB& buffering_state_cb,
                          const base::Closure& ended_cb,
                          const PipelineStatusCB& error_cb,
                          const TimeDeltaCB& get_time_cb) OVERRIDE;
  virtual void Flush(const base::Closure& callback) OVERRIDE;
  virtual void StartPlayingFrom(base::TimeDelta timestamp) OVERRIDE;

  
  virtual void ThreadMain() OVERRIDE;

 private:
  
  void OnVideoFrameStreamInitialized(bool success);

  
  
  void FrameReady(VideoFrameStream::Status status,
                  const scoped_refptr<VideoFrame>& frame);

  
  void AddReadyFrame_Locked(const scoped_refptr<VideoFrame>& frame);

  
  
  
  void AttemptRead();
  void AttemptRead_Locked();

  
  void OnVideoFrameStreamResetDone();

  
  
  
  void PaintNextReadyFrame_Locked();

  
  
  
  void DropNextReadyFrame_Locked();

  
  
  bool HaveEnoughData_Locked();
  void TransitionToHaveEnough_Locked();

  
  
  
  void UpdateStatsAndWait_Locked(base::TimeDelta wait_duration);

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  
  base::Lock lock_;

  
  scoped_ptr<VideoFrameStream> video_frame_stream_;

  
  bool low_delay_;

  
  typedef std::deque<scoped_refptr<VideoFrame> > VideoFrameQueue;
  VideoFrameQueue ready_frames_;

  
  
  bool received_end_of_stream_;
  bool rendered_end_of_stream_;

  
  
  base::ConditionVariable frame_available_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  enum State {
    kUninitialized,
    kInitializing,
    kFlushing,
    kFlushed,
    kPlaying
  };
  State state_;

  
  base::PlatformThreadHandle thread_;

  
  
  bool pending_read_;

  bool drop_frames_;

  BufferingState buffering_state_;

  
  base::Closure flush_cb_;

  
  PipelineStatusCB init_cb_;
  StatisticsCB statistics_cb_;
  BufferingStateCB buffering_state_cb_;
  base::Closure ended_cb_;
  PipelineStatusCB error_cb_;
  TimeDeltaCB get_time_cb_;

  base::TimeDelta start_timestamp_;

  
  PaintCB paint_cb_;

  
  
  
  base::TimeDelta last_timestamp_;

  
  
  base::TimeDelta last_painted_timestamp_;

  
  
  int frames_decoded_;
  int frames_dropped_;

  bool is_shutting_down_;

  
  base::WeakPtrFactory<VideoRendererImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoRendererImpl);
};

}  

#endif  
