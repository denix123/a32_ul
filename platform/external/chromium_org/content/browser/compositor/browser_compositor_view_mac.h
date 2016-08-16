// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_COMPOSITOR_BROWSER_COMPOSITOR_VIEW_MAC_H_
#define CONTENT_BROWSER_COMPOSITOR_BROWSER_COMPOSITOR_VIEW_MAC_H_

#include <vector>

#include "cc/output/software_frame_data.h"
#include "skia/ext/platform_canvas.h"
#include "ui/compositor/compositor.h"
#include "ui/events/latency_info.h"
#include "ui/gfx/geometry/size.h"

namespace content {

class BrowserCompositorViewMacInternal;

class BrowserCompositorViewMacClient {
 public:
  
  
  virtual bool BrowserCompositorViewShouldAckImmediately() const = 0;

  
  
  virtual void BrowserCompositorViewFrameSwapped(
      const std::vector<ui::LatencyInfo>& latency_info) = 0;

  
  
  virtual NSView* BrowserCompositorSuperview() = 0;

  
  virtual ui::Layer* BrowserCompositorRootLayer() = 0;
};

class BrowserCompositorViewMac {
 public:
  
  
  explicit BrowserCompositorViewMac(BrowserCompositorViewMacClient* client);
  ~BrowserCompositorViewMac();

  
  ui::Compositor* GetCompositor() const;

  
  BrowserCompositorViewMacClient* GetClient() const { return client_; }

  
  bool HasFrameOfSize(const gfx::Size& dip_size) const;

  
  
  
  void BeginPumpingFrames();
  void EndPumpingFrames();

  static void GotAcceleratedFrame(
      gfx::AcceleratedWidget widget,
      uint64 surface_handle, int surface_id,
      const std::vector<ui::LatencyInfo>& latency_info,
      gfx::Size pixel_size, float scale_factor,
      int gpu_host_id, int gpu_route_id);

  static void GotSoftwareFrame(
      gfx::AcceleratedWidget widget,
      cc::SoftwareFrameData* frame_data, float scale_factor, SkCanvas* canvas);

 private:
  BrowserCompositorViewMacClient* client_;
  scoped_ptr<BrowserCompositorViewMacInternal> internal_view_;
};

class BrowserCompositorViewPlaceholderMac {
 public:
  BrowserCompositorViewPlaceholderMac();
  ~BrowserCompositorViewPlaceholderMac();
};

}  

#endif  
