// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CAPTURE_WEB_CONTENTS_TRACKER_H_
#define CONTENT_BROWSER_MEDIA_CAPTURE_WEB_CONTENTS_TRACKER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"
#include "content/public/browser/web_contents_observer.h"

namespace base {
class MessageLoopProxy;
}

namespace content {

class RenderWidgetHost;

class CONTENT_EXPORT WebContentsTracker
    : public base::RefCountedThreadSafe<WebContentsTracker>,
      public WebContentsObserver {
 public:
  
  
  
  
  explicit WebContentsTracker(bool track_fullscreen_rwh);

  
  
  
  typedef base::Callback<void(RenderWidgetHost* rwh)> ChangeCallback;

  
  
  
  
  
  virtual void Start(int render_process_id, int main_render_frame_id,
                     const ChangeCallback& callback);

  
  
  virtual void Stop();

  
  RenderWidgetHost* GetTargetRenderWidgetHost() const;

 protected:
  friend class base::RefCountedThreadSafe<WebContentsTracker>;
  virtual ~WebContentsTracker();

 private:
  
  
  
  
  void OnPossibleTargetChange(bool force_callback_run);

  
  
  void MaybeDoCallback(RenderWidgetHost* rwh);

  
  
  void StartObservingWebContents(int render_process_id,
                                 int main_render_frame_id);

  
  
  
  virtual void RenderFrameDeleted(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void RenderFrameHostChanged(RenderFrameHost* old_host,
                                      RenderFrameHost* new_host) OVERRIDE;

  
  
  virtual void WebContentsDestroyed() OVERRIDE;

  
  
  virtual void DidShowFullscreenWidget(int routing_id) OVERRIDE;
  virtual void DidDestroyFullscreenWidget(int routing_id) OVERRIDE;

  
  
  const bool track_fullscreen_rwh_;

  
  scoped_refptr<base::MessageLoopProxy> message_loop_;

  
  ChangeCallback callback_;

  
  
  RenderWidgetHost* last_target_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsTracker);
};

}  

#endif  
