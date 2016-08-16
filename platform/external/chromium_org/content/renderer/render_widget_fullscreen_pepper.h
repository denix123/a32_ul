// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_WIDGET_FULLSCREEN_PEPPER_H_
#define CONTENT_RENDERER_RENDER_WIDGET_FULLSCREEN_PEPPER_H_

#include "base/memory/scoped_ptr.h"
#include "content/renderer/mouse_lock_dispatcher.h"
#include "content/renderer/pepper/fullscreen_container.h"
#include "content/renderer/render_widget_fullscreen.h"
#include "third_party/WebKit/public/web/WebWidget.h"

namespace blink {
class WebLayer;
}

namespace content {
class PepperPluginInstanceImpl;

class RenderWidgetFullscreenPepper : public RenderWidgetFullscreen,
                                     public FullscreenContainer {
 public:
  static RenderWidgetFullscreenPepper* Create(
      int32 opener_id,
      PepperPluginInstanceImpl* plugin,
      const GURL& active_url,
      const blink::WebScreenInfo& screen_info);

  
  virtual void Invalidate() OVERRIDE;
  virtual void InvalidateRect(const blink::WebRect& rect) OVERRIDE;
  virtual void ScrollRect(int dx, int dy, const blink::WebRect& rect) OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual void DidChangeCursor(const blink::WebCursorInfo& cursor) OVERRIDE;
  virtual void SetLayer(blink::WebLayer* layer) OVERRIDE;

  
  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  PepperPluginInstanceImpl* plugin() const { return plugin_; }

  MouseLockDispatcher* mouse_lock_dispatcher() const {
    return mouse_lock_dispatcher_.get();
  }

 protected:
  RenderWidgetFullscreenPepper(PepperPluginInstanceImpl* plugin,
                               const GURL& active_url,
                               const blink::WebScreenInfo& screen_info);
  virtual ~RenderWidgetFullscreenPepper();

  
  virtual void DidInitiatePaint() OVERRIDE;
  virtual void DidFlushPaint() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual void OnResize(const ViewMsg_Resize_Params& params) OVERRIDE;

  
  virtual blink::WebWidget* CreateWebWidget() OVERRIDE;

  
  virtual GURL GetURLForGraphicsContext3D() OVERRIDE;
  virtual void SetDeviceScaleFactor(float device_scale_factor) OVERRIDE;

 private:
  
  GURL active_url_;

  
  PepperPluginInstanceImpl* plugin_;

  blink::WebLayer* layer_;

  scoped_ptr<MouseLockDispatcher> mouse_lock_dispatcher_;

  DISALLOW_COPY_AND_ASSIGN(RenderWidgetFullscreenPepper);
};

}  

#endif  