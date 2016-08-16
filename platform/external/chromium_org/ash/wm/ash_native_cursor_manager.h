// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_ASH_NATIVE_CURSOR_MANAGER_H_
#define ASH_WM_ASH_NATIVE_CURSOR_MANAGER_H_

#include "ash/ash_export.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/point.h"
#include "ui/wm/core/native_cursor_manager.h"
#include "ui/wm/core/native_cursor_manager_delegate.h"

namespace ui {
class ImageCursors;
}

namespace ash {

namespace test {
class CursorManagerTestApi;
}

class ASH_EXPORT AshNativeCursorManager
    : public ::wm::NativeCursorManager {
 public:
  AshNativeCursorManager();
  virtual ~AshNativeCursorManager();

  
  
  
  
  void SetNativeCursorEnabled(bool enabled);

 private:
  friend class test::CursorManagerTestApi;

  
  virtual void SetDisplay(
      const gfx::Display& display,
      ::wm::NativeCursorManagerDelegate* delegate) OVERRIDE;
  virtual void SetCursor(
      gfx::NativeCursor cursor,
      ::wm::NativeCursorManagerDelegate* delegate) OVERRIDE;
  virtual void SetVisibility(
      bool visible,
      ::wm::NativeCursorManagerDelegate* delegate) OVERRIDE;
  virtual void SetCursorSet(
      ui::CursorSetType cursor_set,
      ::wm::NativeCursorManagerDelegate* delegate) OVERRIDE;
  virtual void SetMouseEventsEnabled(
      bool enabled,
      ::wm::NativeCursorManagerDelegate* delegate) OVERRIDE;

  
  gfx::Point disabled_cursor_location_;

  bool native_cursor_enabled_;

  scoped_ptr<ui::ImageCursors> image_cursors_;

  DISALLOW_COPY_AND_ASSIGN(AshNativeCursorManager);
};

}  

#endif  
