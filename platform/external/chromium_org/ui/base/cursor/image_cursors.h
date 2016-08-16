// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_CURSOR_IMAGE_CURSORS_H_
#define UI_BASE_CURSOR_IMAGE_CURSORS_H_

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "ui/base/cursor/cursor.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/display.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {

class CursorLoader;

class UI_BASE_EXPORT ImageCursors {
 public:
  ImageCursors();
  ~ImageCursors();

  
  float GetScale() const;
  gfx::Display::Rotation GetRotation() const;

  
  
  bool SetDisplay(const gfx::Display& display, float scale_factor);

  
  void SetCursorSet(CursorSetType cursor_set);

  
  void SetPlatformCursor(gfx::NativeCursor* cursor);

 private:
  
  void ReloadCursors();

  scoped_ptr<CursorLoader> cursor_loader_;
  CursorSetType cursor_set_;

  DISALLOW_COPY_AND_ASSIGN(ImageCursors);
};

}  

#endif  
