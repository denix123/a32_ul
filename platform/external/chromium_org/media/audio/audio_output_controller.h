// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_AUDIO_AUDIO_OUTPUT_CONTROLLER_H_
#define MEDIA_AUDIO_AUDIO_OUTPUT_CONTROLLER_H_

#include "base/atomic_ref_count.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/timer/timer.h"
#include "build/build_config.h"
#include "media/audio/audio_io.h"
#include "media/audio/audio_manager.h"
#include "media/audio/audio_power_monitor.h"
#include "media/audio/audio_source_diverter.h"
#include "media/audio/simple_sources.h"
#include "media/base/media_export.h"


namespace media {

class MEDIA_EXPORT AudioOutputController
    : public base::RefCountedThreadSafe<AudioOutputController>,
      public AudioOutputStream::AudioSourceCallback,
      public AudioSourceDiverter,
      NON_EXPORTED_BASE(public AudioManager::AudioDeviceListener)  {
 public:
  
  
  class MEDIA_EXPORT EventHandler {
   public:
    virtual void OnCreated() = 0;
    virtual void OnPlaying() = 0;
    virtual void OnPaused() = 0;
    virtual void OnError() = 0;
    virtual void OnDeviceChange(int new_buffer_size, int new_sample_rate) = 0;

   protected:
    virtual ~EventHandler() {}
  };

  
  
  
  
  class SyncReader {
   public:
    virtual ~SyncReader() {}

    
    
    
    virtual void UpdatePendingBytes(uint32 bytes) = 0;

    
    
    virtual void Read(AudioBus* dest) = 0;

    
    virtual void Close() = 0;
  };

  
  
  
  
  
  
  
  static scoped_refptr<AudioOutputController> Create(
      AudioManager* audio_manager, EventHandler* event_handler,
      const AudioParameters& params, const std::string& output_device_id,
      SyncReader* sync_reader);

  
  
  static bool will_monitor_audio_levels() {
#if defined(OS_ANDROID) || defined(OS_IOS)
    return false;
#else
    return true;
#endif
  }

  

  
  void Play();

  
  void Pause();

  
  
  
  
  
  
  
  void Close(const base::Closure& closed_task);

  
  void SetVolume(double volume);

  
  
  void GetOutputDeviceId(
      base::Callback<void(const std::string&)> callback) const;

  
  
  
  
  
  
  
  
  
  void SwitchOutputDevice(const std::string& output_device_id,
                          const base::Closure& callback);

  
  virtual int OnMoreData(AudioBus* dest,
                         AudioBuffersState buffers_state) OVERRIDE;
  virtual void OnError(AudioOutputStream* stream) OVERRIDE;

  
  
  
  
  virtual void OnDeviceChange() OVERRIDE;

  
  virtual const AudioParameters& GetAudioParameters() OVERRIDE;
  virtual void StartDiverting(AudioOutputStream* to_stream) OVERRIDE;
  virtual void StopDiverting() OVERRIDE;

  
  
  std::pair<float, bool> ReadCurrentPowerAndClip();

 protected:
  
  enum State {
    kEmpty,
    kCreated,
    kPlaying,
    kPaused,
    kClosed,
    kError,
  };

  
  
  enum { kPowerMeasurementTimeConstantMillis = 10 };

  friend class base::RefCountedThreadSafe<AudioOutputController>;
  virtual ~AudioOutputController();

 private:
  AudioOutputController(AudioManager* audio_manager, EventHandler* handler,
                        const AudioParameters& params,
                        const std::string& output_device_id,
                        SyncReader* sync_reader);

  
  void DoCreate(bool is_for_device_change);
  void DoPlay();
  void DoPause();
  void DoClose();
  void DoSetVolume(double volume);
  std::string DoGetOutputDeviceId() const;
  void DoSwitchOutputDevice(const std::string& output_device_id);
  void DoReportError();
  void DoStartDiverting(AudioOutputStream* to_stream);
  void DoStopDiverting();

  
  void StopStream();

  
  void DoStopCloseAndClearStream();

  
  void WedgeCheck();

  AudioManager* const audio_manager_;
  const AudioParameters params_;
  EventHandler* const handler_;

  
  
  std::string output_device_id_;

  AudioOutputStream* stream_;

  
  AudioOutputStream* diverting_to_stream_;

  
  double volume_;

  // |state_| is written on the audio manager thread and is read on the
  
  
  State state_;

  
  SyncReader* const sync_reader_;

  
  const scoped_refptr<base::SingleThreadTaskRunner> message_loop_;

  
  AudioPowerMonitor power_monitor_;

  
  base::AtomicRefCount on_more_io_data_called_;
  scoped_ptr<base::OneShotTimer<AudioOutputController> > wedge_timer_;

  DISALLOW_COPY_AND_ASSIGN(AudioOutputController);
};

}  

#endif  
