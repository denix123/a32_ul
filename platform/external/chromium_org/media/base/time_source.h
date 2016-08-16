// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_TIME_SOURCE_H_
#define MEDIA_BASE_TIME_SOURCE_H_

#include "base/time/time.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT TimeSource {
 public:
  TimeSource() {}
  virtual ~TimeSource() {}

  
  
  virtual void StartTicking() = 0;

  
  
  virtual void StopTicking() = 0;

  
  
  
  virtual void SetPlaybackRate(float playback_rate) = 0;

  
  
  virtual void SetMediaTime(base::TimeDelta time) = 0;

  
  
  
  
  
  virtual base::TimeDelta CurrentMediaTime() = 0;

  
  
  
  
  
  
  
  
  
  
  virtual base::TimeDelta CurrentMediaTimeForSyncingVideo() = 0;
};

}  

#endif  
