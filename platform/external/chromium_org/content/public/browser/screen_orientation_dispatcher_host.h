// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_SCREEN_ORIENTATION_DISPATCHER_HOST_H_
#define CONTENT_PUBLIC_BROWSER_SCREEN_ORIENTATION_DISPATCHER_HOST_H_

#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebLockOrientationError.h"

namespace content {

class CONTENT_EXPORT ScreenOrientationDispatcherHost {
 public:
  virtual ~ScreenOrientationDispatcherHost() {}

  
  
  
  virtual void NotifyLockSuccess(int request_id) = 0;

  
  
  
  virtual void NotifyLockError(int request_id,
                               blink::WebLockOrientationError error) = 0;

  virtual void OnOrientationChange() = 0;
};

}  

#endif 
