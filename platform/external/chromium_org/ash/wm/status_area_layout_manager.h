// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_STATUS_AREA_LAYOUT_MANAGER_H_
#define ASH_WM_STATUS_AREA_LAYOUT_MANAGER_H_

#include "ash/snap_to_pixel_layout_manager.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/aura/layout_manager.h"

namespace ash {
class ShelfWidget;

class StatusAreaLayoutManager : public SnapToPixelLayoutManager {
 public:
  StatusAreaLayoutManager(aura::Window* container, ShelfWidget* shelf);
  virtual ~StatusAreaLayoutManager();

  
  virtual void OnWindowResized() OVERRIDE;
  virtual void SetChildBounds(aura::Window* child,
                              const gfx::Rect& requested_bounds) OVERRIDE;

 private:
  
  
  void LayoutStatusArea();

  
  
  bool in_layout_;

  ShelfWidget* shelf_;

  DISALLOW_COPY_AND_ASSIGN(StatusAreaLayoutManager);
};

}  

#endif  
