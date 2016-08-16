// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_ANIMATION_SCROLLBAR_ANIMATION_CONTROLLER_THINNING_H_
#define CC_ANIMATION_SCROLLBAR_ANIMATION_CONTROLLER_THINNING_H_

#include "base/memory/scoped_ptr.h"
#include "cc/animation/scrollbar_animation_controller.h"
#include "cc/base/cc_export.h"

namespace cc {
class LayerImpl;

class CC_EXPORT ScrollbarAnimationControllerThinning
    : public ScrollbarAnimationController {
 public:
  static scoped_ptr<ScrollbarAnimationControllerThinning> Create(
      LayerImpl* scroll_layer,
      ScrollbarAnimationControllerClient* client,
      base::TimeDelta delay_before_starting,
      base::TimeDelta duration);

  virtual ~ScrollbarAnimationControllerThinning();

  void set_mouse_move_distance_for_test(float distance) {
    mouse_move_distance_to_trigger_animation_ = distance;
  }
  bool mouse_is_over_scrollbar() const { return mouse_is_over_scrollbar_; }
  bool mouse_is_near_scrollbar() const { return mouse_is_near_scrollbar_; }

  virtual void DidScrollUpdate() OVERRIDE;
  virtual void DidMouseMoveOffScrollbar() OVERRIDE;
  virtual void DidMouseMoveNear(float distance) OVERRIDE;

 protected:
  ScrollbarAnimationControllerThinning(
      LayerImpl* scroll_layer,
      ScrollbarAnimationControllerClient* client,
      base::TimeDelta delay_before_starting,
      base::TimeDelta duration);

  virtual void RunAnimationFrame(float progress) OVERRIDE;

 private:
  
  
  enum AnimationChange {
    NONE,
    INCREASE,
    DECREASE
  };
  float OpacityAtAnimationProgress(float progress);
  float ThumbThicknessScaleAtAnimationProgress(float progress);
  float AdjustScale(float new_value,
                    float current_value,
                    AnimationChange animation_change);
  void ApplyOpacityAndThumbThicknessScale(float opacity,
                                          float thumb_thickness_scale);

  LayerImpl* scroll_layer_;

  bool mouse_is_over_scrollbar_;
  bool mouse_is_near_scrollbar_;
  
  AnimationChange thickness_change_;
  
  AnimationChange opacity_change_;
  
  float mouse_move_distance_to_trigger_animation_;

  DISALLOW_COPY_AND_ASSIGN(ScrollbarAnimationControllerThinning);
};

}  

#endif  
