// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_WEB_CONTENTS_AURA_WINDOW_SLIDER_H_
#define CONTENT_BROWSER_WEB_CONTENTS_AURA_WINDOW_SLIDER_H_

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/common/content_export.h"
#include "ui/aura/window_observer.h"
#include "ui/compositor/layer_animator.h"
#include "ui/events/event_handler.h"

namespace ui {
class Layer;
}

namespace content {

class ShadowLayerDelegate;

class CONTENT_EXPORT WindowSlider : public ui::EventHandler,
                                    public aura::WindowObserver {
 public:
  class CONTENT_EXPORT Delegate {
   public:
    virtual ~Delegate() {}

    
    
    
    virtual ui::Layer* CreateBackLayer() = 0;

    
    
    
    virtual ui::Layer* CreateFrontLayer() = 0;

    
    
    virtual void OnWindowSlideAborted() = 0;

    
    
    
    
    
    
    virtual void OnWindowSlideCompleting() = 0;

    
    
    
    
    virtual void OnWindowSlideCompleted(scoped_ptr<ui::Layer> layer) = 0;

    
    virtual void OnWindowSliderDestroyed() = 0;
  };

  
  
  
  
  
  WindowSlider(Delegate* delegate,
               aura::Window* event_window,
               aura::Window* owner);

  virtual ~WindowSlider();

  
  void ChangeOwner(aura::Window* new_owner);

  bool IsSlideInProgress() const;

 private:
  
  
  void SetupSliderLayer();

  void UpdateForScroll(float x_offset, float y_offset);

  
  
  void CompleteOrResetSlide();

  
  
  
  void CompleteActiveAnimations();

  
  
  void ResetSlide();

  
  void SlideAnimationCompleted(scoped_ptr<ui::Layer> layer,
                               scoped_ptr<ShadowLayerDelegate> shadow);

  void ResetSlideAnimationCompleted(scoped_ptr<ui::Layer> layer,
                                    scoped_ptr<ShadowLayerDelegate> shadow);

  
  virtual void OnKeyEvent(ui::KeyEvent* event) OVERRIDE;
  virtual void OnMouseEvent(ui::MouseEvent* event) OVERRIDE;
  virtual void OnScrollEvent(ui::ScrollEvent* event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  
  virtual void OnWindowRemovingFromRootWindow(aura::Window* window,
                                              aura::Window* new_root) OVERRIDE;

  Delegate* delegate_;

  
  
  
  aura::Window* event_window_;

  
  
  
  
  aura::Window* owner_;

  
  
  ui::LayerAnimator* active_animator_;

  
  float delta_x_;

  
  scoped_ptr<ui::Layer> slider_;

  
  scoped_ptr<ShadowLayerDelegate> shadow_;

  float active_start_threshold_;

  const float start_threshold_touchscreen_;
  const float start_threshold_touchpad_;
  const float complete_threshold_;

  base::WeakPtrFactory<WindowSlider> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(WindowSlider);
};

}  

#endif  