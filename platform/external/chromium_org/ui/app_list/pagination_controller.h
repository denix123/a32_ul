// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_PAGINATION_CONTROLLER_H_
#define UI_APP_LIST_PAGINATION_CONTROLLER_H_

#include "ui/app_list/app_list_export.h"

namespace gfx {
class Vector2d;
class Rect;
}

namespace ui {
class GestureEvent;
}

namespace app_list {

class PaginationModel;

class APP_LIST_EXPORT PaginationController {
 public:
  enum ScrollAxis { SCROLL_AXIS_HORIZONTAL, SCROLL_AXIS_VERTICAL };

  
  
  
  PaginationController(PaginationModel* model, ScrollAxis scroll_axis);

  ScrollAxis scroll_axis() const { return scroll_axis_; }

  
  
  
  bool OnScroll(const gfx::Vector2d& offset);

  
  
  bool OnGestureEvent(const ui::GestureEvent& event, const gfx::Rect& bounds);

 private:
  PaginationModel* pagination_model_;  
  ScrollAxis scroll_axis_;
};

}  

#endif  
