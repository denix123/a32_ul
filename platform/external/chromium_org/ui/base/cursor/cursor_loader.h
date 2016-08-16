// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_CURSOR_CURSOR_LOADER_H_
#define UI_BASE_CURSOR_CURSOR_LOADER_H_

#include "base/logging.h"
#include "base/strings/string16.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/display.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/point.h"

namespace ui {

class UI_BASE_EXPORT CursorLoader {
 public:
  CursorLoader() : scale_(1.f), rotation_(gfx::Display::ROTATE_0) {}
  virtual ~CursorLoader() {}

  gfx::Display::Rotation rotation() const {
    return rotation_;
  }

  void set_rotation(gfx::Display::Rotation rotation) {
    rotation_ = rotation;
  }

  
  float scale() const {
    return scale_;
  }

  
  void set_scale(const float scale) {
    scale_ = scale;
  }

  
  virtual void LoadImageCursor(int id,
                               int resource_id,
                               const gfx::Point& hot) = 0;

  
  
  
  
  
  virtual void LoadAnimatedCursor(int id,
                                  int resource_id,
                                  const gfx::Point& hot,
                                  int frame_delay_ms) = 0;

  
  virtual void UnloadAll() = 0;

  
  virtual void SetPlatformCursor(gfx::NativeCursor* cursor) = 0;

  
  static CursorLoader* Create();

 private:
  
  float scale_;

  
  gfx::Display::Rotation rotation_;

  DISALLOW_COPY_AND_ASSIGN(CursorLoader);
};

}  

#endif  
