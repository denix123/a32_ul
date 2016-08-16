// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_FILTERS_AUDIO_RENDERER_ALGORITHM_H_
#define MEDIA_FILTERS_AUDIO_RENDERER_ALGORITHM_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "media/audio/audio_parameters.h"
#include "media/base/audio_buffer.h"
#include "media/base/audio_buffer_queue.h"

namespace media {

class AudioBus;

class MEDIA_EXPORT AudioRendererAlgorithm {
 public:
  AudioRendererAlgorithm();
  ~AudioRendererAlgorithm();

  
  void Initialize(const AudioParameters& params);

  
  
  
  
  
  
  
  int FillBuffer(AudioBus* dest, int requested_frames, float playback_rate);

  
  void FlushBuffers();

  
  
  void EnqueueBuffer(const scoped_refptr<AudioBuffer>& buffer_in);

  
  bool IsQueueFull();

  
  int QueueCapacity() const { return capacity_; }

  
  void IncreaseQueueCapacity();

  
  
  
  int frames_buffered() { return audio_buffer_.frames(); }

  
  int samples_per_second() { return samples_per_second_; }

 private:
  
  
  
  
  void GetOptimalBlock();

  
  
  int WriteCompletedFramesTo(
      int requested_frames, int output_offset, AudioBus* dest);

  
  
  
  
  
  
  
  void PeekAudioWithZeroPrepend(int read_offset_frames, AudioBus* dest);

  
  
  
  bool RunOneWsolaIteration(float playback_rate);

  
  
  void RemoveOldInputFrames(float playback_rate);

  
  
  void UpdateOutputTime(float playback_rate, double time_change);

  
  
  bool TargetIsWithinSearchRegion() const;

  
  bool CanPerformWsola() const;

  
  int channels_;

  
  int samples_per_second_;

  
  AudioBufferQueue audio_buffer_;

  
  double muted_partial_frame_;

  
  int capacity_;

  
  
  
  
  
  
  
  
  double output_time_;

  
  int search_block_center_offset_;

  
  int search_block_index_;

  
  
  int num_candidate_blocks_;

  
  int target_block_index_;

  
  int ola_window_size_;

  
  
  int ola_hop_size_;

  
  
  
  int num_complete_frames_;

  
  
  
  
  
  scoped_ptr<AudioBus> wsola_output_;

  
  scoped_ptr<float[]> ola_window_;

  
  
  scoped_ptr<float[]> transition_window_;

  

  
  
  
  scoped_ptr<AudioBus> optimal_block_;

  
  scoped_ptr<AudioBus> search_block_;

  
  
  
  scoped_ptr<AudioBus> target_block_;

  DISALLOW_COPY_AND_ASSIGN(AudioRendererAlgorithm);
};

}  

#endif  
