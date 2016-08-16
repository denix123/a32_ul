// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_RENDER_WIDGET_HOST_H_
#define CONTENT_PUBLIC_BROWSER_RENDER_WIDGET_HOST_H_

#include "base/callback.h"
#include "content/common/content_export.h"
#include "content/public/browser/native_web_keyboard_event.h"
#include "ipc/ipc_channel.h"
#include "ipc/ipc_sender.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "third_party/WebKit/public/web/WebTextDirection.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/size.h"
#include "ui/surface/transport_dib.h"

#if defined(OS_MACOSX)
#include "skia/ext/platform_device.h"
#endif

class SkBitmap;

namespace gfx {
class Rect;
}

namespace blink {
class WebMouseEvent;
struct WebScreenInfo;
}

namespace content {

class RenderProcessHost;
class RenderWidgetHostImpl;
class RenderWidgetHostIterator;
class RenderWidgetHostView;

class CONTENT_EXPORT RenderWidgetHost : public IPC::Sender {
 public:
  
  
  static RenderWidgetHost* FromID(int32 process_id, int32 routing_id);

  
  
  static scoped_ptr<RenderWidgetHostIterator> GetRenderWidgetHosts();

  virtual ~RenderWidgetHost() {}

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void UpdateTextDirection(blink::WebTextDirection direction) = 0;
  virtual void NotifyTextDirection() = 0;

  virtual void Focus() = 0;
  virtual void Blur() = 0;

  
  
  
  
  virtual void SetActive(bool active) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void CopyFromBackingStore(
      const gfx::Rect& src_rect,
      const gfx::Size& accelerated_dst_size,
      const base::Callback<void(bool, const SkBitmap&)>& callback,
      const SkColorType color_type) = 0;
  
  virtual bool CanCopyFromBackingStore() = 0;
#if defined(OS_ANDROID)
  virtual void LockBackingStore() = 0;
  virtual void UnlockBackingStore() = 0;
#endif

  
  
  virtual void ForwardMouseEvent(
      const blink::WebMouseEvent& mouse_event) = 0;
  virtual void ForwardWheelEvent(
      const blink::WebMouseWheelEvent& wheel_event) = 0;
  virtual void ForwardKeyboardEvent(
      const NativeWebKeyboardEvent& key_event) = 0;

  virtual RenderProcessHost* GetProcess() const = 0;

  virtual int GetRoutingID() const = 0;

  
  
  
  
  virtual RenderWidgetHostView* GetView() const = 0;

  
  virtual bool IsLoading() const = 0;

  
  virtual bool IsRenderView() const = 0;

  
  
  virtual void ResizeRectChanged(const gfx::Rect& new_rect) = 0;

  
  
  
  
  
  virtual void RestartHangMonitorTimeout() = 0;

  virtual void SetIgnoreInputEvents(bool ignore_input_events) = 0;

  
  virtual void WasResized() = 0;

  
  

  
  typedef base::Callback<bool(const NativeWebKeyboardEvent&)>
      KeyPressEventCallback;
  virtual void AddKeyPressEventCallback(
      const KeyPressEventCallback& callback) = 0;
  virtual void RemoveKeyPressEventCallback(
      const KeyPressEventCallback& callback) = 0;

  
  typedef base::Callback<bool(const blink::WebMouseEvent&)> MouseEventCallback;
  virtual void AddMouseEventCallback(const MouseEventCallback& callback) = 0;
  virtual void RemoveMouseEventCallback(const MouseEventCallback& callback) = 0;

  
  virtual void GetWebScreenInfo(blink::WebScreenInfo* result) = 0;

  virtual SkColorType PreferredReadbackFormat() = 0;

 protected:
  friend class RenderWidgetHostImpl;

  
  
  
  
  
  virtual RenderWidgetHostImpl* AsRenderWidgetHostImpl() = 0;
};

}  

#endif  
