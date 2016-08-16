// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_RENDERER_H_
#define MEDIA_BASE_RENDERER_H_

#include "base/callback.h"
#include "base/time/time.h"
#include "media/base/buffering_state.h"
#include "media/base/media_export.h"
#include "media/base/pipeline_status.h"

namespace media {

class MediaKeys;

class MEDIA_EXPORT Renderer {
 public:
  typedef base::Callback<base::TimeDelta()> TimeDeltaCB;

  Renderer();

  
  virtual ~Renderer();

  
  
  
  
  
  
  
  
  virtual void Initialize(const base::Closure& init_cb,
                          const StatisticsCB& statistics_cb,
                          const base::Closure& ended_cb,
                          const PipelineStatusCB& error_cb,
                          const BufferingStateCB& buffering_state_cb) = 0;

  

  
  virtual void Flush(const base::Closure& flush_cb) = 0;

  
  virtual void StartPlayingFrom(base::TimeDelta time) = 0;

  
  virtual void SetPlaybackRate(float playback_rate) = 0;

  
  virtual void SetVolume(float volume) = 0;

  
  virtual base::TimeDelta GetMediaTime() = 0;

  
  virtual bool HasAudio() = 0;

  
  virtual bool HasVideo() = 0;

  
  virtual void SetCdm(MediaKeys* cdm) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Renderer);
};

}  

#endif  
