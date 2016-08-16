// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_FILTERS_AUDIO_RENDERER_IMPL_H_
#define MEDIA_FILTERS_AUDIO_RENDERER_IMPL_H_

#include <deque>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "media/base/audio_decoder.h"
#include "media/base/audio_renderer.h"
#include "media/base/audio_renderer_sink.h"
#include "media/base/decryptor.h"
#include "media/base/media_log.h"
#include "media/base/time_source.h"
#include "media/filters/audio_renderer_algorithm.h"
#include "media/filters/decoder_stream.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class AudioBufferConverter;
class AudioBus;
class AudioClock;
class AudioHardwareConfig;
class AudioSplicer;
class DecryptingDemuxerStream;

class MEDIA_EXPORT AudioRendererImpl
    : public AudioRenderer,
      public TimeSource,
      NON_EXPORTED_BASE(public AudioRendererSink::RenderCallback) {
 public:
  
  
  
  
  
  
  
  
  AudioRendererImpl(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      AudioRendererSink* sink,
      ScopedVector<AudioDecoder> decoders,
      const SetDecryptorReadyCB& set_decryptor_ready_cb,
      const AudioHardwareConfig& hardware_params,
      const scoped_refptr<MediaLog>& media_log);
  virtual ~AudioRendererImpl();

  
  virtual void StartTicking() OVERRIDE;
  virtual void StopTicking() OVERRIDE;
  virtual void SetPlaybackRate(float rate) OVERRIDE;
  virtual void SetMediaTime(base::TimeDelta time) OVERRIDE;
  virtual base::TimeDelta CurrentMediaTime() OVERRIDE;
  virtual base::TimeDelta CurrentMediaTimeForSyncingVideo() OVERRIDE;

  
  virtual void Initialize(DemuxerStream* stream,
                          const PipelineStatusCB& init_cb,
                          const StatisticsCB& statistics_cb,
                          const BufferingStateCB& buffering_state_cb,
                          const base::Closure& ended_cb,
                          const PipelineStatusCB& error_cb) OVERRIDE;
  virtual TimeSource* GetTimeSource() OVERRIDE;
  virtual void Flush(const base::Closure& callback) OVERRIDE;
  virtual void StartPlaying() OVERRIDE;
  virtual void SetVolume(float volume) OVERRIDE;

 private:
  friend class AudioRendererImplTest;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  enum State {
    kUninitialized,
    kInitializing,
    kFlushing,
    kFlushed,
    kPlaying
  };

  
  void DecodedAudioReady(AudioBufferStream::Status status,
                         const scoped_refptr<AudioBuffer>& buffer);

  
  
  bool HandleSplicerBuffer_Locked(const scoped_refptr<AudioBuffer>& buffer);

  
  
  void HandleAbortedReadOrDecodeError(bool is_decode_error);

  void StartRendering_Locked();
  void StopRendering_Locked();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual int Render(AudioBus* audio_bus,
                     int audio_delay_milliseconds) OVERRIDE;
  virtual void OnRenderError() OVERRIDE;

  
  
  
  
  void AttemptRead();
  void AttemptRead_Locked();
  bool CanRead_Locked();
  void ChangeState_Locked(State new_state);

  
  
  bool IsBeforeStartTime(const scoped_refptr<AudioBuffer>& buffer);

  
  
  void OnAudioBufferStreamInitialized(bool succes);

  
  
  void DoFlush_Locked();

  
  
  void ResetDecoder();

  
  void ResetDecoderDone();

  
  void OnNewSpliceBuffer(base::TimeDelta);

  
  void OnConfigChange();

  
  void SetBufferingState_Locked(BufferingState buffering_state);

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  scoped_ptr<AudioSplicer> splicer_;
  scoped_ptr<AudioBufferConverter> buffer_converter_;

  
  bool expecting_config_changes_;

  
  
  
  scoped_refptr<media::AudioRendererSink> sink_;

  scoped_ptr<AudioBufferStream> audio_buffer_stream_;

  
  const AudioHardwareConfig& hardware_config_;

  
  AudioParameters audio_parameters_;

  
  PipelineStatusCB init_cb_;
  BufferingStateCB buffering_state_cb_;
  base::Closure ended_cb_;
  PipelineStatusCB error_cb_;

  
  base::Closure flush_cb_;

  
  
  base::Lock lock_;

  
  float playback_rate_;
  scoped_ptr<AudioRendererAlgorithm> algorithm_;

  
  State state_;

  BufferingState buffering_state_;

  
  
  bool rendering_;
  bool sink_playing_;

  
  bool pending_read_;

  
  bool received_end_of_stream_;
  bool rendered_end_of_stream_;

  scoped_ptr<AudioClock> audio_clock_;

  
  
  base::TimeDelta start_timestamp_;

  
  
  base::TimeDelta ended_timestamp_;

  
  
  base::TimeTicks last_render_ticks_;

  

  
  base::WeakPtrFactory<AudioRendererImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AudioRendererImpl);
};

}  

#endif  
