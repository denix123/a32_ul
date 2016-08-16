// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_STREAM_UI_PROXY_H_
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_STREAM_UI_PROXY_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/common/media_stream_request.h"

namespace content {

class RenderFrameHostDelegate;

class CONTENT_EXPORT MediaStreamUIProxy {
 public:
  typedef base::Callback<
      void (const MediaStreamDevices& devices,
            content::MediaStreamRequestResult result)>
        ResponseCallback;

  typedef base::Callback<void(gfx::NativeViewId window_id)> WindowIdCallback;

  static scoped_ptr<MediaStreamUIProxy> Create();
  static scoped_ptr<MediaStreamUIProxy> CreateForTests(
      RenderFrameHostDelegate* render_delegate);

  virtual ~MediaStreamUIProxy();

  
  
  
  
  virtual void RequestAccess(const MediaStreamRequest& request,
                             const ResponseCallback& response_callback);

  
  
  
  
  virtual void CheckAccess(const GURL& security_origin,
                           MediaStreamType type,
                           int render_process_id,
                           int render_frame_id,
                           const base::Callback<void(bool)>& callback);

  
  
  
  
  
  virtual void OnStarted(const base::Closure& stop_callback,
                         const WindowIdCallback& window_id_callback);

  void SetRenderFrameHostDelegateForTests(RenderFrameHostDelegate* delegate);

 protected:
  explicit MediaStreamUIProxy(RenderFrameHostDelegate* test_render_delegate);

 private:
  class Core;
  friend class Core;
  friend class FakeMediaStreamUIProxy;

  void ProcessAccessRequestResponse(
      const MediaStreamDevices& devices,
      content::MediaStreamRequestResult result);
  void ProcessStopRequestFromUI();
  void OnWindowId(const WindowIdCallback& window_id_callback,
                  gfx::NativeViewId* window_id);
  void OnCheckedAccess(const base::Callback<void(bool)>& callback,
                       bool have_access);

  scoped_ptr<Core, content::BrowserThread::DeleteOnUIThread> core_;
  ResponseCallback response_callback_;
  base::Closure stop_callback_;

  base::WeakPtrFactory<MediaStreamUIProxy> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamUIProxy);
};

class CONTENT_EXPORT FakeMediaStreamUIProxy : public MediaStreamUIProxy {
 public:
  explicit FakeMediaStreamUIProxy();
  virtual ~FakeMediaStreamUIProxy();

  void SetAvailableDevices(const MediaStreamDevices& devices);
  void SetMicAccess(bool access);
  void SetCameraAccess(bool access);

  
  virtual void RequestAccess(
      const MediaStreamRequest& request,
      const ResponseCallback& response_callback) OVERRIDE;
  virtual void CheckAccess(const GURL& security_origin,
                           MediaStreamType type,
                           int render_process_id,
                           int render_frame_id,
                           const base::Callback<void(bool)>& callback) OVERRIDE;
  virtual void OnStarted(const base::Closure& stop_callback,
                         const WindowIdCallback& window_id_callback) OVERRIDE;

 private:
  
  MediaStreamDevices devices_;

  
  bool mic_access_;
  bool camera_access_;

  DISALLOW_COPY_AND_ASSIGN(FakeMediaStreamUIProxy);
};

}  

#endif  
