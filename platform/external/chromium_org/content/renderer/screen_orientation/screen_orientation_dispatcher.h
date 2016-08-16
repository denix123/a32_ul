// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_SCREEN_ORIENTATION_SCREEN_ORIENTATION_DISPATCHER_H_
#define CONTENT_RENDERER_SCREEN_ORIENTATION_SCREEN_ORIENTATION_DISPATCHER_H_

#include "base/compiler_specific.h"
#include "base/id_map.h"
#include "base/macros.h"
#include "content/public/renderer/render_frame_observer.h"
#include "third_party/WebKit/public/platform/WebLockOrientationCallback.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationClient.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationLockType.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationType.h"

namespace content {

class RenderFrame;

class CONTENT_EXPORT ScreenOrientationDispatcher :
    public RenderFrameObserver,
    NON_EXPORTED_BASE(public blink::WebScreenOrientationClient) {
 public:
  explicit ScreenOrientationDispatcher(RenderFrame* render_frame);
  virtual ~ScreenOrientationDispatcher();

 private:
  friend class ScreenOrientationDispatcherTest;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void lockOrientation(
      blink::WebScreenOrientationLockType orientation,
      blink::WebLockOrientationCallback* callback) OVERRIDE;
  virtual void unlockOrientation() OVERRIDE;

  void OnLockSuccess(int request_id);
  void OnLockError(int request_id,
                   blink::WebLockOrientationError error);

  void CancelPendingLocks();

  
  
  
  
  
  typedef IDMap<blink::WebLockOrientationCallback, IDMapOwnPointer> CallbackMap;
  CallbackMap pending_callbacks_;

  DISALLOW_COPY_AND_ASSIGN(ScreenOrientationDispatcher);
};

}  

#endif 
