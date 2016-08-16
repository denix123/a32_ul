// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_AUDIO_RENDERER_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_AUDIO_RENDERER_H_

#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "base/threading/non_thread_safe.h"
#include "base/threading/thread_checker.h"
#include "content/renderer/media/media_stream_audio_renderer.h"
#include "content/renderer/media/webrtc_audio_device_impl.h"
#include "media/base/audio_decoder.h"
#include "media/base/audio_pull_fifo.h"
#include "media/base/audio_renderer_sink.h"
#include "media/base/channel_layout.h"

namespace media {
class AudioOutputDevice;
}  

namespace webrtc {
class AudioSourceInterface;
class MediaStreamInterface;
}  

namespace content {

class WebRtcAudioRendererSource;

class CONTENT_EXPORT WebRtcAudioRenderer
    : NON_EXPORTED_BASE(public media::AudioRendererSink::RenderCallback),
      NON_EXPORTED_BASE(public MediaStreamAudioRenderer) {
 public:
  
  
  
  
  
  class PlayingState : public base::NonThreadSafe {
   public:
    PlayingState() : playing_(false), volume_(1.0f) {}

    bool playing() const {
      DCHECK(CalledOnValidThread());
      return playing_;
    }

    void set_playing(bool playing) {
      DCHECK(CalledOnValidThread());
      playing_ = playing;
    }

    float volume() const {
      DCHECK(CalledOnValidThread());
      return volume_;
    }

    void set_volume(float volume) {
      DCHECK(CalledOnValidThread());
      volume_ = volume;
    }

   private:
    bool playing_;
    float volume_;
  };

  WebRtcAudioRenderer(
      const scoped_refptr<webrtc::MediaStreamInterface>& media_stream,
      int source_render_view_id,
      int source_render_frame_id,
      int session_id,
      int sample_rate,
      int frames_per_buffer);

  
  
  bool Initialize(WebRtcAudioRendererSource* source);

  
  
  
  
  
  
  
  
  
  scoped_refptr<MediaStreamAudioRenderer> CreateSharedAudioRendererProxy(
      const scoped_refptr<webrtc::MediaStreamInterface>& media_stream);

  
  bool IsStarted() const;

  
  int channels() const { return sink_params_.channels(); }
  int sample_rate() const { return sink_params_.sample_rate(); }
  int frames_per_buffer() const { return sink_params_.frames_per_buffer(); }

 private:
  
  
  
  virtual void Start() OVERRIDE;
  virtual void Play() OVERRIDE;
  virtual void Pause() OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual void SetVolume(float volume) OVERRIDE;
  virtual base::TimeDelta GetCurrentRenderTime() const OVERRIDE;
  virtual bool IsLocalRenderer() const OVERRIDE;

  
  
  
  
  void EnterPlayState();

  
  
  void EnterPauseState();

 protected:
  virtual ~WebRtcAudioRenderer();

 private:
  enum State {
    UNINITIALIZED,
    PLAYING,
    PAUSED,
  };

  
  
  typedef std::vector<PlayingState*> PlayingStates;
  
  
  typedef std::map<webrtc::AudioSourceInterface*, PlayingStates>
      SourcePlayingStates;

  
  base::ThreadChecker thread_checker_;

  
  State state_;

  
  
  virtual int Render(media::AudioBus* audio_bus,
                     int audio_delay_milliseconds) OVERRIDE;
  virtual void OnRenderError() OVERRIDE;

  
  
  void SourceCallback(int fifo_frame_delay, media::AudioBus* audio_bus);

  
  
  void UpdateSourceVolume(webrtc::AudioSourceInterface* source);

  
  
  
  bool AddPlayingState(webrtc::AudioSourceInterface* source,
                       PlayingState* state);
  
  
  
  bool RemovePlayingState(webrtc::AudioSourceInterface* source,
                          PlayingState* state);

  
  
  
  
  
  void OnPlayStateChanged(
      const scoped_refptr<webrtc::MediaStreamInterface>& media_stream,
      PlayingState* state);

  
  const int source_render_view_id_;
  const int source_render_frame_id_;
  const int session_id_;

  
  scoped_refptr<media::AudioOutputDevice> sink_;

  
  const scoped_refptr<webrtc::MediaStreamInterface> media_stream_;

  
  WebRtcAudioRendererSource* source_;

  
  mutable base::Lock lock_;

  
  int play_ref_count_;

  
  int start_ref_count_;

  
  
  scoped_ptr<media::AudioPullFifo> audio_fifo_;

  
  
  int audio_delay_milliseconds_;

  
  int fifo_delay_milliseconds_;

  base::TimeDelta current_time_;

  
  PlayingState playing_state_;

  
  media::AudioParameters sink_params_;

  
  
  
  
  
  SourcePlayingStates source_playing_states_;

  
  
  int render_callback_count_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(WebRtcAudioRenderer);
};

}  

#endif  
