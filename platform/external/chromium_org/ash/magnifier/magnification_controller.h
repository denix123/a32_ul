// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_MAGNIFIER_MAGNIFICATION_CONTROLLER_H_
#define ASH_MAGNIFIER_MAGNIFICATION_CONTROLLER_H_

#include "ash/ash_export.h"
#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/point.h"
#include "ui/gfx/rect.h"

namespace aura {
class RootWindow;
}

namespace ash {

class ASH_EXPORT MagnificationController {
 public:
  enum ScrollDirection {
    SCROLL_NONE,
    SCROLL_LEFT,
    SCROLL_RIGHT,
    SCROLL_UP,
    SCROLL_DOWN
  };

  virtual ~MagnificationController() {}

  
  
  static MagnificationController* CreateInstance();

  
  virtual void SetEnabled(bool enabled) = 0;

  
  virtual bool IsEnabled() const = 0;

  
  virtual void SetScale(float scale, bool animate) = 0;
  
  virtual float GetScale() const = 0;

  
  virtual void MoveWindow(int x, int y, bool animate) = 0;
  virtual void MoveWindow(const gfx::Point& point, bool animate) = 0;
  
  virtual gfx::Point GetWindowPosition() const = 0;

  virtual void SetScrollDirection(ScrollDirection direction) = 0;

  
  
  
  virtual gfx::Point GetPointOfInterestForTesting() = 0;

 protected:
  MagnificationController() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(MagnificationController);
};

}  

#endif  
