// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_FRAME_PROXY_H_
#define CONTENT_RENDERER_RENDER_FRAME_PROXY_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"

#include "third_party/WebKit/public/web/WebRemoteFrame.h"
#include "third_party/WebKit/public/web/WebRemoteFrameClient.h"

struct FrameMsg_BuffersSwapped_Params;
struct FrameMsg_CompositorFrameSwapped_Params;

namespace content {

class ChildFrameCompositingHelper;
class RenderFrameImpl;
class RenderViewImpl;

class CONTENT_EXPORT RenderFrameProxy
    : public IPC::Listener,
      public IPC::Sender,
      NON_EXPORTED_BASE(public blink::WebRemoteFrameClient) {
 public:
  
  
  
  
  
  static RenderFrameProxy* CreateProxyToReplaceFrame(
      RenderFrameImpl* frame_to_replace,
      int routing_id);

  
  
  
  
  
  
  
  
  
  
  
  
  
  static RenderFrameProxy* CreateFrameProxy(int routing_id,
                                            int parent_routing_id,
                                            int render_view_routing_id);

  
  static RenderFrameProxy* FromRoutingID(int routing_id);

  
  static RenderFrameProxy* FromWebFrame(blink::WebFrame* web_frame);

  virtual ~RenderFrameProxy();

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  
  void DidCommitCompositorFrame();

  int routing_id() { return routing_id_; }
  RenderViewImpl* render_view() { return render_view_; }
  blink::WebRemoteFrame* web_frame() { return web_frame_; }

  
  virtual void postMessageEvent(
      blink::WebLocalFrame* sourceFrame,
      blink::WebRemoteFrame* targetFrame,
      blink::WebSecurityOrigin target,
      blink::WebDOMMessageEvent event);
  virtual void initializeChildFrame(
      const blink::WebRect& frame_rect,
      float scale_factor);

 private:
  RenderFrameProxy(int routing_id, int frame_routing_id);

  void Init(blink::WebRemoteFrame* frame, RenderViewImpl* render_view);

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  void OnDeleteProxy();
  void OnChildFrameProcessGone();
  void OnCompositorFrameSwapped(const IPC::Message& message);
  void OnDisownOpener();

  
  const int routing_id_;

  
  
  const int frame_routing_id_;

  
  blink::WebRemoteFrame* web_frame_;
  scoped_refptr<ChildFrameCompositingHelper> compositing_helper_;

  RenderViewImpl* render_view_;

  DISALLOW_COPY_AND_ASSIGN(RenderFrameProxy);
};

}  

#endif  
