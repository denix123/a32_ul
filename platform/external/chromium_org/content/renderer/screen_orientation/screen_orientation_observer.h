// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/public/renderer/platform_event_observer.h"

namespace content {

class ScreenOrientationObserver
    : public PlatformEventObserver<blink::WebPlatformEventListener> {
 public:
  ScreenOrientationObserver();

  
  virtual void Start(blink::WebPlatformEventListener* listener) OVERRIDE;

 protected:
  virtual void SendStartMessage() OVERRIDE;
  virtual void SendStopMessage() OVERRIDE;
};

}; 
