// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_WEBMEDIAPLAYER_IMPL_H_
#define MEDIA_BLINK_WEBMEDIAPLAYER_IMPL_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "media/base/audio_renderer_sink.h"
#include "media/base/media_export.h"
#include "media/base/media_keys.h"
#include "media/base/pipeline.h"
#include "media/base/text_track.h"
#include "media/blink/buffered_data_source.h"
#include "media/blink/buffered_data_source_host_impl.h"
#include "media/blink/video_frame_compositor.h"
#include "media/filters/skcanvas_video_renderer.h"
#include "third_party/WebKit/public/platform/WebAudioSourceProvider.h"
#include "third_party/WebKit/public/platform/WebContentDecryptionModuleResult.h"
#include "third_party/WebKit/public/platform/WebGraphicsContext3D.h"
#include "third_party/WebKit/public/platform/WebMediaPlayer.h"
#include "third_party/WebKit/public/platform/WebMediaPlayerClient.h"
#include "url/gurl.h"

namespace blink {
class WebLocalFrame;
}

namespace base {
class SingleThreadTaskRunner;
}

namespace cc_blink {
class WebLayerImpl;
}

namespace media {
class AudioHardwareConfig;
class ChunkDemuxer;
class EncryptedMediaPlayerSupport;
class GpuVideoAcceleratorFactories;
class MediaLog;
class VideoFrameCompositor;
class WebAudioSourceProviderImpl;
class WebMediaPlayerDelegate;
class WebMediaPlayerParams;
class WebTextTrackImpl;

class MEDIA_EXPORT WebMediaPlayerImpl
    : public NON_EXPORTED_BASE(blink::WebMediaPlayer),
      public base::SupportsWeakPtr<WebMediaPlayerImpl> {
 public:
  
  
  WebMediaPlayerImpl(blink::WebLocalFrame* frame,
                     blink::WebMediaPlayerClient* client,
                     base::WeakPtr<WebMediaPlayerDelegate> delegate,
                     const WebMediaPlayerParams& params);
  virtual ~WebMediaPlayerImpl();

  virtual void load(LoadType load_type,
                    const blink::WebURL& url,
                    CORSMode cors_mode);

  
  virtual void play();
  virtual void pause();
  virtual bool supportsSave() const;
  virtual void seek(double seconds);
  virtual void setRate(double rate);
  virtual void setVolume(double volume);
  virtual void setPreload(blink::WebMediaPlayer::Preload preload);
  virtual blink::WebTimeRanges buffered() const;
  virtual double maxTimeSeekable() const;

  
  virtual void paint(blink::WebCanvas* canvas,
                     const blink::WebRect& rect,
                     unsigned char alpha,
                     SkXfermode::Mode mode);
  
  virtual void paint(blink::WebCanvas* canvas,
                     const blink::WebRect& rect,
                     unsigned char alpha);

  
  virtual bool hasVideo() const;
  virtual bool hasAudio() const;

  
  virtual blink::WebSize naturalSize() const;

  
  virtual bool paused() const;
  virtual bool seeking() const;
  virtual double duration() const;
  virtual double timelineOffset() const;
  virtual double currentTime() const;

  
  
  
  virtual blink::WebMediaPlayer::NetworkState networkState() const;
  virtual blink::WebMediaPlayer::ReadyState readyState() const;

  virtual bool didLoadingProgress();

  virtual bool hasSingleSecurityOrigin() const;
  virtual bool didPassCORSAccessCheck() const;

  virtual double mediaTimeForTimeValue(double timeValue) const;

  virtual unsigned decodedFrameCount() const;
  virtual unsigned droppedFrameCount() const;
  virtual unsigned audioDecodedByteCount() const;
  virtual unsigned videoDecodedByteCount() const;

  virtual bool copyVideoTextureToPlatformTexture(
      blink::WebGraphicsContext3D* web_graphics_context,
      unsigned int texture,
      unsigned int level,
      unsigned int internal_format,
      unsigned int type,
      bool premultiply_alpha,
      bool flip_y);

  virtual blink::WebAudioSourceProvider* audioSourceProvider();

  virtual MediaKeyException generateKeyRequest(
      const blink::WebString& key_system,
      const unsigned char* init_data,
      unsigned init_data_length);

  virtual MediaKeyException addKey(const blink::WebString& key_system,
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

  void OnPipelineSeeked(bool time_changed, PipelineStatus status);
  void OnPipelineEnded();
  void OnPipelineError(PipelineStatus error);
  void OnPipelineMetadata(PipelineMetadata metadata);
  void OnPipelineBufferingStateChanged(BufferingState buffering_state);
  void OnDemuxerOpened();
  void OnAddTextTrack(const TextTrackConfig& config,
                      const AddTextTrackDoneCB& done_cb);

 private:
  
  
  void DoLoad(LoadType load_type,
              const blink::WebURL& url,
              CORSMode cors_mode);

  
  void DataSourceInitialized(bool success);

  
  void NotifyDownloading(bool is_downloading);

  
  scoped_ptr<Renderer> CreateRenderer();

  
  void StartPipeline();

  
  
  void SetNetworkState(blink::WebMediaPlayer::NetworkState state);
  void SetReadyState(blink::WebMediaPlayer::ReadyState state);

  
  double GetPipelineDuration() const;

  
  void OnDurationChanged();
  void OnNaturalSizeChanged(gfx::Size size);
  void OnOpacityChanged(bool opaque);

  
  
  void FrameReady(const scoped_refptr<VideoFrame>& frame);

  
  
  scoped_refptr<VideoFrame> GetCurrentFrameFromCompositor();

  blink::WebLocalFrame* frame_;

  
  blink::WebMediaPlayer::NetworkState network_state_;
  blink::WebMediaPlayer::ReadyState ready_state_;

  
  BufferedDataSource::Preload preload_;

  
  
  const scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;

  scoped_refptr<base::SingleThreadTaskRunner> media_task_runner_;
  scoped_refptr<MediaLog> media_log_;
  Pipeline pipeline_;

  
  LoadType load_type_;

  
  PipelineMetadata pipeline_metadata_;

  
  bool opaque_;

  
  
  
  
  
  
  
  
  
  
  
  
  bool paused_;
  bool seeking_;
  double playback_rate_;
  base::TimeDelta paused_time_;

  
  
  bool ended_;

  
  
  bool pending_seek_;
  double pending_seek_seconds_;

  
  
  bool should_notify_time_changed_;

  blink::WebMediaPlayerClient* client_;

  base::WeakPtr<WebMediaPlayerDelegate> delegate_;

  base::Callback<void(const base::Closure&)> defer_load_cb_;

  
  scoped_refptr<GpuVideoAcceleratorFactories> gpu_factories_;

  
  scoped_refptr<WebAudioSourceProviderImpl> audio_source_provider_;

  bool supports_save_;

  
  
  
  
  
  
  scoped_ptr<BufferedDataSource> data_source_;
  scoped_ptr<Demuxer> demuxer_;
  ChunkDemuxer* chunk_demuxer_;

  BufferedDataSourceHostImpl buffered_data_source_host_;

  
  scoped_refptr<base::SingleThreadTaskRunner> compositor_task_runner_;
  VideoFrameCompositor* compositor_;  
  SkCanvasVideoRenderer skcanvas_video_renderer_;

  
  
  scoped_ptr<cc_blink::WebLayerImpl> video_weblayer_;

  
  int text_track_index_;

  scoped_ptr<EncryptedMediaPlayerSupport> encrypted_media_support_;

  const AudioHardwareConfig& audio_hardware_config_;

  DISALLOW_COPY_AND_ASSIGN(WebMediaPlayerImpl);
};

}  

#endif  
