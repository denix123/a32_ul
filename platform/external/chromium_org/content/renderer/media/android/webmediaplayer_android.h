// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_ANDROID_WEBMEDIAPLAYER_ANDROID_H_
#define CONTENT_RENDERER_MEDIA_ANDROID_WEBMEDIAPLAYER_ANDROID_H_

#include <jni.h>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/default_tick_clock.h"
#include "base/time/time.h"
#include "cc/layers/video_frame_provider.h"
#include "content/common/media/media_player_messages_enums_android.h"
#include "content/public/renderer/render_frame_observer.h"
#include "content/renderer/media/android/media_info_loader.h"
#include "content/renderer/media/android/media_source_delegate.h"
#include "content/renderer/media/android/stream_texture_factory.h"
#include "content/renderer/media/crypto/proxy_decryptor.h"
#include "gpu/command_buffer/common/mailbox.h"
#include "media/base/android/media_player_android.h"
#include "media/base/demuxer_stream.h"
#include "media/base/media_keys.h"
#include "media/base/time_delta_interpolator.h"
#include "third_party/WebKit/public/platform/WebGraphicsContext3D.h"
#include "third_party/WebKit/public/platform/WebMediaPlayer.h"
#include "third_party/WebKit/public/platform/WebSize.h"
#include "third_party/WebKit/public/platform/WebURL.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/gpu/GrContext.h"
#include "third_party/skia/include/gpu/SkGrPixelRef.h"
#include "ui/gfx/rect_f.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace blink {
class WebContentDecryptionModule;
class WebContentDecryptionModuleResult;
class WebFrame;
class WebURL;
}

namespace cc_blink {
class WebLayerImpl;
}

namespace gpu {
struct MailboxHolder;
}

namespace media {
class MediaLog;
class WebMediaPlayerDelegate;
}

