// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_PLAYER_BRIDGE_H_
#define MEDIA_BASE_ANDROID_MEDIA_PLAYER_BRIDGE_H_

#include <jni.h>
#include <map>
#include <string>

#include "base/android/scoped_java_ref.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "media/base/android/media_player_android.h"
#include "url/gurl.h"

namespace media {

class MediaPlayerManager;

class MEDIA_EXPORT MediaPlayerBridge : public MediaPlayerAndroid {
 public:
  static bool RegisterMediaPlayerBridge(JNIEnv* env);

  
  
  
  
  
  MediaPlayerBridge(int player_id,
                    const GURL& url,
                    const GURL& first_party_for_cookies,
                    const std::string& user_agent,
                    bool hide_url_log,
                    MediaPlayerManager* manager,
                    const RequestMediaResourcesCB& request_media_resources_cb,
                    const GURL& frame_url,
                    bool allow_credentials);
  virtual ~MediaPlayerBridge();

  
  virtual void Initialize();

  
  virtual void SetVideoSurface(gfx::ScopedJavaSurface surface) OVERRIDE;
  virtual void Start() OVERRIDE;
  virtual void Pause(bool is_media_related_action ALLOW_UNUSED) OVERRIDE;
  virtual void SeekTo(base::TimeDelta timestamp) OVERRIDE;
  virtual void Release() OVERRIDE;
  virtual void SetVolume(double volume) OVERRIDE;
  virtual int GetVideoWidth() OVERRIDE;
  virtual int GetVideoHeight() OVERRIDE;
  virtual base::TimeDelta GetCurrentTime() OVERRIDE;
  virtual base::TimeDelta GetDuration() OVERRIDE;
  virtual bool IsPlaying() OVERRIDE;
  virtual bool CanPause() OVERRIDE;
  virtual bool CanSeekForward() OVERRIDE;
  virtual bool CanSeekBackward() OVERRIDE;
  virtual bool IsPlayerReady() OVERRIDE;
  virtual GURL GetUrl() OVERRIDE;
  virtual GURL GetFirstPartyForCookies() OVERRIDE;

  void OnDidSetDataUriDataSource(JNIEnv* env, jobject obj, jboolean success);

 protected:
  void SetJavaMediaPlayerBridge(jobject j_media_player_bridge);
  base::android::ScopedJavaLocalRef<jobject> GetJavaMediaPlayerBridge();
  void SetDuration(base::TimeDelta time);

  virtual void PendingSeekInternal(const base::TimeDelta& time);

  
  
  
  virtual void Prepare();

  
  virtual void OnVideoSizeChanged(int width, int height) override;
  virtual void OnPlaybackComplete() override;
  virtual void OnMediaInterrupted() override;
  virtual void OnMediaPrepared() override;

  
  virtual void CreateJavaMediaPlayerBridge();

  
  virtual base::android::ScopedJavaLocalRef<jobject> GetAllowedOperations();

 private:
  
  void SetDataSource(const std::string& url);

  
  void StartInternal();
  void PauseInternal();
  void SeekInternal(base::TimeDelta time);

  
  void OnTimeUpdateTimerFired();

  
  void UpdateAllowedOperations();

  
  
  void OnCookiesRetrieved(const std::string& cookies);

  
  
  void OnAuthCredentialsRetrieved(
      const base::string16& username, const base::string16& password);

  
  
  void ExtractMediaMetadata(const std::string& url);
  void OnMediaMetadataExtracted(base::TimeDelta duration, int width, int height,
                                bool success);

  
  
  bool InterceptMediaUrl(
      const std::string& url, int* fd, int64* offset, int64* size);

  
  bool prepared_;

  
  bool pending_play_;

  
  base::TimeDelta pending_seek_;

  
  bool should_seek_on_prepare_;

  
  GURL url_;

  
  GURL first_party_for_cookies_;

  
  const std::string user_agent_;

  
  bool hide_url_log_;

  
  base::TimeDelta duration_;
  int width_;
  int height_;

  
  bool can_pause_;
  bool can_seek_forward_;
  bool can_seek_backward_;

  
  std::string cookies_;

  
  base::android::ScopedJavaGlobalRef<jobject> j_media_player_bridge_;

  base::RepeatingTimer<MediaPlayerBridge> time_update_timer_;

  
  double volume_;

  
  bool allow_credentials_;

  
  base::WeakPtrFactory<MediaPlayerBridge> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaPlayerBridge);
};

}  

#endif  
