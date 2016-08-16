// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_ANDROID_SYNCHRONOUS_COMPOSITOR_CLIENT_H_
#define CONTENT_PUBLIC_BROWSER_ANDROID_SYNCHRONOUS_COMPOSITOR_CLIENT_H_

#include "base/basictypes.h"
#include "ui/gfx/geometry/size_f.h"
#include "ui/gfx/vector2d_f.h"

namespace content {

class SynchronousCompositor;

class SynchronousCompositorClient {
 public:
  
  
  virtual void DidInitializeCompositor(SynchronousCompositor* compositor) = 0;

  
  
  
  
  virtual void DidDestroyCompositor(SynchronousCompositor* compositor) = 0;

  
  virtual gfx::Vector2dF GetTotalRootLayerScrollOffset() = 0;
  virtual void UpdateRootLayerState(const gfx::Vector2dF& total_scroll_offset,
                                    const gfx::Vector2dF& max_scroll_offset,
                                    const gfx::SizeF& scrollable_size,
                                    float page_scale_factor,
                                    float min_page_scale_factor,
                                    float max_page_scale_factor) = 0;
  virtual bool IsExternalFlingActive() const = 0;

  virtual void DidOverscroll(gfx::Vector2dF accumulated_overscroll,
                             gfx::Vector2dF latest_overscroll_delta,
                             gfx::Vector2dF current_fling_velocity) = 0;

  
  
  
  virtual void SetContinuousInvalidate(bool invalidate) = 0;

  virtual void DidUpdateContent() = 0;

 protected:
  SynchronousCompositorClient() {}
  virtual ~SynchronousCompositorClient() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(SynchronousCompositorClient);
};

}  

#endif  
