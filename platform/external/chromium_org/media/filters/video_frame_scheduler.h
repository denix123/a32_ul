// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_VIDEO_FRAME_SCHEDULER_H_
#define MEDIA_FILTERS_VIDEO_FRAME_SCHEDULER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "media/base/media_export.h"

namespace media {

class VideoFrame;

class MEDIA_EXPORT VideoFrameScheduler {
 public:
  VideoFrameScheduler() {}
  virtual ~VideoFrameScheduler() {}

  enum Reason {
    DISPLAYED,  
    DROPPED,    
  };
  typedef base::Callback<void(const scoped_refptr<VideoFrame>&, Reason)> DoneCB;

  
  
  
  
  virtual void ScheduleVideoFrame(const scoped_refptr<VideoFrame>& frame,
                                  base::TimeTicks wall_ticks,
                                  const DoneCB& done_cb) = 0;

  
  
  
  
  
  virtual void Reset() = 0;
};

}  

#endif  
