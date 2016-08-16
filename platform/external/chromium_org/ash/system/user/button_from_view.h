// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_USER_BUTTON_FROM_VIEW_H_
#define ASH_SYSTEM_USER_BUTTON_FROM_VIEW_H_

#include "base/macros.h"
#include "ui/gfx/insets.h"
#include "ui/views/controls/button/custom_button.h"

namespace ash {
namespace tray {

class ButtonFromView : public views::CustomButton {
 public:
  
  
  
  
  
  
  ButtonFromView(views::View* content,
                 views::ButtonListener* listener,
                 bool highlight_on_hover,
                 const gfx::Insets& tab_frame_inset);
  virtual ~ButtonFromView();

  
  void ForceBorderVisible(bool show);

  
  virtual void OnMouseEntered(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseExited(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;

  
  bool is_hovered_for_test() { return button_hovered_; }

 private:
  
  void ShowActive();

  
  views::View* content_;

  
  bool highlight_on_hover_;

  
  bool button_hovered_;

  
  bool show_border_;

  
  gfx::Insets tab_frame_inset_;

  DISALLOW_COPY_AND_ASSIGN(ButtonFromView);
};

}  
}  

#endif  
