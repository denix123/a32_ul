/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_AUDIO_BUFFER_H_
#define PPAPI_C_PPB_AUDIO_BUFFER_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_time.h"

#define PPB_AUDIOBUFFER_INTERFACE_0_1 "PPB_AudioBuffer;0.1"
#define PPB_AUDIOBUFFER_INTERFACE PPB_AUDIOBUFFER_INTERFACE_0_1



typedef enum {
  PP_AUDIOBUFFER_SAMPLERATE_UNKNOWN = 0,
  PP_AUDIOBUFFER_SAMPLERATE_8000 = 8000,
  PP_AUDIOBUFFER_SAMPLERATE_16000 = 16000,
  PP_AUDIOBUFFER_SAMPLERATE_22050 = 22050,
  PP_AUDIOBUFFER_SAMPLERATE_32000 = 32000,
  PP_AUDIOBUFFER_SAMPLERATE_44100 = 44100,
  PP_AUDIOBUFFER_SAMPLERATE_48000 = 48000,
  PP_AUDIOBUFFER_SAMPLERATE_96000 = 96000,
  PP_AUDIOBUFFER_SAMPLERATE_192000 = 192000
} PP_AudioBuffer_SampleRate;

typedef enum {
  PP_AUDIOBUFFER_SAMPLESIZE_UNKNOWN = 0,
  PP_AUDIOBUFFER_SAMPLESIZE_16_BITS = 2
} PP_AudioBuffer_SampleSize;

struct PPB_AudioBuffer_0_1 {
  PP_Bool (*IsAudioBuffer)(PP_Resource resource);
  PP_TimeDelta (*GetTimestamp)(PP_Resource buffer);
  void (*SetTimestamp)(PP_Resource buffer, PP_TimeDelta timestamp);
  PP_AudioBuffer_SampleRate (*GetSampleRate)(PP_Resource buffer);
  PP_AudioBuffer_SampleSize (*GetSampleSize)(PP_Resource buffer);
  uint32_t (*GetNumberOfChannels)(PP_Resource buffer);
  uint32_t (*GetNumberOfSamples)(PP_Resource buffer);
  void* (*GetDataBuffer)(PP_Resource buffer);
  uint32_t (*GetDataBufferSize)(PP_Resource buffer);
};

typedef struct PPB_AudioBuffer_0_1 PPB_AudioBuffer;

#endif  

