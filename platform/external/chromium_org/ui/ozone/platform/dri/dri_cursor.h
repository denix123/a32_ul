// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_CURSOR_H_
#define UI_OZONE_PLATFORM_DRI_DRI_CURSOR_H_

#include "base/memory/ref_counted.h"
#include "ui/base/cursor/cursor.h"
#include "ui/events/ozone/evdev/cursor_delegate_evdev.h"
#include "ui/gfx/native_widget_types.h"

namespace gfx {
class PointF;
class Vector2dF;
}

namespace ui {

class BitmapCursorOzone;
class BitmapCursorFactoryOzone;
class DriWindowManager;
class HardwareCursorDelegate;

class DriCursor : public CursorDelegateEvdev {
 public:
  explicit DriCursor(HardwareCursorDelegate* hardware,
                     DriWindowManager* window_manager);
  virtual ~DriCursor();

  void SetCursor(gfx::AcceleratedWidget widget, PlatformCursor platform_cursor);
  void ShowCursor();
  void HideCursor();
  gfx::AcceleratedWidget GetCursorWindow();

  
  virtual void MoveCursorTo(gfx::AcceleratedWidget widget,
                            const gfx::PointF& location) OVERRIDE;
  virtual void MoveCursor(const gfx::Vector2dF& delta) OVERRIDE;
  virtual bool IsCursorVisible() OVERRIDE;
  virtual gfx::PointF location() OVERRIDE;

 private:
  
  gfx::Point bitmap_location();

  
  HardwareCursorDelegate* hardware_;

  DriWindowManager* window_manager_;  

  
  scoped_refptr<BitmapCursorOzone> cursor_;

  
  gfx::AcceleratedWidget cursor_window_;

  
  gfx::PointF cursor_location_;
};

}  

#endif  
