// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SCREEN_ORIENTATION_SCREEN_ORIENTATION_DISPATCHER_HOST_IMPL_H_
#define CONTENT_BROWSER_SCREEN_ORIENTATION_SCREEN_ORIENTATION_DISPATCHER_HOST_IMPL_H_

#include "content/public/browser/screen_orientation_dispatcher_host.h"
#include "content/public/browser/web_contents_observer.h"
#include "third_party/WebKit/public/platform/WebLockOrientationError.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationLockType.h"

namespace content {

class RenderFrameHost;
class ScreenOrientationProvider;
class WebContents;

class CONTENT_EXPORT ScreenOrientationDispatcherHostImpl
    : public ScreenOrientationDispatcherHost,
      public WebContentsObserver {
 public:
  explicit ScreenOrientationDispatcherHostImpl(WebContents* web_contents);
  virtual ~ScreenOrientationDispatcherHostImpl();

  
  virtual void NotifyLockSuccess(int request_id) OVERRIDE;
  virtual void NotifyLockError(int request_id,
                               blink::WebLockOrientationError error) OVERRIDE;
  virtual void OnOrientationChange() OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message&,
                                 RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void DidNavigateMainFrame(const LoadCommittedDetails& details,
                                    const FrameNavigateParams& params) OVERRIDE;

 private:
  void OnLockRequest(RenderFrameHost* render_frame_host,
                     blink::WebScreenOrientationLockType orientation,
                     int request_id);
  void OnUnlockRequest(RenderFrameHost* render_frame_host);

  
  
  RenderFrameHost* GetRenderFrameHostForRequestID(int request_id);

  void ResetCurrentLock();
  void NotifyLockError(int request_id,
                       RenderFrameHost* render_frame_host,
                       blink::WebLockOrientationError error);

  scoped_ptr<ScreenOrientationProvider> provider_;

  struct LockInformation {
    LockInformation(int request_id, int process_id, int routing_id);
    int request_id;
    int process_id;
    int routing_id;
  };
  
  LockInformation* current_lock_;

  DISALLOW_COPY_AND_ASSIGN(ScreenOrientationDispatcherHostImpl);
};

}  

#endif 
