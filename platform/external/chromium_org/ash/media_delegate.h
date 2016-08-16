// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_MEDIA_DELEGATE_H_
#define ASH_MEDIA_DELEGATE_H_

namespace content {
class BrowserContext;
}

namespace ash {

enum MediaCaptureState {
  MEDIA_CAPTURE_NONE = 0,
  MEDIA_CAPTURE_AUDIO = 1 << 0,
  MEDIA_CAPTURE_VIDEO = 1 << 1,
  MEDIA_CAPTURE_AUDIO_VIDEO = MEDIA_CAPTURE_AUDIO | MEDIA_CAPTURE_VIDEO,
};

class MediaDelegate {
 public:
  virtual ~MediaDelegate() {}

  
  virtual void HandleMediaNextTrack() = 0;

  
  virtual void HandleMediaPlayPause() = 0;

  
  virtual void HandleMediaPrevTrack() = 0;

  
  
  virtual MediaCaptureState GetMediaCaptureState(
      content::BrowserContext* context) = 0;
};

}  

#endif  
