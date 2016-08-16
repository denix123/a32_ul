// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_PLAYER_ANDROID_H_
#define MEDIA_BASE_ANDROID_MEDIA_PLAYER_ANDROID_H_

#include <jni.h>
#include <string>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "media/base/android/media_player_listener.h"
#include "media/base/media_export.h"
#include "ui/gl/android/scoped_java_surface.h"
#include "url/gurl.h"

namespace media {

class BrowserCdm;
class MediaPlayerManager;

class MEDIA_EXPORT MediaPlayerAndroid {
 public:
  virtual ~MediaPlayerAndroid();

  
  enum MediaErrorType {
    MEDIA_ERROR_FORMAT,
    MEDIA_ERROR_DECODE,
    MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK,
    MEDIA_ERROR_INVALID_CODE,
  };

  
  typedef base::Callback<void(int player_id)> RequestMediaResourcesCB;

  
  virtual void SetVideoSurface(gfx::ScopedJavaSurface surface) = 0;

  
  virtual void Start() = 0;

  
  virtual void Pause(bool is_media_related_action) = 0;

  
  
  
  virtual void SeekTo(base::TimeDelta timestamp) = 0;

  
  virtual void Release() = 0;

  
  virtual void SetVolume(double volume) = 0;

  
  virtual int GetVideoWidth() = 0;
  virtual int GetVideoHeight() = 0;
  virtual base::TimeDelta GetDuration() = 0;
  virtual base::TimeDelta GetCurrentTime() = 0;
  virtual bool IsPlaying() = 0;
  virtual bool IsPlayerReady() = 0;
  virtual bool CanPause() = 0;
  virtual bool CanSeekForward() = 0;
  virtual bool CanSeekBackward() = 0;
  virtual GURL GetUrl();
  virtual GURL GetFirstPartyForCookies();

  
  virtual void SetCdm(BrowserCdm* cdm);

  int player_id() { return player_id_; }

  GURL frame_url() { return frame_url_; }

 protected:
  MediaPlayerAndroid(int player_id,
                     MediaPlayerManager* manager,
                     const RequestMediaResourcesCB& request_media_resources_cb,
                     const GURL& frame_url);

  
  
  
  
  virtual void OnVideoSizeChanged(int width, int height);
  virtual void OnMediaError(int error_type);
  virtual void OnBufferingUpdate(int percent);
  virtual void OnPlaybackComplete();
  virtual void OnMediaInterrupted();
  virtual void OnSeekComplete();
  virtual void OnMediaPrepared();

  
  
  
  void AttachListener(jobject j_media_player);
  void DetachListener();

  MediaPlayerManager* manager() { return manager_; }

  RequestMediaResourcesCB request_media_resources_cb_;

 private:
  friend class MediaPlayerListener;

  
  int player_id_;

  
  MediaPlayerManager* manager_;

  
  GURL frame_url_;

  
  scoped_ptr<MediaPlayerListener> listener_;

  
  
  base::WeakPtrFactory<MediaPlayerAndroid> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaPlayerAndroid);
};

}  

#endif  
