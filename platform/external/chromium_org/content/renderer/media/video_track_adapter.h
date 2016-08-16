// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_VIDEO_TRACK_ADAPTER_H_
#define CONTENT_RENDERER_MEDIA_VIDEO_TRACK_ADAPTER_H_

#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "content/renderer/media/media_stream_video_track.h"
#include "media/base/video_frame.h"

namespace content {

class VideoTrackAdapter
    : public base::RefCountedThreadSafe<VideoTrackAdapter> {
 public:
  typedef base::Callback<void(bool mute_state)> OnMutedCallback;

  explicit VideoTrackAdapter(
      const scoped_refptr<base::MessageLoopProxy>& io_message_loop);

  
  
  
  
  
  
  void AddTrack(const MediaStreamVideoTrack* track,
                VideoCaptureDeliverFrameCB frame_callback,
                int max_width, int max_height,
                double min_aspect_ratio,
                double max_aspect_ratio,
                double max_frame_rate);
  void RemoveTrack(const MediaStreamVideoTrack* track);

  
  
  void DeliverFrameOnIO(
      const scoped_refptr<media::VideoFrame>& frame,
      const media::VideoCaptureFormat& format,
      const base::TimeTicks& estimated_capture_time);

  const scoped_refptr<base::MessageLoopProxy>& io_message_loop() {
    DCHECK(thread_checker_.CalledOnValidThread());
    return io_message_loop_;
  }

  
  
  
  void StartFrameMonitoring(double source_frame_rate,
                            const OnMutedCallback& on_muted_callback);
  void StopFrameMonitoring();

 private:
  virtual ~VideoTrackAdapter();
  friend class base::RefCountedThreadSafe<VideoTrackAdapter>;

  void AddTrackOnIO(
      const MediaStreamVideoTrack* track,
      VideoCaptureDeliverFrameCB frame_callback,
      const gfx::Size& max_frame_size,
      double min_aspect_ratio,
      double max_aspect_ratio,
      double max_frame_rate);
  void RemoveTrackOnIO(const MediaStreamVideoTrack* track);

  void StartFrameMonitoringOnIO(
    const OnMutedCallback& on_muted_state_callback,
    double source_frame_rate);
  void StopFrameMonitoringOnIO();

  
  
  void CheckFramesReceivedOnIO(const OnMutedCallback& set_muted_state_callback,
                               uint64 old_frame_counter_snapshot);

  
  base::ThreadChecker thread_checker_;

  scoped_refptr<base::MessageLoopProxy> io_message_loop_;

  
  
  scoped_refptr<base::SingleThreadTaskRunner> renderer_task_runner_;

  
  
  
  class VideoFrameResolutionAdapter;
  typedef std::vector<scoped_refptr<VideoFrameResolutionAdapter> >
      FrameAdapters;
  FrameAdapters adapters_;

  
  
  bool monitoring_frame_rate_;

  
  
  bool muted_state_;

  
  uint64 frame_counter_;

  
  float source_frame_rate_;

  DISALLOW_COPY_AND_ASSIGN(VideoTrackAdapter);
};

}  

#endif  
