// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_RENDER_FRAME_H_
#define CONTENT_PUBLIC_RENDERER_RENDER_FRAME_H_

#include "base/strings/string16.h"
#include "content/common/content_export.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "third_party/WebKit/public/web/WebNavigationPolicy.h"

namespace blink {
class WebFrame;
class WebLocalFrame;
class WebNode;
class WebPlugin;
class WebURLRequest;
class WebURLResponse;
struct WebPluginParams;
}

namespace content {
class ContextMenuClient;
class RenderView;
class ServiceRegistry;
struct ContextMenuParams;
struct WebPluginInfo;
struct WebPreferences;

class CONTENT_EXPORT RenderFrame : public IPC::Listener,
                                   public IPC::Sender {
 public:
  
  static RenderFrame* FromWebFrame(blink::WebFrame* web_frame);

  
  virtual RenderView* GetRenderView() = 0;

  
  virtual int GetRoutingID() = 0;

  
  virtual blink::WebLocalFrame* GetWebFrame() = 0;

   
  virtual WebPreferences& GetWebkitPreferences() = 0;

  
  
  
  
  
  
  
  
  
  
  
  virtual int ShowContextMenu(ContextMenuClient* client,
                              const ContextMenuParams& params) = 0;

  
  
  virtual void CancelContextMenu(int request_id) = 0;

  
  virtual blink::WebNode GetContextMenuNode() const = 0;

  
  
  virtual blink::WebPlugin* CreatePlugin(
      blink::WebFrame* frame,
      const WebPluginInfo& info,
      const blink::WebPluginParams& params) = 0;

  
  virtual void LoadURLExternally(blink::WebLocalFrame* frame,
                                 const blink::WebURLRequest& request,
                                 blink::WebNavigationPolicy policy) = 0;

  
  virtual void ExecuteJavaScript(const base::string16& javascript) = 0;

  
  virtual bool IsHidden() = 0;

  
  virtual ServiceRegistry* GetServiceRegistry() = 0;

  
  virtual bool IsFTPDirectoryListing() = 0;

  
  
  virtual void AttachGuest(int element_instance_id) = 0;

 protected:
  virtual ~RenderFrame() {}

 private:
  
  friend class RenderFrameImpl;
  RenderFrame() {}
};

}  

#endif  
