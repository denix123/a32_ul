// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MOJO_SERVICES_MOJO_RENDERER_SERVICE_H_
#define MEDIA_MOJO_SERVICES_MOJO_RENDERER_SERVICE_H_

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/audio_hardware_config.h"
#include "media/base/buffering_state.h"
#include "media/base/pipeline_status.h"
#include "media/mojo/interfaces/media_renderer.mojom.h"
#include "mojo/public/cpp/bindings/interface_impl.h"

namespace mojo {
class ApplicationConnection;
}

namespace media {

class AudioRenderer;
class MojoDemuxerStreamAdapter;

class MojoRendererService : public mojo::InterfaceImpl<mojo::MediaRenderer> {
 public:
  
  
  
  
  explicit MojoRendererService(mojo::ApplicationConnection* connection);
  virtual ~MojoRendererService();

  
  virtual void Initialize(mojo::DemuxerStreamPtr stream,
                          const mojo::Callback<void()>& callback) MOJO_OVERRIDE;
  virtual void Flush(const mojo::Callback<void()>& callback) MOJO_OVERRIDE;
  virtual void StartPlayingFrom(int64_t time_delta_usec) MOJO_OVERRIDE;
  virtual void SetPlaybackRate(float playback_rate) MOJO_OVERRIDE;
  virtual void SetVolume(float volume) MOJO_OVERRIDE;

 private:
  
  
  void OnStreamReady();

  
  void OnAudioRendererInitializeDone(PipelineStatus status);

  
  void OnUpdateStatistics(const PipelineStatistics& stats);

  
  void OnAudioTimeUpdate(base::TimeDelta time, base::TimeDelta max_time);

  
  
  void OnBufferingStateChanged(BufferingState new_buffering_state);

  
  void OnAudioRendererEnded();

  
  void OnError(PipelineStatus error);

  scoped_ptr<MojoDemuxerStreamAdapter> stream_;
  scoped_ptr<AudioRenderer> audio_renderer_;

  mojo::Callback<void()> init_cb_;

  
  
  
  
  media::AudioHardwareConfig hardware_config_;

  base::WeakPtrFactory<MojoRendererService> weak_factory_;
  base::WeakPtr<MojoRendererService> weak_this_;
  DISALLOW_COPY_AND_ASSIGN(MojoRendererService);
};

}  

#endif  
