// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_HEADER_PAINTER_UTIL_H_
#define ASH_FRAME_HEADER_PAINTER_UTIL_H_

#include "ash/ash_export.h"
#include "base/macros.h"

namespace gfx {
class FontList;
class Rect;
}
namespace views {
class View;
class Widget;
}

namespace ash {

class ASH_EXPORT HeaderPainterUtil {
 public:
  
  static int GetTopCornerRadiusWhenRestored();

  
  
  static int GetDefaultLeftViewXInset();

  
  
  static int GetThemeBackgroundXInset();

  
  
  
  static gfx::Rect GetTitleBounds(const views::View* left_view,
                                  const views::View* right_view,
                                  const gfx::FontList& title_font_list);

  
  
  
  static bool CanAnimateActivation(views::Widget* widget);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(HeaderPainterUtil);
};

}  

#endif  
