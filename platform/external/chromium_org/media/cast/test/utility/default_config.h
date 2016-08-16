// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_TEST_UTILITY_DEFAULT_CONFIG_H_
#define MEDIA_CAST_TEST_UTILITY_DEFAULT_CONFIG_H_

#include "media/cast/cast_config.h"

namespace media {
namespace cast {

FrameReceiverConfig GetDefaultAudioReceiverConfig();

FrameReceiverConfig GetDefaultVideoReceiverConfig();

AudioSenderConfig GetDefaultAudioSenderConfig();

VideoSenderConfig GetDefaultVideoSenderConfig();

CreateVideoEncodeAcceleratorCallback
    CreateDefaultVideoEncodeAcceleratorCallback();

CreateVideoEncodeMemoryCallback CreateDefaultVideoEncodeMemoryCallback();

}  
}  

#endif  
