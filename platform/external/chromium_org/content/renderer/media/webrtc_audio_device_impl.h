// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_AUDIO_DEVICE_IMPL_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_AUDIO_DEVICE_IMPL_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/files/file.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "content/renderer/media/webrtc_audio_capturer.h"
#include "content/renderer/media/webrtc_audio_device_not_impl.h"
#include "ipc/ipc_platform_file.h"
#include "media/base/audio_capturer_source.h"
#include "media/base/audio_renderer_sink.h"


namespace content {

class WebRtcAudioCapturer;
class WebRtcAudioRenderer;

class WebRtcAudioRendererSource {
 public:
  
  virtual void RenderData(media::AudioBus* audio_bus,
                          int sample_rate,
                          int audio_delay_milliseconds,
                          base::TimeDelta* current_time) = 0;

  
  virtual void RemoveAudioRenderer(WebRtcAudioRenderer* renderer) = 0;

 protected:
  virtual ~WebRtcAudioRendererSource() {}
};

class PeerConnectionAudioSink {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  virtual int OnData(const int16* audio_data,
                     int sample_rate,
                     int number_of_channels,
                     int number_of_frames,
                     const std::vector<int>& channels,
                     int audio_delay_milliseconds,
                     int current_volume,
                     bool need_audio_processing,
                     bool key_pressed) = 0;

  
  
  
  virtual void OnSetFormat(const media::AudioParameters& params) = 0;

 protected:
 virtual ~PeerConnectionAudioSink() {}
};

class WebRtcPlayoutDataSource {
 public:
  class Sink {
   public:
    
    
    virtual void OnPlayoutData(media::AudioBus* audio_bus,
                               int sample_rate,
                               int audio_delay_milliseconds) = 0;

    
    
    virtual void OnPlayoutDataSourceChanged() = 0;

   protected:
    virtual ~Sink() {}
  };

  
  
  
  virtual void AddPlayoutSink(Sink* sink) = 0;
  virtual void RemovePlayoutSink(Sink* sink) = 0;

 protected:
  virtual ~WebRtcPlayoutDataSource() {}
};

class CONTENT_EXPORT WebRtcAudioDeviceImpl
    : NON_EXPORTED_BASE(public PeerConnectionAudioSink),
      NON_EXPORTED_BASE(public WebRtcAudioDeviceNotImpl),
      NON_EXPORTED_BASE(public WebRtcAudioRendererSource),
      NON_EXPORTED_BASE(public WebRtcPlayoutDataSource) {
 public:
  
  static const int kMaxVolumeLevel = 255;

  
  WebRtcAudioDeviceImpl();

  
  
  
  
  virtual int32_t AddRef() OVERRIDE;
  virtual int32_t Release() OVERRIDE;

  
  
  

  virtual int32_t RegisterAudioCallback(webrtc::AudioTransport* audio_callback)
      OVERRIDE;

  virtual int32_t Init() OVERRIDE;
  virtual int32_t Terminate() OVERRIDE;
  virtual bool Initialized() const OVERRIDE;

  virtual int32_t PlayoutIsAvailable(bool* available) OVERRIDE;
  virtual bool PlayoutIsInitialized() const OVERRIDE;
  virtual int32_t RecordingIsAvailable(bool* available) OVERRIDE;
  virtual bool RecordingIsInitialized() const OVERRIDE;

  
  virtual int32_t StartPlayout() OVERRIDE;
  virtual int32_t StopPlayout() OVERRIDE;
  virtual bool Playing() const OVERRIDE;
  virtual int32_t StartRecording() OVERRIDE;
  virtual int32_t StopRecording() OVERRIDE;
  virtual bool Recording() const OVERRIDE;

  
  virtual int32_t SetMicrophoneVolume(uint32_t volume) OVERRIDE;

  
  virtual int32_t MicrophoneVolume(uint32_t* volume) const OVERRIDE;

  virtual int32_t MaxMicrophoneVolume(uint32_t* max_volume) const OVERRIDE;
  virtual int32_t MinMicrophoneVolume(uint32_t* min_volume) const OVERRIDE;
  virtual int32_t StereoPlayoutIsAvailable(bool* available) const OVERRIDE;
  virtual int32_t StereoRecordingIsAvailable(bool* available) const OVERRIDE;
  virtual int32_t PlayoutDelay(uint16_t* delay_ms) const OVERRIDE;
  virtual int32_t RecordingDelay(uint16_t* delay_ms) const OVERRIDE;
  virtual int32_t RecordingSampleRate(uint32_t* sample_rate) const OVERRIDE;
  virtual int32_t PlayoutSampleRate(uint32_t* sample_rate) const OVERRIDE;

  
  
  bool SetAudioRenderer(WebRtcAudioRenderer* renderer);

  
  
  
  void AddAudioCapturer(const scoped_refptr<WebRtcAudioCapturer>& capturer);
  void RemoveAudioCapturer(const scoped_refptr<WebRtcAudioCapturer>& capturer);

  
  
  scoped_refptr<WebRtcAudioCapturer> GetDefaultCapturer() const;

  
  
  
  
  
  
  
  bool GetAuthorizedDeviceInfoForAudioRenderer(
      int* session_id, int* output_sample_rate, int* output_buffer_size);

  const scoped_refptr<WebRtcAudioRenderer>& renderer() const {
    return renderer_;
  }

 private:
  typedef std::list<scoped_refptr<WebRtcAudioCapturer> > CapturerList;
  typedef std::list<WebRtcPlayoutDataSource::Sink*> PlayoutDataSinkList;
  class RenderBuffer;

  
  virtual ~WebRtcAudioDeviceImpl();

  

  
  virtual int OnData(const int16* audio_data,
                     int sample_rate,
                     int number_of_channels,
                     int number_of_frames,
                     const std::vector<int>& channels,
                     int audio_delay_milliseconds,
                     int current_volume,
                     bool need_audio_processing,
                     bool key_pressed) OVERRIDE;

  
  virtual void OnSetFormat(const media::AudioParameters& params) OVERRIDE;

  

  
  virtual void RenderData(media::AudioBus* audio_bus,
                          int sample_rate,
                          int audio_delay_milliseconds,
                          base::TimeDelta* current_time) OVERRIDE;

  
  virtual void RemoveAudioRenderer(WebRtcAudioRenderer* renderer) OVERRIDE;

  
  virtual void AddPlayoutSink(WebRtcPlayoutDataSource::Sink* sink) OVERRIDE;
  virtual void RemovePlayoutSink(WebRtcPlayoutDataSource::Sink* sink) OVERRIDE;

  
  base::ThreadChecker thread_checker_;

  int ref_count_;

  
  
  CapturerList capturers_;

  
  scoped_refptr<WebRtcAudioRenderer> renderer_;

  
  
  
  PlayoutDataSinkList playout_sinks_;

  
  
  
  webrtc::AudioTransport* audio_transport_callback_;

  
  int input_delay_ms_;

  
  int output_delay_ms_;

  
  
  mutable base::Lock lock_;

  
  
  mutable base::Lock capture_callback_lock_;

  bool initialized_;
  bool playing_;
  bool recording_;

  
  
  uint32_t microphone_volume_;

  
  
  std::vector<int16> render_buffer_;

  
  const bool is_audio_track_processing_enabled_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcAudioDeviceImpl);
};

}  

#endif  
