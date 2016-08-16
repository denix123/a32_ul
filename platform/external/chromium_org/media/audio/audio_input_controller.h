// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_AUDIO_AUDIO_INPUT_CONTROLLER_H_
#define MEDIA_AUDIO_AUDIO_INPUT_CONTROLLER_H_

#include <string>
#include "base/atomicops.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/thread.h"
#include "base/timer/timer.h"
#include "media/audio/audio_io.h"
#include "media/audio/audio_manager_base.h"
#include "media/audio/audio_parameters.h"
#include "media/audio/audio_power_monitor.h"
#include "media/base/audio_bus.h"

namespace media {

#if !defined(OS_ANDROID) && !defined(OS_IOS)
#define AUDIO_POWER_MONITORING
#endif

class UserInputMonitor;

class MEDIA_EXPORT AudioInputController
    : public base::RefCountedThreadSafe<AudioInputController>,
      public AudioInputStream::AudioInputCallback {
 public:

  
  
  
  
  enum ErrorCode {
    
    UNKNOWN_ERROR = 0,

    
    STREAM_CREATE_ERROR,  

    
    STREAM_OPEN_ERROR,  

    
    
    STREAM_ERROR,  

    
    NO_DATA_ERROR,  
  };

  
  
  class MEDIA_EXPORT EventHandler {
   public:
    virtual void OnCreated(AudioInputController* controller) = 0;
    virtual void OnRecording(AudioInputController* controller) = 0;
    virtual void OnError(AudioInputController* controller,
                         ErrorCode error_code) = 0;
    virtual void OnData(AudioInputController* controller,
                        const AudioBus* data) = 0;
    virtual void OnLog(AudioInputController* controller,
                       const std::string& message) = 0;

   protected:
    virtual ~EventHandler() {}
  };

  
  
  class SyncWriter {
   public:
    virtual ~SyncWriter() {}

    
    
    virtual void UpdateRecordedBytes(uint32 bytes) = 0;

    
    virtual void Write(const AudioBus* data,
                       double volume,
                       bool key_pressed) = 0;

    
    virtual void Close() = 0;
  };

  
  
  
  class Factory {
   public:
    virtual AudioInputController* Create(
        AudioManager* audio_manager,
        EventHandler* event_handler,
        AudioParameters params,
        UserInputMonitor* user_input_monitor) = 0;

   protected:
    virtual ~Factory() {}
  };

  
  
  
  
  
  static scoped_refptr<AudioInputController> Create(
      AudioManager* audio_manager,
      EventHandler* event_handler,
      const AudioParameters& params,
      const std::string& device_id,
      UserInputMonitor* user_input_monitor);

  
  
  
  static void set_factory_for_testing(Factory* factory) { factory_ = factory; }
  AudioInputStream* stream_for_testing() { return stream_; }

  
  
  
  
  static scoped_refptr<AudioInputController> CreateLowLatency(
      AudioManager* audio_manager,
      EventHandler* event_handler,
      const AudioParameters& params,
      const std::string& device_id,
      
      SyncWriter* sync_writer,
      UserInputMonitor* user_input_monitor);

  
  
  
  
  
  static scoped_refptr<AudioInputController> CreateForStream(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      EventHandler* event_handler,
      AudioInputStream* stream,
      
      SyncWriter* sync_writer,
      UserInputMonitor* user_input_monitor);

  
  
  virtual void Record();

  
  
  
  
  
  
  
  
  virtual void Close(const base::Closure& closed_task);

  
  
  virtual void SetVolume(double volume);

  
  
  virtual void SetAutomaticGainControl(bool enabled);

  
  
  virtual void OnData(AudioInputStream* stream,
                      const AudioBus* source,
                      uint32 hardware_delay_bytes,
                      double volume) OVERRIDE;
  virtual void OnError(AudioInputStream* stream) OVERRIDE;

  bool SharedMemoryAndSyncSocketMode() const { return sync_writer_ != NULL; }

 protected:
  friend class base::RefCountedThreadSafe<AudioInputController>;

  
  enum State {
    CREATED,
    RECORDING,
    CLOSED
  };

#if defined(AUDIO_POWER_MONITORING)
  
  
  
  
  
  
  
  
  
  
  enum SilenceState {
    SILENCE_STATE_NO_MEASUREMENT = 0,
    SILENCE_STATE_ONLY_AUDIO = 1,
    SILENCE_STATE_ONLY_SILENCE = 2,
    SILENCE_STATE_AUDIO_AND_SILENCE = 3,
    SILENCE_STATE_MAX = SILENCE_STATE_AUDIO_AND_SILENCE
  };
#endif

  AudioInputController(EventHandler* handler,
                       SyncWriter* sync_writer,
                       UserInputMonitor* user_input_monitor);
  virtual ~AudioInputController();

  
  void DoCreate(AudioManager* audio_manager,
                const AudioParameters& params,
                const std::string& device_id);
  void DoCreateForLowLatency(AudioManager* audio_manager,
                             const AudioParameters& params,
                             const std::string& device_id);
  void DoCreateForStream(AudioInputStream* stream_to_control);
  void DoRecord();
  void DoClose();
  void DoReportError();
  void DoSetVolume(double volume);
  void DoSetAutomaticGainControl(bool enabled);
  void DoOnData(scoped_ptr<AudioBus> data);
  void DoLogAudioLevels(float level_dbfs, int microphone_volume_percent);

  
  
  void FirstCheckForNoData();

  
  
  void DoCheckForNoData();

  
  void DoStopCloseAndClearStream();

  void SetDataIsActive(bool enabled);
  bool GetDataIsActive();

#if defined(AUDIO_POWER_MONITORING)
  
  
  void UpdateSilenceState(bool silence);

  
  void LogSilenceState(SilenceState value);
#endif

  
  scoped_refptr<base::SingleThreadTaskRunner> creator_task_runner_;

  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  
  
  EventHandler* handler_;

  
  AudioInputStream* stream_;

  
  
  
  
  
  scoped_ptr<base::Timer> no_data_timer_;

  
  
  
  
  base::subtle::Atomic32 data_is_active_;

  // |state_| is written on the audio thread and is read on the hardware audio
  
  
  State state_;

  base::Lock lock_;

  
  SyncWriter* sync_writer_;

  static Factory* factory_;

  double max_volume_;

  UserInputMonitor* user_input_monitor_;

#if defined(AUDIO_POWER_MONITORING)
  
  scoped_ptr<AudioPowerMonitor> audio_level_;

  
  media::AudioParameters audio_params_;
  base::TimeTicks last_audio_level_log_time_;

  
  bool log_silence_state_;

  
  SilenceState silence_state_;
#endif

  size_t prev_key_down_count_;

  
  base::TimeTicks low_latency_create_time_;

  DISALLOW_COPY_AND_ASSIGN(AudioInputController);
};

}  

#endif  
