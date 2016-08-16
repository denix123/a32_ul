// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_AUDIO_BUFFER_CONVERTER
#define MEDIA_BASE_AUDIO_BUFFER_CONVERTER

#include <deque>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/audio/audio_parameters.h"
#include "media/base/audio_converter.h"
#include "media/base/audio_timestamp_helper.h"
#include "media/base/media_export.h"

namespace media {

class AudioBuffer;
class AudioBus;

class MEDIA_EXPORT AudioBufferConverter : public AudioConverter::InputCallback {
 public:
  explicit AudioBufferConverter(const AudioParameters& output_params);
  virtual ~AudioBufferConverter();

  void AddInput(const scoped_refptr<AudioBuffer>& buffer);

  
  bool HasNextBuffer();

  
  scoped_refptr<AudioBuffer> GetNextBuffer();

  
  void Reset();

  
  
  void ResetTimestampState();

  int input_buffer_size_for_testing() const {
    return input_params_.frames_per_buffer();
  }
  int input_frames_left_for_testing() const {
    return input_frames_;
  }

 private:
  
  virtual double ProvideInput(AudioBus* audio_bus,
                              base::TimeDelta buffer_delay) OVERRIDE;

  
  void ResetConverter(const scoped_refptr<AudioBuffer>& input_buffer);

  
  void ConvertIfPossible();

  
  void Flush();

  
  AudioParameters output_params_;

  
  
  AudioParameters input_params_;

  typedef std::deque<scoped_refptr<AudioBuffer> > BufferQueue;

  
  
  BufferQueue queued_inputs_;

  
  
  int last_input_buffer_offset_;

  
  BufferQueue queued_outputs_;

  
  int input_frames_;

  
  double buffered_input_frames_;

  
  double io_sample_rate_ratio_;

  
  AudioTimestampHelper timestamp_helper_;

  
  
  bool is_flushing_;

  
  scoped_ptr<AudioConverter> audio_converter_;
};

}  

#endif  
