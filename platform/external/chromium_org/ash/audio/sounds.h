// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_AUDIO_SOUNDS_H_
#define ASH_AUDIO_SOUNDS_H_

#include "ash/ash_export.h"
#include "media/audio/sounds/sounds_manager.h"

namespace ash {

ASH_EXPORT bool PlaySystemSoundAlways(media::SoundsManager::SoundKey key);

ASH_EXPORT bool PlaySystemSoundIfSpokenFeedback(
    media::SoundsManager::SoundKey key);

}  

#endif  
