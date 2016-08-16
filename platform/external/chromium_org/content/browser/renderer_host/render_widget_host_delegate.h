// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDER_WIDGET_HOST_DELEGATE_H_
#define CONTENT_BROWSER_RENDER_WIDGET_HOST_DELEGATE_H_

#include "base/basictypes.h"
#include "build/build_config.h"
#include "content/common/content_export.h"
#include "ui/gfx/native_widget_types.h"

namespace blink {
class WebMouseWheelEvent;
class WebGestureEvent;
}

namespace content {

class BrowserAccessibilityManager;
class RenderWidgetHostImpl;
struct NativeWebKeyboardEvent;

class CONTENT_EXPORT RenderWidgetHostDelegate {
 public:
  
  virtual void RenderWidgetDeleted(RenderWidgetHostImpl* render_widget_host) {}

  
  
  
  
  
  virtual bool PreHandleKeyboardEvent(const NativeWebKeyboardEvent& event,
                                      bool* is_keyboard_shortcut);

  
  
  
  virtual void HandleKeyboardEvent(const NativeWebKeyboardEvent& event) {}

  
  
  
  virtual bool HandleWheelEvent(const blink::WebMouseWheelEvent& event);

  
  
  
  virtual bool PreHandleGestureEvent(const blink::WebGestureEvent& event);

  
  
  virtual bool HandleGestureEvent(const blink::WebGestureEvent& event);

  
  virtual void DidSendScreenRects(RenderWidgetHostImpl* rwh) {}

  
  virtual BrowserAccessibilityManager* GetRootBrowserAccessibilityManager();

  
  
  virtual BrowserAccessibilityManager*
      GetOrCreateRootBrowserAccessibilityManager();

#if defined(OS_WIN)
  virtual gfx::NativeViewAccessible GetParentNativeViewAccessible();
#endif

 protected:
  virtual ~RenderWidgetHostDelegate() {}
};

}  

#endif  
