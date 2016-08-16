// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_RESIZE_HANDLE_WINDOW_TARGETER_H_
#define ASH_WM_RESIZE_HANDLE_WINDOW_TARGETER_H_

#include "ash/wm/window_state_observer.h"
#include "ui/aura/window_observer.h"
#include "ui/aura/window_targeter.h"
#include "ui/gfx/geometry/insets.h"

namespace ash {

class ImmersiveFullscreenController;

class ResizeHandleWindowTargeter : public wm::WindowStateObserver,
                                   public aura::WindowObserver,
                                   public aura::WindowTargeter {
 public:
  ResizeHandleWindowTargeter(aura::Window* window,
                             ImmersiveFullscreenController* immersive);
  virtual ~ResizeHandleWindowTargeter();

 private:
  
  virtual void OnPostWindowStateTypeChange(
      wm::WindowState* window_state,
      wm::WindowStateType old_type) OVERRIDE;
  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

  
  virtual ui::EventTarget* FindTargetForLocatedEvent(
      ui::EventTarget* root,
      ui::LocatedEvent* event) OVERRIDE;
  virtual bool SubtreeShouldBeExploredForEvent(
      ui::EventTarget* target,
      const ui::LocatedEvent& event) OVERRIDE;

  
  
  aura::Window* window_;
  gfx::Insets frame_border_inset_;
  ImmersiveFullscreenController* immersive_controller_;

  DISALLOW_COPY_AND_ASSIGN(ResizeHandleWindowTargeter);
};

}  

#endif  
