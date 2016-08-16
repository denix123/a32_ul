// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_IMAGE_TRANSPORT_SURFACE_CALAYER_MAC_H_
#define CONTENT_COMMON_GPU_IMAGE_TRANSPORT_SURFACE_CALAYER_MAC_H_

#include "base/mac/scoped_nsobject.h"
#include "content/common/gpu/image_transport_surface_fbo_mac.h"
#include "ui/base/cocoa/remote_layer_api.h"
#include "ui/gl/gl_bindings.h"
#include "ui/gl/scoped_cgl.h"

@class ImageTransportLayer;

namespace content {

class CALayerStorageProvider
    : public ImageTransportSurfaceFBO::StorageProvider {
 public:
  CALayerStorageProvider(ImageTransportSurfaceFBO* transport_surface);
  virtual ~CALayerStorageProvider();

  
  virtual gfx::Size GetRoundedSize(gfx::Size size) OVERRIDE;
  virtual bool AllocateColorBufferStorage(
      CGLContextObj context, GLuint texture,
      gfx::Size pixel_size, float scale_factor) OVERRIDE;
  virtual void FreeColorBufferStorage() OVERRIDE;
  virtual void SwapBuffers(const gfx::Size& size, float scale_factor) OVERRIDE;
  virtual void WillWriteToBackbuffer() OVERRIDE;
  virtual void DiscardBackbuffer() OVERRIDE;
  virtual void SwapBuffersAckedByBrowser() OVERRIDE;

  
  CGLContextObj LayerShareGroupContext();
  bool LayerCanDraw();
  void LayerDoDraw();
  void LayerResetStorageProvider();

 private:
  void DrawWithVsyncDisabled();
  void SendPendingSwapToBrowserAfterFrameDrawn();

  ImageTransportSurfaceFBO* transport_surface_;

  
  
  const bool gpu_vsync_disabled_;

  
  bool has_pending_draw_;

  
  
  
  uint32 can_draw_returned_false_count_;

  
  
  base::ScopedTypeRef<CGLContextObj> share_group_context_;
  GLuint fbo_texture_;
  gfx::Size fbo_pixel_size_;
  float fbo_scale_factor_;

  
  base::scoped_nsobject<CAContext> context_;
  base::scoped_nsobject<ImageTransportLayer> layer_;

  base::WeakPtrFactory<CALayerStorageProvider> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(CALayerStorageProvider);
};

}  

#endif  
