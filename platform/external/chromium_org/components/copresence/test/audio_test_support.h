// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_COMMON_AUDIO_TEST_SUPPORT_
#define COMPONENTS_COPRESENCE_COMMON_AUDIO_TEST_SUPPORT_

#include <cstddef>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

namespace media {
class AudioBus;
class AudioBusRefCounted;
}

namespace copresence {

void PopulateSamples(int random_seed, size_t size, float* samples);

scoped_ptr<media::AudioBus> CreateRandomAudio(int random_seed,
                                              int channels,
                                              int samples);

scoped_refptr<media::AudioBusRefCounted>
    CreateRandomAudioRefCounted(int random_seed, int channels, int samples);

}  

#endif  
