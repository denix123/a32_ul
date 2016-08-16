// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_WINDOW_ANIMATIONS_H_
#define UI_WM_CORE_WINDOW_ANIMATIONS_H_

#include <vector>

#include "ui/compositor/scoped_layer_animation_settings.h"
#include "ui/wm/wm_export.h"

namespace aura {
class Window;
}
namespace base {
class TimeDelta;
}
namespace gfx {
class Rect;
}
namespace ui {
class ImplicitAnimationObserver;
class Layer;
class LayerAnimationSequence;
}

namespace wm {

enum WindowVisibilityAnimationType {
  WINDOW_VISIBILITY_ANIMATION_TYPE_DEFAULT = 0,     
                                                    
                                                    
  WINDOW_VISIBILITY_ANIMATION_TYPE_DROP,            
  WINDOW_VISIBILITY_ANIMATION_TYPE_VERTICAL,        
  WINDOW_VISIBILITY_ANIMATION_TYPE_FADE,            
  WINDOW_VISIBILITY_ANIMATION_TYPE_ROTATE,          

  
  WINDOW_VISIBILITY_ANIMATION_MAX
};

enum WindowAnimationType {
  WINDOW_ANIMATION_TYPE_BOUNCE = 0,  
};

enum WindowVisibilityAnimationTransition {
  ANIMATE_SHOW = 0x1,
  ANIMATE_HIDE = 0x2,
  ANIMATE_BOTH = ANIMATE_SHOW | ANIMATE_HIDE,
  ANIMATE_NONE = 0x4,
};

WM_EXPORT void SetWindowVisibilityAnimationType(aura::Window* window, int type);
WM_EXPORT int GetWindowVisibilityAnimationType(aura::Window* window);

WM_EXPORT void SetWindowVisibilityAnimationTransition(
    aura::Window* window,
    WindowVisibilityAnimationTransition transition);

WM_EXPORT bool HasWindowVisibilityAnimationTransition(
    aura::Window* window,
    WindowVisibilityAnimationTransition transition);

WM_EXPORT void SetWindowVisibilityAnimationDuration(
    aura::Window* window,
    const base::TimeDelta& duration);

WM_EXPORT base::TimeDelta GetWindowVisibilityAnimationDuration(
    const aura::Window& window);

WM_EXPORT void SetWindowVisibilityAnimationVerticalPosition(
    aura::Window* window,
    float position);

class ImplicitHidingWindowAnimationObserver;
class WM_EXPORT ScopedHidingAnimationSettings {
 public:
  explicit ScopedHidingAnimationSettings(aura::Window* window);
  ~ScopedHidingAnimationSettings();

  
  ui::ScopedLayerAnimationSettings* layer_animation_settings() {
    return &layer_animation_settings_;
  }

 private:
  ui::ScopedLayerAnimationSettings layer_animation_settings_;
  ImplicitHidingWindowAnimationObserver* observer_;

  DISALLOW_COPY_AND_ASSIGN(ScopedHidingAnimationSettings);
};

WM_EXPORT bool AnimateOnChildWindowVisibilityChanged(aura::Window* window,
                                                     bool visible);
WM_EXPORT bool AnimateWindow(aura::Window* window, WindowAnimationType type);

WM_EXPORT bool WindowAnimationsDisabled(aura::Window* window);

}  

#endif  
