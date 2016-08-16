// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_VIDEO_FRAME_SCHEDULER_PROXY_H_
#define MEDIA_FILTERS_VIDEO_FRAME_SCHEDULER_PROXY_H_

#include "base/memory/weak_ptr.h"
#include "media/filters/video_frame_scheduler.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class MEDIA_EXPORT VideoFrameSchedulerProxy : public VideoFrameScheduler {
 public:
  
  
  
  VideoFrameSchedulerProxy(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      const scoped_refptr<base::SingleThreadTaskRunner>& scheduler_runner,
      scoped_ptr<VideoFrameScheduler> scheduler);
  virtual ~VideoFrameSchedulerProxy();

  
  virtual void ScheduleVideoFrame(const scoped_refptr<VideoFrame>& frame,
                                  base::TimeTicks wall_ticks,
                                  const DoneCB& done_cb) OVERRIDE;
  virtual void Reset() OVERRIDE;

 private:
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> scheduler_runner_;
  scoped_ptr<VideoFrameScheduler> scheduler_;

  
  base::WeakPtrFactory<VideoFrameSchedulerProxy> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoFrameSchedulerProxy);
};

}  

#endif  
