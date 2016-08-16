// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_COMPOSITOR_BROWSER_COMPOSITOR_VIEW_PRIVATE_MAC_H_
#define CONTENT_BROWSER_COMPOSITOR_BROWSER_COMPOSITOR_VIEW_PRIVATE_MAC_H_

#include <IOSurface/IOSurfaceAPI.h>

#include "base/mac/scoped_nsobject.h"
#include "content/browser/compositor/browser_compositor_view_mac.h"
#include "content/browser/compositor/io_surface_layer_mac.h"
#include "content/browser/compositor/software_layer_mac.h"
#include "ui/base/cocoa/remote_layer_api.h"

namespace content {

class BrowserCompositorViewMacInternal
    : public IOSurfaceLayerClient {
 public:
  BrowserCompositorViewMacInternal();
  virtual ~BrowserCompositorViewMacInternal();
  static BrowserCompositorViewMacInternal* FromAcceleratedWidget(
      gfx::AcceleratedWidget widget);

  void SetClient(BrowserCompositorViewMacClient* client);
  void ResetClient();

  ui::Compositor* compositor() const { return compositor_.get(); }

  
  bool HasFrameOfSize(const gfx::Size& dip_size) const;

  
  int GetRendererID() const;

  
  
  void BeginPumpingFrames();
  void EndPumpingFrames();

  void GotAcceleratedFrame(
      uint64 surface_handle, int output_surface_id,
      const std::vector<ui::LatencyInfo>& latency_info,
      gfx::Size pixel_size, float scale_factor);

  void GotSoftwareFrame(
      cc::SoftwareFrameData* frame_data, float scale_factor, SkCanvas* canvas);

private:
  
  virtual bool IOSurfaceLayerShouldAckImmediately() const OVERRIDE;
  virtual void IOSurfaceLayerDidDrawFrame() OVERRIDE;
  virtual void IOSurfaceLayerHitError() OVERRIDE;

  void GotAcceleratedCAContextFrame(
      CAContextID ca_context_id, gfx::Size pixel_size, float scale_factor);

  void GotAcceleratedIOSurfaceFrame(
      IOSurfaceID io_surface_id, gfx::Size pixel_size, float scale_factor);

  
  
  
  
  void DestroyCAContextLayer(
      base::scoped_nsobject<CALayerHost> ca_context_layer);
  void DestroyIOSurfaceLayer(
      base::scoped_nsobject<IOSurfaceLayer> io_surface_layer);
  void DestroySoftwareLayer();

  
  
  BrowserCompositorViewMacClient* client_;

  
  gfx::AcceleratedWidget native_widget_;

  
  scoped_ptr<ui::Compositor> compositor_;

  
  
  
  
  
  
  
  base::scoped_nsobject<CALayer> flipped_layer_;

  
  base::scoped_nsobject<CALayerHost> ca_context_layer_;

  
  base::scoped_nsobject<IOSurfaceLayer> io_surface_layer_;

  
  base::scoped_nsobject<SoftwareLayer> software_layer_;

  
  
  
  int accelerated_output_surface_id_;
  std::vector<ui::LatencyInfo> accelerated_latency_info_;

  
  gfx::Size last_swap_size_dip_;
};

}  

#endif  
