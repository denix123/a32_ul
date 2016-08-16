// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WINDOW_ANIMATIONS_H_
#define ASH_WM_WINDOW_ANIMATIONS_H_

#include "ash/ash_export.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/animation/tween.h"
#include "ui/gfx/transform.h"
#include "ui/wm/core/window_animations.h"

namespace aura {
class Window;
}
namespace ui {
class Layer;
class LayerTreeOwner;
}
namespace views {
}

namespace ash {

enum WindowVisibilityAnimationType {
  
  WINDOW_VISIBILITY_ANIMATION_TYPE_MINIMIZE =
      ::wm::WINDOW_VISIBILITY_ANIMATION_MAX,
  
  WINDOW_VISIBILITY_ANIMATION_TYPE_BRIGHTNESS_GRAYSCALE
};

enum LayerScaleAnimationDirection {
  LAYER_SCALE_ANIMATION_ABOVE,
  LAYER_SCALE_ANIMATION_BELOW,
};

extern const int kCrossFadeDurationMS;

ASH_EXPORT base::TimeDelta CrossFadeAnimation(
    aura::Window* window,
    scoped_ptr<ui::LayerTreeOwner> old_layer_owner,
    gfx::Tween::Type tween_type);

ASH_EXPORT bool AnimateOnChildWindowVisibilityChanged(aura::Window* window,
                                                      bool visible);

ASH_EXPORT std::vector<ui::LayerAnimationSequence*>
CreateBrightnessGrayscaleAnimationSequence(float target_value,
                                           base::TimeDelta duration);

ASH_EXPORT void SetTransformForScaleAnimation(
    ui::Layer* layer,
    LayerScaleAnimationDirection type);

ASH_EXPORT gfx::Rect GetMinimizeAnimationTargetBoundsInScreen(
    aura::Window* window);

}  

#endif  
