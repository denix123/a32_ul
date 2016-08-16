// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_AUDIO_BLOCK_FIFO_H_
#define MEDIA_BASE_AUDIO_BLOCK_FIFO_H_

#include "base/memory/scoped_vector.h"
#include "media/base/audio_bus.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT AudioBlockFifo {
 public:
  
  
  AudioBlockFifo(int channels, int frames, int blocks);
  virtual ~AudioBlockFifo();

  
  
  
  void Push(const void* source, int frames, int bytes_per_sample);

  
  
  
  const AudioBus* Consume();

  
  void Clear();

  
  int available_blocks() const { return available_blocks_; }

  
  int GetAvailableFrames() const;

  
  int GetUnfilledFrames() const;

  
  void IncreaseCapacity(int blocks);

 private:
  
  ScopedVector<AudioBus> audio_blocks_;

  
  const int channels_;

  
  
  const int block_frames_;

  // Used to keep track which block of memory to be written.
  int write_block_;

  
  int read_block_;

  
  int available_blocks_;

  // Current write position in the current written block.
  int write_pos_;

  DISALLOW_COPY_AND_ASSIGN(AudioBlockFifo);
};

}  

#endif  
