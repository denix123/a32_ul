// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_PLAYER_MANAGER_H_
#define MEDIA_BASE_ANDROID_MEDIA_PLAYER_MANAGER_H_

#include "base/basictypes.h"
#include "base/time/time.h"
#include "media/base/android/demuxer_stream_player_params.h"
#include "media/base/media_export.h"

namespace media {

class MediaPlayerAndroid;
class MediaResourceGetter;
class MediaUrlInterceptor;

class MEDIA_EXPORT MediaPlayerManager {
 public:
  virtual ~MediaPlayerManager() {}

  
  virtual MediaResourceGetter* GetMediaResourceGetter() = 0;

  
  virtual MediaUrlInterceptor* GetMediaUrlInterceptor() = 0;

  
  
  virtual void OnTimeUpdate(int player_id,
                            base::TimeDelta current_timestamp,
                            base::TimeTicks current_time_ticks) = 0;

  
  
  virtual void OnMediaMetadataChanged(
      int player_id,
      base::TimeDelta duration,
      int width,
      int height,
      bool success) = 0;

  
  virtual void OnPlaybackComplete(int player_id) = 0;

  
  virtual void OnMediaInterrupted(int player_id) = 0;

  
  
  virtual void OnBufferingUpdate(int player_id, int percentage) = 0;

  
  virtual void OnSeekComplete(
      int player_id,
      const base::TimeDelta& current_time) = 0;

  
  virtual void OnError(int player_id, int error) = 0;

  
  virtual void OnVideoSizeChanged(int player_id, int width, int height) = 0;

  
  virtual MediaPlayerAndroid* GetFullscreenPlayer() = 0;

  
  virtual MediaPlayerAndroid* GetPlayer(int player_id) = 0;

  
  virtual void RequestFullScreen(int player_id) = 0;

#if defined(VIDEO_HOLE)
  
  
  virtual bool ShouldUseVideoOverlayForEmbeddedEncryptedVideo() = 0;
#endif  
};

}  

#endif  
