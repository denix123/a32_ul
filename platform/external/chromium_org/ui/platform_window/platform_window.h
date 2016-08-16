// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_PLATFORM_WINDOW_PLATFORM_WINDOW_H_
#define UI_PLATFORM_WINDOW_PLATFORM_WINDOW_H_

#include "base/memory/scoped_ptr.h"
#include "ui/base/cursor/cursor.h"

namespace gfx {
class Rect;
}

namespace ui {

class PlatformWindowDelegate;

class PlatformWindow {
 public:
  virtual ~PlatformWindow() {}

  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void Close() = 0;

  
  
  virtual void SetBounds(const gfx::Rect& bounds) = 0;
  virtual gfx::Rect GetBounds() = 0;

  virtual void SetCapture() = 0;
  virtual void ReleaseCapture() = 0;

  virtual void ToggleFullscreen() = 0;
  virtual void Maximize() = 0;
  virtual void Minimize() = 0;
  virtual void Restore() = 0;

  virtual void SetCursor(PlatformCursor cursor) = 0;
  virtual void MoveCursorTo(const gfx::Point& location) = 0;
};

}  

#endif  