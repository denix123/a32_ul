// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_CHROMEOS_AURA_DESKTOP_CAPTURER_H_
#define REMOTING_HOST_CHROMEOS_AURA_DESKTOP_CAPTURER_H_

#include "base/memory/weak_ptr.h"
#include "third_party/webrtc/modules/desktop_capture/screen_capturer.h"

namespace cc {
class CopyOutputResult;
}  

namespace aura {
class Window;
}  

namespace remoting {

class AuraDesktopCapturer : public webrtc::DesktopCapturer {
 public:
  AuraDesktopCapturer();
  virtual ~AuraDesktopCapturer();

  
  virtual void Start(webrtc::DesktopCapturer::Callback* callback) OVERRIDE;
  virtual void Capture(const webrtc::DesktopRegion& region) OVERRIDE;

 private:
  friend class AuraDesktopCapturerTest;

  
  void OnFrameCaptured(scoped_ptr<cc::CopyOutputResult> result);

  
  webrtc::DesktopCapturer::Callback* callback_;

  
  aura::Window* desktop_window_;

  base::WeakPtrFactory<AuraDesktopCapturer> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AuraDesktopCapturer);
};

}  

#endif  
