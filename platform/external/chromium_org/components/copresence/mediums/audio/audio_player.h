// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_MEDIUMS_AUDIO_AUDIO_PLAYER_H_
#define COMPONENTS_COPRESENCE_MEDIUMS_AUDIO_AUDIO_PLAYER_H_

#include <vector>

#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "media/audio/audio_io.h"

namespace media {
class AudioBus;
class AudioBusRefCounted;
}

namespace copresence {

class AudioPlayer : public media::AudioOutputStream::AudioSourceCallback {
 public:
  AudioPlayer();

  
  virtual void Initialize();

  
  
  virtual void Play(const scoped_refptr<media::AudioBusRefCounted>& samples);

  
  virtual void Stop();

  
  virtual void Finalize();

  bool IsPlaying();

  
  void set_output_stream_for_testing(
      media::AudioOutputStream* output_stream_for_testing) {
    output_stream_for_testing_.reset(output_stream_for_testing);
  }

 protected:
  virtual ~AudioPlayer();
  void set_is_playing(bool is_playing) { is_playing_ = is_playing; }

 private:
  friend class AudioPlayerTest;
  FRIEND_TEST_ALL_PREFIXES(AudioPlayerTest, BasicPlayAndStop);
  FRIEND_TEST_ALL_PREFIXES(AudioPlayerTest, OutOfOrderPlayAndStopMultiple);

  
  
  void InitializeOnAudioThread();
  void PlayOnAudioThread(
      const scoped_refptr<media::AudioBusRefCounted>& samples);
  void StopOnAudioThread();
  void StopAndCloseOnAudioThread();
  void FinalizeOnAudioThread();

  
  
  virtual int OnMoreData(media::AudioBus* dest,
                         media::AudioBuffersState ) OVERRIDE;
  virtual void OnError(media::AudioOutputStream* ) OVERRIDE;

  
  
  void FlushAudioLoopForTesting();

  bool is_playing_;

  
  media::AudioOutputStream* stream_;

  scoped_ptr<media::AudioOutputStream> output_stream_for_testing_;

  
  base::Lock state_lock_;

  scoped_refptr<media::AudioBusRefCounted> samples_;

  
  int frame_index_;

  DISALLOW_COPY_AND_ASSIGN(AudioPlayer);
};

}  

#endif  
