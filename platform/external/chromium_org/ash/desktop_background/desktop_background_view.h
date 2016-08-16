// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DESKTOP_BACKGROUND_DESKTOP_BACKGROUND_VIEW_H_
#define ASH_DESKTOP_BACKGROUND_DESKTOP_BACKGROUND_VIEW_H_

#include "ui/events/event.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/views/context_menu_controller.h"
#include "ui/views/view.h"

namespace ash {

class PreEventDispatchHandler;

class DesktopBackgroundView : public views::View,
                              public views::ContextMenuController {
 public:
  DesktopBackgroundView();
  virtual ~DesktopBackgroundView();

 private:
  
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;

  
  virtual void ShowContextMenuForView(views::View* source,
                                      const gfx::Point& point,
                                      ui::MenuSourceType source_type) OVERRIDE;
  scoped_ptr<PreEventDispatchHandler> pre_dispatch_handler_;

  DISALLOW_COPY_AND_ASSIGN(DesktopBackgroundView);
};

}  

#endif  