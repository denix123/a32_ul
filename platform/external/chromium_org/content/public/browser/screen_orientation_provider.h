// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_SCREEN_ORIENTATION_PROVIDER_H_
#define CONTENT_PUBLIC_BROWSER_SCREEN_ORIENTATION_PROVIDER_H_

#include "base/macros.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationLockType.h"

namespace content {

class ScreenOrientationDispatcherHost;
class WebContents;

class CONTENT_EXPORT ScreenOrientationProvider {
 public:
  
  virtual void LockOrientation(
      int request_id,
      blink::WebScreenOrientationLockType orientations) = 0;

  
  virtual void UnlockOrientation() = 0;

  
  
  virtual void OnOrientationChange() = 0;

  virtual ~ScreenOrientationProvider() {}

 protected:
  friend class ScreenOrientationDispatcherHostImpl;

  static ScreenOrientationProvider* Create(
      ScreenOrientationDispatcherHost* dispatcher_host,
      WebContents* web_contents);

  ScreenOrientationProvider() {}

  DISALLOW_COPY_AND_ASSIGN(ScreenOrientationProvider);
};

#if !defined(OS_ANDROID)
ScreenOrientationProvider* ScreenOrientationProvider::Create(
    ScreenOrientationDispatcherHost* dispatcher_host,
    WebContents* web_contents) {
  return NULL;
}
#endif 

} 

#endif 
