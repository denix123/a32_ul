// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_PROXY_HOST_H_
#define CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_PROXY_HOST_H_

#include "base/memory/scoped_ptr.h"
#include "content/browser/frame_host/render_frame_host_impl.h"
#include "content/browser/site_instance_impl.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"

namespace content {

class CrossProcessFrameConnector;
class FrameTreeNode;
class RenderProcessHost;
class RenderFrameHostImpl;
class RenderViewHostImpl;
class RenderWidgetHostView;

class RenderFrameProxyHost
    : public IPC::Listener,
      public IPC::Sender {
 public:
  static RenderFrameProxyHost* FromID(int process_id, int routing_id);

  RenderFrameProxyHost(SiteInstance* site_instance,
                       FrameTreeNode* frame_tree_node);
  virtual ~RenderFrameProxyHost();

  RenderProcessHost* GetProcess() {
    return site_instance_->GetProcess();
  }

  
  
  bool InitRenderFrameProxy();

  int GetRoutingID() {
    return routing_id_;
  }

  SiteInstance* GetSiteInstance() {
    return site_instance_.get();
  }

  FrameTreeNode* frame_tree_node() const { return frame_tree_node_; };

  void SetChildRWHView(RenderWidgetHostView* view);

  
  
  RenderFrameHostImpl* render_frame_host() {
    return render_frame_host_.get();
  }
  RenderViewHostImpl* GetRenderViewHost();

  void TakeFrameHostOwnership(
      scoped_ptr<RenderFrameHostImpl> render_frame_host) {
    render_frame_host_ = render_frame_host.Pass();
  }
  scoped_ptr<RenderFrameHostImpl> PassFrameHostOwnership();

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  CrossProcessFrameConnector* cross_process_frame_connector() {
    return cross_process_frame_connector_.get();
  }

  
  
  void DisownOpener();

 private:
  
  int routing_id_;

  
  scoped_refptr<SiteInstance> site_instance_;

  
  FrameTreeNode* frame_tree_node_;

  
  
  
  
  scoped_ptr<CrossProcessFrameConnector> cross_process_frame_connector_;

  
  
  scoped_ptr<RenderFrameHostImpl> render_frame_host_;

  DISALLOW_COPY_AND_ASSIGN(RenderFrameProxyHost);
};

}  

#endif  
