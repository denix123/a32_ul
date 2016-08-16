// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_COMPOSITOR_SURFACE_DISPLAY_OUTPUT_SURFACE_H_
#define CONTENT_BROWSER_COMPOSITOR_SURFACE_DISPLAY_OUTPUT_SURFACE_H_

#include "cc/output/output_surface.h"
#include "cc/surfaces/surface_factory.h"
#include "cc/surfaces/surface_factory_client.h"
#include "cc/surfaces/surface_id_allocator.h"

namespace cc {
class Display;
class SurfaceManager;
}

namespace content {

class SurfaceDisplayOutputSurface : public cc::OutputSurface,
                                    public cc::SurfaceFactoryClient {
 public:
  
  SurfaceDisplayOutputSurface(
      cc::SurfaceManager* surface_manager,
      uint32_t surface_id_namespace,
      const scoped_refptr<cc::ContextProvider>& context_provider);
  virtual ~SurfaceDisplayOutputSurface();

  void set_display(cc::Display* display) { display_ = display; }
  cc::SurfaceFactory* factory() { return &factory_; }
  void ReceivedVSyncParameters(base::TimeTicks timebase,
                               base::TimeDelta interval);

  
  virtual void SwapBuffers(cc::CompositorFrame* frame) OVERRIDE;

  
  virtual void ReturnResources(
      const cc::ReturnedResourceArray& resources) OVERRIDE;

 private:
  void SwapBuffersComplete();

  cc::Display* display_;
  cc::SurfaceManager* surface_manager_;
  cc::SurfaceFactory factory_;
  gfx::Size display_size_;
  cc::SurfaceId surface_id_;
  cc::SurfaceIdAllocator allocator_;

  DISALLOW_COPY_AND_ASSIGN(SurfaceDisplayOutputSurface);
};

}  

#endif  
