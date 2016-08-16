// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_AUDIO_BUFFER_H_
#define PPAPI_CPP_AUDIO_BUFFER_H_

#include "ppapi/c/ppb_audio_buffer.h"
#include "ppapi/cpp/resource.h"

namespace pp {

class AudioBuffer : public Resource {
 public:
  
  
  AudioBuffer();

  
  
  
  AudioBuffer(const AudioBuffer& other);

  
  
  
  explicit AudioBuffer(const Resource& resource);

  
  
  
  
  AudioBuffer(PassRef, PP_Resource resource);

  virtual ~AudioBuffer();

  
  
  
  
  PP_TimeDelta GetTimestamp() const;

  
  
  
  
  
  void SetTimestamp(PP_TimeDelta timestamp);

  
  
  
  PP_AudioBuffer_SampleRate GetSampleRate() const;

  
  
  
  PP_AudioBuffer_SampleSize GetSampleSize() const;

  
  
  
  uint32_t GetNumberOfChannels() const;

  
  
  
  
  
  uint32_t GetNumberOfSamples() const;

  
  
  
  void* GetDataBuffer();

  
  
  
  uint32_t GetDataBufferSize() const;
};

}  

#endif  
