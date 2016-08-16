// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_UTIL_DRAG_HANDLE_H_
#define ATHENA_UTIL_DRAG_HANDLE_H_

#include "athena/athena_export.h"

namespace views {
class View;
}

namespace athena {
class DragHandleScrollDelegate {
 public:
  virtual ~DragHandleScrollDelegate() {}

  
  virtual void HandleScrollBegin(float delta) = 0;

  
  virtual void HandleScrollEnd() = 0;

  
  virtual void HandleScrollUpdate(float delta) = 0;
};

enum DragHandleScrollDirection { DRAG_HANDLE_VERTICAL, DRAG_HANDLE_HORIZONTAL };

ATHENA_EXPORT views::View* CreateDragHandleView(
    DragHandleScrollDirection scroll_direction,
    DragHandleScrollDelegate* delegate,
    int preferred_width,
    int preferred_height);

}  

#endif  
