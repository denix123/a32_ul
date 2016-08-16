// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_NATIVE_CURSOR_MANAGER_H_
#define UI_WM_CORE_NATIVE_CURSOR_MANAGER_H_

#include "base/strings/string16.h"
#include "ui/base/cursor/cursor.h"
#include "ui/wm/core/native_cursor_manager_delegate.h"
#include "ui/wm/wm_export.h"

namespace gfx {
class Display;
}

namespace wm {

class WM_EXPORT NativeCursorManager {
 public:
  virtual ~NativeCursorManager() {}

  
  virtual void SetDisplay(
      const gfx::Display& display,
      NativeCursorManagerDelegate* delegate) = 0;

  
  
  
  virtual void SetCursor(
      gfx::NativeCursor cursor,
      NativeCursorManagerDelegate* delegate) = 0;

  
  
  
  virtual void SetVisibility(
    bool visible,
    NativeCursorManagerDelegate* delegate) = 0;

  
  virtual void SetCursorSet(
      ui::CursorSetType cursor_set,
      NativeCursorManagerDelegate* delegate) = 0;

  
  
  
  virtual void SetMouseEventsEnabled(
      bool enabled,
      NativeCursorManagerDelegate* delegate) = 0;
};

}  

#endif  
