// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebMediaStream.h"

namespace webrtc {
class MediaStreamInterface;
}

namespace content {

class MediaStreamObserver {
 public:
  
  virtual void TrackAdded(const blink::WebMediaStreamTrack& track)  = 0;
  
  virtual void TrackRemoved(const blink::WebMediaStreamTrack& track) = 0;

 protected:
  virtual ~MediaStreamObserver() {}
};

class CONTENT_EXPORT MediaStream
    : NON_EXPORTED_BASE(public blink::WebMediaStream::ExtraData) {
 public:
  
  MediaStream(const blink::WebMediaStream& stream);

  
  
  
  explicit MediaStream(webrtc::MediaStreamInterface* webrtc_stream);

  virtual ~MediaStream();

  
  static MediaStream* GetMediaStream(
      const blink::WebMediaStream& stream);

  
  
  
  static webrtc::MediaStreamInterface* GetAdapter(
      const blink::WebMediaStream& stream);

  
  
  void AddObserver(MediaStreamObserver* observer);
  void RemoveObserver(MediaStreamObserver* observer);

  
  
  bool is_local() const { return is_local_; }

  
  bool AddTrack(const blink::WebMediaStreamTrack& track);

  
  bool RemoveTrack(const blink::WebMediaStreamTrack& track);

 protected:
  virtual webrtc::MediaStreamInterface* GetWebRtcAdapter(
      const blink::WebMediaStream& stream);

 private:
  base::ThreadChecker thread_checker_;
  const bool is_local_;
  const std::string label_;
  std::vector<MediaStreamObserver*> observers_;

  
  
  scoped_refptr<webrtc::MediaStreamInterface> webrtc_media_stream_;

  DISALLOW_COPY_AND_ASSIGN(MediaStream);
};

}  

#endif  
