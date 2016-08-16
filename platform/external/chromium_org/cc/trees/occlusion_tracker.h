// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TREES_OCCLUSION_TRACKER_H_
#define CC_TREES_OCCLUSION_TRACKER_H_

#include <vector>

#include "base/basictypes.h"
#include "cc/base/cc_export.h"
#include "cc/base/simple_enclosed_region.h"
#include "cc/layers/layer_iterator.h"
#include "cc/trees/occlusion.h"
#include "ui/gfx/rect.h"

namespace cc {
class LayerImpl;
class Region;
class RenderSurfaceImpl;
class Layer;
class RenderSurface;

template <typename LayerType>
class CC_EXPORT OcclusionTracker {
 public:
  explicit OcclusionTracker(const gfx::Rect& screen_space_clip_rect);
  ~OcclusionTracker();

  
  
  Occlusion GetCurrentOcclusionForLayer(
      const gfx::Transform& draw_transform) const;

  
  
  void EnterLayer(const LayerIteratorPosition<LayerType>& layer_iterator);
  
  
  void LeaveLayer(const LayerIteratorPosition<LayerType>& layer_iterator);

  
  
  
  gfx::Rect UnoccludedContributingSurfaceContentRect(
      const gfx::Rect& content_rect,
      const gfx::Transform& draw_transform) const;

  
  Region ComputeVisibleRegionInScreen() const;

  void set_minimum_tracking_size(const gfx::Size& size) {
    minimum_tracking_size_ = size;
  }

  
  void set_occluding_screen_space_rects_container(
      std::vector<gfx::Rect>* rects) {
    occluding_screen_space_rects_ = rects;
  }
  void set_non_occluding_screen_space_rects_container(
      std::vector<gfx::Rect>* rects) {
    non_occluding_screen_space_rects_ = rects;
  }

 protected:
  struct StackObject {
    StackObject() : target(0) {}
    explicit StackObject(const LayerType* target) : target(target) {}
    const LayerType* target;
    SimpleEnclosedRegion occlusion_from_outside_target;
    SimpleEnclosedRegion occlusion_from_inside_target;
  };

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  std::vector<StackObject> stack_;

 private:
  
  
  void EnterRenderTarget(const LayerType* new_target);

  
  
  
  void FinishedRenderTarget(const LayerType* finished_target);

  
  
  
  
  void LeaveToRenderTarget(const LayerType* new_target);

  
  void MarkOccludedBehindLayer(const LayerType* layer);

  gfx::Rect screen_space_clip_rect_;
  gfx::Size minimum_tracking_size_;

  
  std::vector<gfx::Rect>* occluding_screen_space_rects_;
  std::vector<gfx::Rect>* non_occluding_screen_space_rects_;

  DISALLOW_COPY_AND_ASSIGN(OcclusionTracker);
};

#if !defined(COMPILER_MSVC)
extern template class OcclusionTracker<Layer>;
extern template class OcclusionTracker<LayerImpl>;
#endif

}  

#endif  
