// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_ACCESSIBILITY_RENDERER_ACCESSIBILITY_COMPLETE_H_
#define CONTENT_RENDERER_ACCESSIBILITY_RENDERER_ACCESSIBILITY_COMPLETE_H_

#include <set>
#include <vector>

#include "base/containers/hash_tables.h"
#include "base/memory/weak_ptr.h"
#include "content/public/renderer/render_view_observer.h"
#include "content/renderer/accessibility/blink_ax_tree_source.h"
#include "content/renderer/accessibility/renderer_accessibility.h"
#include "third_party/WebKit/public/web/WebAXEnums.h"
#include "third_party/WebKit/public/web/WebAXObject.h"
#include "ui/accessibility/ax_node_data.h"
#include "ui/accessibility/ax_tree_serializer.h"

namespace blink {
class WebDocument;
class WebNode;
};

namespace content {
class RenderViewImpl;

class CONTENT_EXPORT RendererAccessibilityComplete
    : public RendererAccessibility {
 public:
  explicit RendererAccessibilityComplete(RenderFrameImpl* render_frame);
  virtual ~RendererAccessibilityComplete();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void HandleWebAccessibilityEvent(
      const blink::WebAXObject& obj, blink::WebAXEvent event) OVERRIDE;
  virtual RendererAccessibilityType GetType() OVERRIDE;
  virtual void FocusedNodeChanged(const blink::WebNode& node) OVERRIDE;

  void HandleAXEvent(const blink::WebAXObject& obj, ui::AXEvent event);

 protected:
  
  void SendPendingAccessibilityEvents();

  
  
  
  void SendLocationChanges();

 private:
  
  void OnDoDefaultAction(int acc_obj_id);
  void OnEventsAck();
  void OnChangeScrollPosition(int acc_obj_id, int scroll_x, int scroll_y);
  void OnScrollToMakeVisible(int acc_obj_id, gfx::Rect subfocus);
  void OnScrollToPoint(int acc_obj_id, gfx::Point point);
  void OnSetFocus(int acc_obj_id);
  void OnSetTextSelection(int acc_obj_id, int start_offset, int end_offset);
  void OnHitTest(gfx::Point point);
  void OnReset(int reset_token);
  void OnFatalError();

  
  
  std::vector<AccessibilityHostMsg_EventParams> pending_events_;

  
  BlinkAXTreeSource tree_source_;

  
  ui::AXTreeSerializer<blink::WebAXObject> serializer_;

  
  base::hash_map<int, gfx::Rect> locations_;

  
  
  
  gfx::Size last_scroll_offset_;

  
  bool ack_pending_;

  
  
  int reset_token_;

  
  base::WeakPtrFactory<RendererAccessibilityComplete> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RendererAccessibilityComplete);
};

#endif  

}  
