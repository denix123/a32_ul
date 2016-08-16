// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_PANELS_ATTACHED_PANEL_WINDOW_TARGETER_H_
#define ASH_WM_PANELS_ATTACHED_PANEL_WINDOW_TARGETER_H_

#include "ash/shell_observer.h"
#include "ui/wm/core/easy_resize_window_targeter.h"

namespace ash {

class PanelLayoutManager;

class AttachedPanelWindowTargeter : public ::wm::EasyResizeWindowTargeter,
                                    public ShellObserver {
 public:
  AttachedPanelWindowTargeter(aura::Window* container,
                              const gfx::Insets& default_mouse_extend,
                              const gfx::Insets& default_touch_extend,
                              PanelLayoutManager* panel_layout_manager);
  virtual ~AttachedPanelWindowTargeter();

  
  virtual void OnShelfCreatedForRootWindow(aura::Window* root_window) OVERRIDE;
  virtual void OnShelfAlignmentChanged(aura::Window* root_window) OVERRIDE;

 private:
  void UpdateTouchExtend(aura::Window* root_window);

  aura::Window* panel_container_;
  PanelLayoutManager* panel_layout_manager_;
  gfx::Insets default_touch_extend_;

  DISALLOW_COPY_AND_ASSIGN(AttachedPanelWindowTargeter);
};

}  

#endif  
