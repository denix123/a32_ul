// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_MEDIA_STREAM_AUDIO_TRACK_H_
#define PPAPI_CPP_MEDIA_STREAM_AUDIO_TRACK_H_

#include <string>

#include "ppapi/c/ppb_media_stream_audio_track.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/var.h"


namespace pp {

class AudioBuffer;
class CompletionCallback;
template <typename T> class CompletionCallbackWithOutput;

class MediaStreamAudioTrack : public Resource {
 public:
  
  
  MediaStreamAudioTrack();

  
  
  
  MediaStreamAudioTrack(const MediaStreamAudioTrack& other);

  
  
  
  
  explicit MediaStreamAudioTrack(const Resource& resource);

  
  
  
  
  MediaStreamAudioTrack(PassRef, PP_Resource resource);

  ~MediaStreamAudioTrack();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t Configure(const int32_t attributes[],
                    const CompletionCallback& callback);

  
  
  
  
  
  
  
  int32_t GetAttrib(PP_MediaStreamAudioTrack_Attrib attrib,
                    int32_t* value);

  
  std::string GetId() const;

  
  
  
  bool HasEnded() const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t GetBuffer(
      const CompletionCallbackWithOutput<AudioBuffer>& callback);

  
  
  
  
  
  
  
  
  int32_t RecycleBuffer(const AudioBuffer& buffer);

  
  
  
  void Close();

  
  
  
  
  
  
  
  static bool IsMediaStreamAudioTrack(const Resource& resource);
};

}  

#endif  
