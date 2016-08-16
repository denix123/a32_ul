// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_MEDIA_STREAM_VIDEO_TRACK_H_
#define PPAPI_CPP_MEDIA_STREAM_VIDEO_TRACK_H_

#include <string>

#include "ppapi/c/ppb_media_stream_video_track.h"
#include "ppapi/cpp/resource.h"
#include "ppapi/cpp/var.h"


namespace pp {

class VideoFrame;
class CompletionCallback;
template <typename T> class CompletionCallbackWithOutput;

class MediaStreamVideoTrack : public Resource {
 public:
  
  
  MediaStreamVideoTrack();

  
  
  
  MediaStreamVideoTrack(const MediaStreamVideoTrack& other);

  
  
  
  
  explicit MediaStreamVideoTrack(const Resource& resource);

  
  
  explicit MediaStreamVideoTrack(const InstanceHandle& instance);

  
  
  
  
  MediaStreamVideoTrack(PassRef, PP_Resource resource);

  ~MediaStreamVideoTrack();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t Configure(const int32_t attributes[],
                    const CompletionCallback& callback);

  
  
  
  
  
  
  
  int32_t GetAttrib(PP_MediaStreamVideoTrack_Attrib attrib,
                    int32_t* value);

  
  std::string GetId() const;

  
  
  
  bool HasEnded() const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int32_t GetFrame(
      const CompletionCallbackWithOutput<VideoFrame>& callback);

  
  
  
  
  
  
  
  
  int32_t RecycleFrame(const VideoFrame& frame);

  
  
  void Close();

  
  
  
  int32_t GetEmptyFrame(
      const CompletionCallbackWithOutput<VideoFrame>& callback);

  
  
  
  int32_t PutFrame(const VideoFrame& frame);

  
  
  
  
  
  
  
  static bool IsMediaStreamVideoTrack(const Resource& resource);
};

}  

#endif  
