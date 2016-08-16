// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_AUDIO_PROCESSOR_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_AUDIO_PROCESSOR_H_

#include "base/atomicops.h"
#include "base/files/file.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/renderer/media/aec_dump_message_filter.h"
#include "content/renderer/media/webrtc_audio_device_impl.h"
#include "media/base/audio_converter.h"
#include "third_party/libjingle/source/talk/app/webrtc/mediastreaminterface.h"
#include "third_party/webrtc/modules/audio_processing/include/audio_processing.h"
#include "third_party/webrtc/modules/interface/module_common_types.h"

namespace blink {
class WebMediaConstraints;
}

namespace media {
class AudioBus;
class AudioFifo;
class AudioParameters;
}  

namespace webrtc {
class AudioFrame;
class TypingDetection;
}

namespace content {

class MediaStreamAudioBus;
class MediaStreamAudioFifo;
class RTCMediaConstraints;

using webrtc::AudioProcessorInterface;

class CONTENT_EXPORT MediaStreamAudioProcessor :
    NON_EXPORTED_BASE(public WebRtcPlayoutDataSource::Sink),
    NON_EXPORTED_BASE(public AudioProcessorInterface),
    NON_EXPORTED_BASE(public AecDumpMessageFilter::AecDumpDelegate) {
 public:
  
  
  static bool IsAudioTrackProcessingEnabled();

  
  
  
  MediaStreamAudioProcessor(const blink::WebMediaConstraints& constraints,
                            int effects,
                            WebRtcPlayoutDataSource* playout_data_source);

  
  
  
  
  
  void OnCaptureFormatChanged(const media::AudioParameters& source_params);

  
  
  
  
  void PushCaptureData(const media::AudioBus* audio_source);

  
  
  
  
  
  
  
  
  
  
  
  
  
  bool ProcessAndConsumeData(base::TimeDelta capture_delay,
                             int volume,
                             bool key_pressed,
                             int* new_volume,
                             int16** out);

  
  
  void Stop();

  
  
  const media::AudioParameters& InputFormat() const;
  const media::AudioParameters& OutputFormat() const;

  
  bool has_audio_processing() const { return audio_processing_ != NULL; }

  
  
  virtual void OnAecDumpFile(
      const IPC::PlatformFileForTransit& file_handle) OVERRIDE;
  virtual void OnDisableAecDump() OVERRIDE;
  virtual void OnIpcClosing() OVERRIDE;

 protected:
  friend class base::RefCountedThreadSafe<MediaStreamAudioProcessor>;
  virtual ~MediaStreamAudioProcessor();

 private:
  friend class MediaStreamAudioProcessorTest;
  FRIEND_TEST_ALL_PREFIXES(MediaStreamAudioProcessorTest,
                           GetAecDumpMessageFilter);

  
  virtual void OnPlayoutData(media::AudioBus* audio_bus,
                             int sample_rate,
                             int audio_delay_milliseconds) OVERRIDE;
  virtual void OnPlayoutDataSourceChanged() OVERRIDE;

  
  
  virtual void GetStats(AudioProcessorStats* stats) OVERRIDE;

  
  void InitializeAudioProcessingModule(
      const blink::WebMediaConstraints& constraints, int effects);

  
  void InitializeCaptureFifo(const media::AudioParameters& input_format);

  
  void InitializeRenderFifoIfNeeded(int sample_rate,
                                    int number_of_channels,
                                    int frames_per_buffer);

  
  
  
  int ProcessData(const float* const* process_ptrs,
                  int process_frames,
                  base::TimeDelta capture_delay,
                  int volume,
                  bool key_pressed,
                  float* const* output_ptrs);

  
  
  base::subtle::Atomic32 render_delay_ms_;

  
  scoped_ptr<webrtc::AudioProcessing> audio_processing_;

  
  scoped_ptr<MediaStreamAudioFifo> capture_fifo_;
  
  scoped_ptr<MediaStreamAudioBus> output_bus_;
  
  scoped_ptr<int16[]> output_data_;

  
  scoped_ptr<MediaStreamAudioFifo> render_fifo_;

  
  
  
  media::AudioParameters input_format_;
  media::AudioParameters output_format_;
  
  media::AudioParameters render_format_;

  
  
  WebRtcPlayoutDataSource* playout_data_source_;

  
  base::ThreadChecker main_thread_checker_;
  
  base::ThreadChecker capture_thread_checker_;
  
  base::ThreadChecker render_thread_checker_;

  
  bool audio_mirroring_;

  scoped_ptr<webrtc::TypingDetection> typing_detector_;
  
  
  
  base::subtle::Atomic32 typing_detected_;

  
  scoped_refptr<AecDumpMessageFilter> aec_dump_message_filter_;

  
  bool stopped_;
};

}  

#endif  
