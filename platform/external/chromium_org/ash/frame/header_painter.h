// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_HEADER_PAINTER_H_
#define ASH_FRAME_HEADER_PAINTER_H_

#include "ash/ash_export.h"

namespace gfx {
class Canvas;
}

namespace ash {

class ASH_EXPORT HeaderPainter {
 public:
  enum Mode {
    MODE_ACTIVE,
    MODE_INACTIVE
  };

  virtual ~HeaderPainter() {
  }

  
  virtual int GetMinimumHeaderWidth() const = 0;

  
  virtual void PaintHeader(gfx::Canvas* canvas, Mode mode) = 0;

  
  virtual void LayoutHeader() = 0;

  
  
  virtual int GetHeaderHeightForPainting() const = 0;
  virtual void SetHeaderHeightForPainting(int height_for_painting) = 0;

  
  virtual void SchedulePaintForTitle() = 0;

  
  virtual void UpdateLeftViewXInset(int left_view_x_inset) = 0;
};

}  

#endif  