namespace content {
class RendererCdmManager;
class RendererMediaPlayerManager;
class WebContentDecryptionModuleImpl;

class WebMediaPlayerAndroid : public blink::WebMediaPlayer,
                              public cc::VideoFrameProvider,
                              public RenderFrameObserver,
                              public StreamTextureFactoryContextObserver {
 public:
  
  
  
  
  
  
  WebMediaPlayerAndroid(
      blink::WebFrame* frame,
      blink::WebMediaPlayerClient* client,
      base::WeakPtr<media::WebMediaPlayerDelegate> delegate,
      RendererMediaPlayerManager* player_manager,
      RendererCdmManager* cdm_manager,
      blink::WebContentDecryptionModule* initial_cdm,
      scoped_refptr<StreamTextureFactory> factory,
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      media::MediaLog* media_log);
  virtual ~WebMediaPlayerAndroid();

  
  virtual void enterFullscreen();
  virtual bool canEnterFullscreen() const;

  
  virtual void load(LoadType load_type,
                    const blink::WebURL& url,
                    CORSMode cors_mode);

  
  virtual void play();
  virtual void pause();
  virtual void seek(double seconds);
  virtual bool supportsSave() const;
  virtual void setRate(double rate);
  virtual void setVolume(double volume);
  virtual void requestRemotePlayback();
  virtual void requestRemotePlaybackControl();
  virtual blink::WebTimeRanges buffered() const;
  virtual double maxTimeSeekable() const;

  
  virtual void setPoster(const blink::WebURL& poster) OVERRIDE;

  
  
  
  
  
  virtual void paint(blink::WebCanvas* canvas,
                     const blink::WebRect& rect,
                     unsigned char alpha,
                     SkXfermode::Mode mode);
  
  virtual void paint(blink::WebCanvas* canvas,
                     const blink::WebRect& rect,
                     unsigned char alpha);

  virtual bool copyVideoTextureToPlatformTexture(
      blink::WebGraphicsContext3D* web_graphics_context,
      unsigned int texture,
      unsigned int level,
      unsigned int internal_format,
      unsigned int type,
      bool premultiply_alpha,
      bool flip_y);

  
  virtual bool hasVideo() const;
  virtual bool hasAudio() const;

  virtual bool isRemote() const;

  
  virtual blink::WebSize naturalSize() const;

  
  virtual bool paused() const;
  virtual bool seeking() const;
  virtual double duration() const;
  virtual double timelineOffset() const;
  virtual double currentTime() const;

  virtual bool didLoadingProgress();

  
  virtual blink::WebMediaPlayer::NetworkState networkState() const;
  virtual blink::WebMediaPlayer::ReadyState readyState() const;

  virtual bool hasSingleSecurityOrigin() const;
  virtual bool didPassCORSAccessCheck() const;

  virtual double mediaTimeForTimeValue(double timeValue) const;

  
  virtual unsigned decodedFrameCount() const;
  virtual unsigned droppedFrameCount() const;
  virtual unsigned audioDecodedByteCount() const;
  virtual unsigned videoDecodedByteCount() const;

  
  
  virtual void SetVideoFrameProviderClient(
      cc::VideoFrameProvider::Client* client) OVERRIDE;
  virtual scoped_refptr<media::VideoFrame> GetCurrentFrame() OVERRIDE;
  virtual void PutCurrentFrame(const scoped_refptr<media::VideoFrame>& frame)
      OVERRIDE;

  
  void OnMediaMetadataChanged(const base::TimeDelta& duration, int width,
                              int height, bool success);
  void OnPlaybackComplete();
  void OnBufferingUpdate(int percentage);
  void OnSeekRequest(const base::TimeDelta& time_to_seek);
  void OnSeekComplete(const base::TimeDelta& current_time);
  void OnMediaError(int error_type);
  void OnVideoSizeChanged(int width, int height);
  void OnDurationChanged(const base::TimeDelta& duration);

  
  void OnTimeUpdate(base::TimeDelta current_timestamp,
                    base::TimeTicks current_time_ticks);

  
  void OnConnectedToRemoteDevice(const std::string& remote_playback_message);
  void OnDisconnectedFromRemoteDevice();
  void OnDidEnterFullscreen();
  void OnDidExitFullscreen();
  void OnMediaPlayerPlay();
  void OnMediaPlayerPause();
  void OnRequestFullscreen();
  void OnRemoteRouteAvailabilityChanged(bool routes_available);

  
  virtual void ResetStreamTextureProxy() OVERRIDE;

  
  virtual void OnPlayerReleased();

  
  
  
  virtual void ReleaseMediaResources();

  
  virtual void OnDestruct() OVERRIDE;

#if defined(VIDEO_HOLE)
  
  
  
  bool UpdateBoundaryRectangle();

  const gfx::RectF GetBoundaryRectangle();
#endif  

  virtual MediaKeyException generateKeyRequest(
      const blink::WebString& key_system,
      const unsigned char* init_data,
      unsigned init_data_length);
  virtual MediaKeyException addKey(
      const blink::WebString& key_system,
      const unsigned char* key,
      unsigned key_length,
      const unsigned char* init_data,
      unsigned init_data_length,
      const blink::WebString& session_id);
  virtual MediaKeyException cancelKeyRequest(
      const blink::WebString& key_system,
      const blink::WebString& session_id);
  
  
  virtual void setContentDecryptionModule(
      blink::WebContentDecryptionModule* cdm);
  virtual void setContentDecryptionModule(
      blink::WebContentDecryptionModule* cdm,
      blink::WebContentDecryptionModuleResult result);

  void OnKeyAdded(const std::string& session_id);
  void OnKeyError(const std::string& session_id,
                  media::MediaKeys::KeyError error_code,
                  uint32 system_code);
  void OnKeyMessage(const std::string& session_id,
                    const std::vector<uint8>& message,
                    const GURL& destination_url);

  void OnMediaSourceOpened(blink::WebMediaSource* web_media_source);

  void OnNeedKey(const std::string& type,
                 const std::vector<uint8>& init_data);

  
  

 protected:
  
  void UpdatePlayingState(bool is_playing_);

  
  void UpdateNetworkState(blink::WebMediaPlayer::NetworkState state);
  void UpdateReadyState(blink::WebMediaPlayer::ReadyState state);
  void TryCreateStreamTextureProxyIfNeeded();
  void DoCreateStreamTexture();

  
  
  void EstablishSurfaceTexturePeer();

  
  void SetNeedsEstablishPeer(bool needs_establish_peer);

 private:
  void InitializePlayer(const GURL& url,
                        const GURL& first_party_for_cookies,
                        bool allowed_stored_credentials,
                        int demuxer_client_id);
  void Pause(bool is_media_related_action);
  void DrawRemotePlaybackText(const std::string& remote_playback_message);
  void ReallocateVideoFrame();
  void SetCurrentFrameInternal(scoped_refptr<media::VideoFrame>& frame);
  void DidLoadMediaInfo(MediaInfoLoader::Status status,
                        const GURL& redirected_url,
                        const GURL& first_party_for_cookies,
                        bool allow_stored_credentials);
  bool IsKeySystemSupported(const std::string& key_system);
  bool IsLocalResource();

  
  
  MediaKeyException GenerateKeyRequestInternal(const std::string& key_system,
                                               const unsigned char* init_data,
                                               unsigned init_data_length);
  MediaKeyException AddKeyInternal(const std::string& key_system,
                                   const unsigned char* key,
                                   unsigned key_length,
                                   const unsigned char* init_data,
                                   unsigned init_data_length,
                                   const std::string& session_id);
  MediaKeyException CancelKeyRequestInternal(const std::string& key_system,
                                             const std::string& session_id);

  
  
  
  
  void SetDecryptorReadyCB(const media::DecryptorReadyCB& decryptor_ready_cb);

  
  
  void ContentDecryptionModuleAttached(
      blink::WebContentDecryptionModuleResult result,
      bool success);

  bool EnsureTextureBackedSkBitmap(GrContext* gr, SkBitmap& bitmap,
                                   const blink::WebSize& size,
                                   GrSurfaceOrigin origin,
                                   GrPixelConfig config);

  bool IsHLSStream() const;

  blink::WebFrame* const frame_;

  blink::WebMediaPlayerClient* const client_;

  
  
  
  
  
  base::WeakPtr<media::WebMediaPlayerDelegate> delegate_;

  
  blink::WebTimeRanges buffered_;

  
  blink::WebSize natural_size_;

  
  blink::WebSize cached_stream_texture_size_;

  
  scoped_refptr<media::VideoFrame> current_frame_;
  base::Lock current_frame_lock_;

  base::ThreadChecker main_thread_checker_;

  
  const scoped_refptr<base::SingleThreadTaskRunner> media_task_runner_;

  
  GURL url_;

  
  
  GURL redirected_url_;

  
  base::TimeDelta duration_;

  
  
  
  bool ignore_metadata_duration_change_;

  
  
  bool pending_seek_;
  base::TimeDelta pending_seek_time_;

  
  bool seeking_;
  base::TimeDelta seek_time_;

  
  bool did_loading_progress_;

  
  
  RendererMediaPlayerManager* player_manager_;

  
  
  
  RendererCdmManager* cdm_manager_;

  
  int player_id_;

  
  blink::WebMediaPlayer::NetworkState network_state_;
  blink::WebMediaPlayer::ReadyState ready_state_;

  
  unsigned int texture_id_;

  
  
  gpu::Mailbox texture_mailbox_;

  
  unsigned int stream_id_;

  
  bool is_playing_;

  
  bool needs_establish_peer_;

  
  bool has_size_info_;

  const scoped_refptr<base::MessageLoopProxy> compositor_loop_;

  
  scoped_refptr<StreamTextureFactory> stream_texture_factory_;

  
  
  
  
  ScopedStreamTextureProxy stream_texture_proxy_;

  
  
  bool needs_external_surface_;

  
  
  
  
  cc::VideoFrameProvider::Client* video_frame_provider_client_;

  scoped_ptr<cc_blink::WebLayerImpl> video_weblayer_;

#if defined(VIDEO_HOLE)
  
  
  gfx::RectF last_computed_rect_;

  
  
  bool force_use_overlay_embedded_video_;
#endif  

  MediaPlayerHostMsg_Initialize_Type player_type_;

  
  bool is_remote_;

  scoped_refptr<media::MediaLog> media_log_;

  scoped_ptr<MediaInfoLoader> info_loader_;

  
  
  std::string current_key_system_;

  
  
  std::string init_data_type_;

  
  scoped_ptr<ProxyDecryptor> proxy_decryptor_;

  
  
  WebContentDecryptionModuleImpl* web_cdm_;

  
  
  
  
  media::DecryptorReadyCB decryptor_ready_cb_;

  SkBitmap bitmap_;

  
  bool allow_stored_credentials_;

  
  bool is_local_resource_;

  
  base::DefaultTickClock default_tick_clock_;

  
  
  media::TimeDeltaInterpolator interpolator_;

  scoped_ptr<MediaSourceDelegate> media_source_delegate_;

  
  base::WeakPtrFactory<WebMediaPlayerAndroid> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebMediaPlayerAndroid);
};

}  

#endif  
