// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_RENDER_FRAME_HOST_H_
#define CONTENT_PUBLIC_BROWSER_RENDER_FRAME_HOST_H_

#include <string>

#include "base/callback_forward.h"
#include "content/common/content_export.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"
#include "url/gurl.h"

namespace base {
class Value;
}

namespace content {
class RenderProcessHost;
class RenderViewHost;
class ServiceRegistry;
class SiteInstance;

class CONTENT_EXPORT RenderFrameHost : public IPC::Listener,
                                       public IPC::Sender {
 public:
  
  
  static RenderFrameHost* FromID(int render_process_id, int render_frame_id);

  virtual ~RenderFrameHost() {}

  
  virtual int GetRoutingID() = 0;

  
  
  
  virtual SiteInstance* GetSiteInstance() = 0;

  
  virtual RenderProcessHost* GetProcess() = 0;

  
  
  
  virtual RenderFrameHost* GetParent() = 0;

  
  
  
  
  virtual const std::string& GetFrameName() = 0;

  
  virtual bool IsCrossProcessSubframe() = 0;

  
  virtual GURL GetLastCommittedURL() = 0;

  
  virtual gfx::NativeView GetNativeView() = 0;

  
  
  typedef base::Callback<void(const base::Value*)> JavaScriptResultCallback;
  virtual void ExecuteJavaScript(const base::string16& javascript) = 0;
  virtual void ExecuteJavaScript(const base::string16& javascript,
                                 const JavaScriptResultCallback& callback) = 0;

  
  
  virtual void ExecuteJavaScriptForTests(const base::string16& javascript) = 0;

  
  virtual void AccessibilitySetFocus(int acc_obj_id) = 0;
  virtual void AccessibilityDoDefaultAction(int acc_obj_id) = 0;
  virtual void AccessibilityScrollToMakeVisible(
      int acc_obj_id, const gfx::Rect& subfocus) = 0;
  virtual void AccessibilitySetTextSelection(
      int acc_obj_id, int start_offset, int end_offset) = 0;

  
  virtual RenderViewHost* GetRenderViewHost() = 0;

  
  virtual ServiceRegistry* GetServiceRegistry() = 0;

 private:
  
  friend class RenderFrameHostImpl;
  RenderFrameHost() {}
};

}  

#endif  
