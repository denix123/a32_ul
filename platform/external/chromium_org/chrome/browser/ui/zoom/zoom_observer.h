// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ZOOM_ZOOM_OBSERVER_H_
#define CHROME_BROWSER_UI_ZOOM_ZOOM_OBSERVER_H_

#include "chrome/browser/ui/zoom/zoom_controller.h"

namespace content {
class WebContents;
}

class ZoomObserver {
 public:
  
  virtual void OnZoomChanged(const ZoomController::ZoomChangedEventData& data) {
  }

 protected:
  virtual ~ZoomObserver() {}
};

#endif  
