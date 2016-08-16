// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELF_APP_LIST_BUTTON_H_
#define ASH_SHELF_APP_LIST_BUTTON_H_

#include "ui/views/controls/button/image_button.h"

namespace ash {
class ShelfButtonHost;
class ShelfWidget;

class AppListButton : public views::ImageButton {
 public:
  
  static const int kImageBoundsSize;

  AppListButton(views::ButtonListener* listener,
                ShelfButtonHost* host,
                ShelfWidget* shelf_widget);
  virtual ~AppListButton();

  bool draw_background_as_active() {
    return draw_background_as_active_;
  }

 protected:
  
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseCaptureLost() OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseMoved(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseEntered(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseExited(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;

  
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

 private:
  
  void SetDrawBackgroundAsActive(bool draw_background_as_active);

  
  
  bool draw_background_as_active_;

  
  
  bool touch_feedback_enabled_;

  ShelfButtonHost* host_;
  
  
  ShelfWidget* shelf_widget_;

  DISALLOW_COPY_AND_ASSIGN(AppListButton);
};

}  

#endif  
