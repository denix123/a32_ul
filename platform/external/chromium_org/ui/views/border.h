// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_BORDER_H_
#define UI_VIEWS_BORDER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/insets.h"
#include "ui/views/views_export.h"

namespace gfx{
class Canvas;
class Size;
}

namespace views {

class Painter;
class View;


class VIEWS_EXPORT Border {
 public:
  Border();
  virtual ~Border();

  
  static scoped_ptr<Border> NullBorder();

  
  
  static scoped_ptr<Border> CreateSolidBorder(int thickness, SkColor color);

  
  
  static scoped_ptr<Border> CreateEmptyBorder(int top,
                                              int left,
                                              int bottom,
                                              int right);

  
  
  static scoped_ptr<Border> CreateSolidSidedBorder(int top,
                                                   int left,
                                                   int bottom,
                                                   int right,
                                                   SkColor color);

  
  
  
  static scoped_ptr<Border> CreateBorderPainter(Painter* painter,
                                                const gfx::Insets& insets);

  
  virtual void Paint(const View& view, gfx::Canvas* canvas) = 0;

  
  virtual gfx::Insets GetInsets() const = 0;

  
  
  
  
  
  
  virtual gfx::Size GetMinimumSize() const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Border);
};

}  

#endif  
