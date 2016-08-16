// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_ANDROID_BROWSER_MEDIA_PLAYER_MANAGER_H_
#define CONTENT_BROWSER_MEDIA_ANDROID_BROWSER_MEDIA_PLAYER_MANAGER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"
#include "content/browser/android/content_video_view.h"
#include "content/common/content_export.h"
#include "content/common/media/media_player_messages_enums_android.h"
#include "ipc/ipc_message.h"
#include "media/base/android/media_player_android.h"
#include "media/base/android/media_player_manager.h"
#include "media/base/android/media_url_interceptor.h"
#include "ui/gfx/rect_f.h"
#include "url/gurl.h"

namespace media {
class DemuxerAndroid;
}

struct MediaPlayerHostMsg_Initialize_Params;

namespace content {
class BrowserDemuxerAndroid;
class ContentViewCoreImpl;
class ExternalVideoSurfaceContainer;
class RenderFrameHost;
class WebContents;

class CONTENT_EXPORT BrowserMediaPlayerManager
    : public media::MediaPlayerManager {
 public:
  
  typedef BrowserMediaPlayerManager* (*Factory)(RenderFrameHost*);
  static void RegisterFactory(Factory factory);

  
  static void RegisterMediaUrlInterceptor(
      media::MediaUrlInterceptor* media_url_interceptor);

  
  static BrowserMediaPlayerManager* Create(RenderFrameHost* rfh);

  ContentViewCoreImpl* GetContentViewCore() const;

  virtual ~BrowserMediaPlayerManager();

  
  virtual void FullscreenPlayerPlay();
  virtual void FullscreenPlayerPause();
  virtual void FullscreenPlayerSeek(int msec);
  virtual void ExitFullscreen(bool release_media_player);
  virtual void SetVideoSurface(gfx::ScopedJavaSurface surface);

  
  
  void OnSeekRequest(int player_id, const base::TimeDelta& time_to_seek);

  
  void ReleaseAllMediaPlayers();

  
  virtual void OnTimeUpdate(
      int player_id,
      base::TimeDelta current_timestamp,
      base::TimeTicks current_time_ticks) OVERRIDE;
  virtual void OnMediaMetadataChanged(
      int player_id,
      base::TimeDelta duration,
      int width,
      int height,
      bool success) OVERRIDE;
  virtual void OnPlaybackComplete(int player_id) OVERRIDE;
  virtual void OnMediaInterrupted(int player_id) OVERRIDE;
  virtual void OnBufferingUpdate(int player_id, int percentage) OVERRIDE;
  virtual void OnSeekComplete(
      int player_id,
      const base::TimeDelta& current_time) OVERRIDE;
  virtual void OnError(int player_id, int error) OVERRIDE;
  virtual void OnVideoSizeChanged(
      int player_id, int width, int height) OVERRIDE;
  virtual media::MediaResourceGetter* GetMediaResourceGetter() OVERRIDE;
  virtual media::MediaUrlInterceptor* GetMediaUrlInterceptor() OVERRIDE;
  virtual media::MediaPlayerAndroid* GetFullscreenPlayer() OVERRIDE;
  virtual media::MediaPlayerAndroid* GetPlayer(int player_id) OVERRIDE;
  virtual void RequestFullScreen(int player_id) OVERRIDE;
#if defined(VIDEO_HOLE)
  virtual bool ShouldUseVideoOverlayForEmbeddedEncryptedVideo() OVERRIDE;

  void AttachExternalVideoSurface(int player_id, jobject surface);
  void DetachExternalVideoSurface(int player_id);
  void OnFrameInfoUpdated();
#endif  

  
  virtual void OnEnterFullscreen(int player_id);
  virtual void OnExitFullscreen(int player_id);
  virtual void OnInitialize(
      const MediaPlayerHostMsg_Initialize_Params& media_player_params);
  virtual void OnStart(int player_id);
  virtual void OnSeek(int player_id, const base::TimeDelta& time);
  virtual void OnPause(int player_id, bool is_media_related_action);
  virtual void OnSetVolume(int player_id, double volume);
  virtual void OnSetPoster(int player_id, const GURL& poster);
  virtual void OnReleaseResources(int player_id);
  virtual void OnDestroyPlayer(int player_id);
  virtual void OnRequestRemotePlayback(int player_id);
  virtual void OnRequestRemotePlaybackControl(int player_id);
  virtual void ReleaseFullscreenPlayer(media::MediaPlayerAndroid* player);
#if defined(VIDEO_HOLE)
  void OnNotifyExternalSurface(
      int player_id, bool is_request, const gfx::RectF& rect);
#endif  

 protected:
  
  explicit BrowserMediaPlayerManager(RenderFrameHost* render_frame_host);

  WebContents* web_contents() const { return web_contents_; }

  
  void AddPlayer(media::MediaPlayerAndroid* player);

  
  void RemovePlayer(int player_id);

  
  
  
  scoped_ptr<media::MediaPlayerAndroid> SwapPlayer(
      int player_id,
      media::MediaPlayerAndroid* player);

  int RoutingID();

  
  bool Send(IPC::Message* msg);

 private:
  
  media::MediaPlayerAndroid* CreateMediaPlayer(
      const MediaPlayerHostMsg_Initialize_Params& media_player_params,
      bool hide_url_log,
      media::MediaPlayerManager* manager,
      BrowserDemuxerAndroid* demuxer);

  
  
  
  
  
  virtual void OnMediaResourcesRequested(int player_id);

  
  void ReleaseMediaResources(int player_id);

  
  void ReleasePlayer(media::MediaPlayerAndroid* player);

#if defined(VIDEO_HOLE)
  void OnRequestExternalSurface(int player_id, const gfx::RectF& rect);
#endif  

  RenderFrameHost* const render_frame_host_;

  
  ScopedVector<media::MediaPlayerAndroid> players_;

  
  
  scoped_ptr<ContentVideoView> video_view_;

#if defined(VIDEO_HOLE)
  scoped_ptr<ExternalVideoSurfaceContainer> external_video_surface_container_;
#endif

  
  int fullscreen_player_id_;

  
  bool fullscreen_player_is_released_;

  WebContents* const web_contents_;

  
  scoped_ptr<media::MediaResourceGetter> media_resource_getter_;

  
  base::WeakPtrFactory<BrowserMediaPlayerManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BrowserMediaPlayerManager);
};

}  

#endif  
