// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_MEDIUMS_AUDIO_AUDIO_RECORDER_H_
#define COMPONENTS_COPRESENCE_MEDIUMS_AUDIO_AUDIO_RECORDER_H_

#include <string>

#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "media/audio/audio_io.h"
#include "media/audio/audio_parameters.h"
#include "media/base/audio_converter.h"

namespace base {
class MessageLoop;
}

namespace media {
class AudioBus;
}

namespace copresence {

class AudioRecorder : public media::AudioInputStream::AudioInputCallback,
                      public media::AudioConverter::InputCallback {
 public:
  typedef base::Callback<void(const std::string&)> DecodeSamplesCallback;

  explicit AudioRecorder(const DecodeSamplesCallback& decode_callback);

  
  virtual void Initialize();

  virtual void Record();
  virtual void Stop();

  
  virtual void Finalize();

  bool IsRecording();

  
  void set_input_stream_for_testing(
      media::AudioInputStream* input_stream_for_testing) {
    input_stream_for_testing_.reset(input_stream_for_testing);
  }

  
  void set_params_for_testing(media::AudioParameters* params_for_testing) {
    params_for_testing_.reset(params_for_testing);
  }

 protected:
  virtual ~AudioRecorder();
  void set_is_recording(bool is_recording) { is_recording_ = is_recording; }

 private:
  friend class AudioRecorderTest;
  FRIEND_TEST_ALL_PREFIXES(AudioRecorderTest, BasicRecordAndStop);
  FRIEND_TEST_ALL_PREFIXES(AudioRecorderTest, OutOfOrderRecordAndStopMultiple);

  
  
  void InitializeOnAudioThread();
  void RecordOnAudioThread();
  void StopOnAudioThread();
  void StopAndCloseOnAudioThread();
  void FinalizeOnAudioThread();

  
  
  
  
  virtual void OnData(media::AudioInputStream* stream,
                      const media::AudioBus* source,
                      uint32 hardware_delay_bytes,
                      double volume) OVERRIDE;
  virtual void OnError(media::AudioInputStream* stream) OVERRIDE;

  
  virtual double ProvideInput(media::AudioBus* dest,
                              base::TimeDelta buffer_delay) OVERRIDE;

  
  
  void FlushAudioLoopForTesting();

  bool is_recording_;

  media::AudioInputStream* stream_;
  DecodeSamplesCallback decode_callback_;

  
  const media::AudioBus* temp_conversion_buffer_;

  
  
  scoped_ptr<media::AudioBus> buffer_;
  int total_buffer_frames_;
  int buffer_frame_index_;

  scoped_ptr<media::AudioConverter> converter_;

  scoped_ptr<media::AudioInputStream> input_stream_for_testing_;
  scoped_ptr<media::AudioParameters> params_for_testing_;

  DISALLOW_COPY_AND_ASSIGN(AudioRecorder);
};

}  

#endif  
