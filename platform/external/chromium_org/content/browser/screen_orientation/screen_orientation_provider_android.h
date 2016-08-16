// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SCREEN_ORIENTATION_SCREEN_ORIENTATION_PROVIDER_ANDROID_H_
#define CONTENT_BROWSER_SCREEN_ORIENTATION_SCREEN_ORIENTATION_PROVIDER_ANDROID_H_

#include <jni.h>

#include "base/compiler_specific.h"
#include "content/public/browser/screen_orientation_provider.h"
#include "content/public/browser/web_contents_observer.h"

namespace content {

class ScreenOrientationDispatcherHost;
class WebContentsImpl;

class ScreenOrientationProviderAndroid : public ScreenOrientationProvider,
                                         public WebContentsObserver {
 public:
  explicit ScreenOrientationProviderAndroid(
      ScreenOrientationDispatcherHost* dispatcher,
      WebContents* web_contents);

  static bool Register(JNIEnv* env);

  
  virtual void LockOrientation(int request_id,
                               blink::WebScreenOrientationLockType) OVERRIDE;
  virtual void UnlockOrientation() OVERRIDE;
  virtual void OnOrientationChange() OVERRIDE;

  
  virtual void DidToggleFullscreenModeForTab(bool entered_fullscreen) OVERRIDE;

  
  
  
  static void StartAccurateListening();

  
  
  
  static void StopAccurateListening();

 private:
  WebContentsImpl* web_contents_impl();

  
  
  bool LockMatchesCurrentOrientation(blink::WebScreenOrientationLockType lock);

  
  
  
  blink::WebScreenOrientationLockType GetNaturalLockType() const;

  virtual ~ScreenOrientationProviderAndroid();

  
  
  ScreenOrientationDispatcherHost* dispatcher_;

  
  bool lock_applied_;

  struct LockInformation {
    LockInformation(int request_id, blink::WebScreenOrientationLockType lock);
    int request_id;
    blink::WebScreenOrientationLockType lock;
  };
  LockInformation* pending_lock_;

  DISALLOW_COPY_AND_ASSIGN(ScreenOrientationProviderAndroid);
};

} 

#endif 
