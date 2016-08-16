// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_MEDIA_TASK_RUNNER_H_
#define CHROMECAST_MEDIA_CMA_BASE_MEDIA_TASK_RUNNER_H_

#include "base/callback.h"
#include "base/location.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"

namespace chromecast {
namespace media {

class MediaTaskRunner
    : public base::RefCountedThreadSafe<MediaTaskRunner> {
 public:
  MediaTaskRunner();

  
  
  
  
  
  
  virtual bool PostMediaTask(
      const tracked_objects::Location& from_here,
      const base::Closure& task,
      base::TimeDelta timestamp) = 0;

 protected:
  virtual ~MediaTaskRunner();
  friend class base::RefCountedThreadSafe<MediaTaskRunner>;

 private:
  DISALLOW_COPY_AND_ASSIGN(MediaTaskRunner);
};

}  
}  

#endif  
