// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_CROSS_PROCESS_FRAME_CONNECTOR_H_
#define CONTENT_BROWSER_FRAME_HOST_CROSS_PROCESS_FRAME_CONNECTOR_H_

#include "cc/output/compositor_frame.h"
#include "ui/gfx/rect.h"

namespace blink {
class WebInputEvent;
}

namespace IPC {
class Message;
}

struct FrameHostMsg_CompositorFrameSwappedACK_Params;
struct FrameHostMsg_ReclaimCompositorResources_Params;

namespace content {
class RenderFrameProxyHost;
class RenderWidgetHostImpl;
class RenderWidgetHostViewChildFrame;

class CrossProcessFrameConnector {
 public:
  
  explicit CrossProcessFrameConnector(
      RenderFrameProxyHost* frame_proxy_in_parent_renderer);
  virtual ~CrossProcessFrameConnector();

  bool OnMessageReceived(const IPC::Message &msg);

  
  
  void set_view(RenderWidgetHostViewChildFrame* view);
  RenderWidgetHostViewChildFrame* get_view_for_testing() { return view_; }

  void RenderProcessGone();

  void ChildFrameCompositorFrameSwapped(uint32 output_surface_id,
                                        int host_id,
                                        int route_id,
                                        scoped_ptr<cc::CompositorFrame> frame);

  gfx::Rect ChildFrameRect();

 private:
  
  void OnCompositorFrameSwappedACK(
      const FrameHostMsg_CompositorFrameSwappedACK_Params& params);
  void OnReclaimCompositorResources(
      const FrameHostMsg_ReclaimCompositorResources_Params& params);
  void OnForwardInputEvent(const blink::WebInputEvent* event);
  void OnInitializeChildFrame(gfx::Rect frame_rect, float scale_factor);

  void SetDeviceScaleFactor(float scale_factor);
  void SetSize(gfx::Rect frame_rect);

  
  
  RenderFrameProxyHost* frame_proxy_in_parent_renderer_;

  
  RenderWidgetHostViewChildFrame* view_;

  gfx::Rect child_frame_rect_;
  float device_scale_factor_;
};

}  

#endif  

