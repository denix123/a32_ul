// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_VIEW_HOST_DELEGATE_VIEW_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_VIEW_HOST_DELEGATE_VIEW_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "content/common/content_export.h"
#include "content/common/drag_event_source_info.h"
#include "third_party/WebKit/public/web/WebDragOperation.h"

class SkBitmap;

namespace gfx {
class ImageSkia;
class Rect;
class Vector2d;
}

namespace ui {
class GestureEvent;
class MouseEvent;
}

namespace content {
class RenderFrameHost;
struct ContextMenuParams;
struct DropData;
struct MenuItem;

class CONTENT_EXPORT RenderViewHostDelegateView {
 public:
  
  
  virtual void ShowContextMenu(RenderFrameHost* render_frame_host,
                               const ContextMenuParams& params) {}

  
  
  
  
  
  virtual void StartDragging(const DropData& drop_data,
                             blink::WebDragOperationsMask allowed_ops,
                             const gfx::ImageSkia& image,
                             const gfx::Vector2d& image_offset,
                             const DragEventSourceInfo& event_info) {}

  
  
  virtual void UpdateDragCursor(blink::WebDragOperation operation) {}

  
  virtual void GotFocus() {}

  
  
  
  virtual void TakeFocus(bool reverse) {}

#if defined(OS_MACOSX) || defined(OS_ANDROID)
  
  
  
  virtual void ShowPopupMenu(RenderFrameHost* render_frame_host,
                             const gfx::Rect& bounds,
                             int item_height,
                             double item_font_size,
                             int selected_item,
                             const std::vector<MenuItem>& items,
                             bool right_aligned,
                             bool allow_multiple_selection) {};

  
  virtual void HidePopupMenu() {};
#endif

#if defined(TOOLKIT_VIEWS) || defined(USE_AURA)
  
  
  
  
  virtual void ShowDisambiguationPopup(
      const gfx::Rect& target_rect,
      const SkBitmap& zoomed_bitmap,
      const base::Callback<void(ui::GestureEvent*)>& gesture_cb,
      const base::Callback<void(ui::MouseEvent*)>& mouse_cb) {}

  
  
  virtual void HideDisambiguationPopup() {}
#endif

 protected:
  virtual ~RenderViewHostDelegateView() {}
};

}  

#endif  
