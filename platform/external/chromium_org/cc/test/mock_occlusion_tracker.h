// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TEST_MOCK_OCCLUSION_TRACKER_H_
#define CC_TEST_MOCK_OCCLUSION_TRACKER_H_

#include "cc/trees/occlusion_tracker.h"

namespace cc {

template <typename LayerType>
class MockOcclusionTracker : public OcclusionTracker<LayerType> {
  
  
  
  
 public:
  MockOcclusionTracker()
      : OcclusionTracker<LayerType>(gfx::Rect(0, 0, 1000, 1000)) {
    typename OcclusionTracker<LayerType>::StackObject stack_obj;
    OcclusionTracker<LayerType>::stack_.push_back(stack_obj);
    OcclusionTracker<LayerType>::stack_.push_back(stack_obj);
  }

  explicit MockOcclusionTracker(const gfx::Rect& screen_scissor_rect)
      : OcclusionTracker<LayerType>(screen_scissor_rect) {
    typename OcclusionTracker<LayerType>::StackObject stack_obj;
    OcclusionTracker<LayerType>::stack_.push_back(stack_obj);
    OcclusionTracker<LayerType>::stack_.push_back(stack_obj);
  }

  void set_occluded_target_rect(const gfx::Rect& occluded) {
    OcclusionTracker<LayerType>::stack_.back().occlusion_from_inside_target =
        occluded;
  }

  void set_occluded_target_rect_for_contributing_surface(
      const gfx::Rect& occluded) {
    OcclusionTracker<
        LayerType>::stack_[OcclusionTracker<LayerType>::stack_.size() - 2]
        .occlusion_from_inside_target = occluded;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(MockOcclusionTracker);
};

}  

#endif  
