// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_OVERVIEW_TRANSPARENT_ACTIVATE_WINDOW_BUTTON_H_
#define ASH_WM_OVERVIEW_TRANSPARENT_ACTIVATE_WINDOW_BUTTON_H_

#include "base/macros.h"
#include "ui/views/controls/button/button.h"

namespace ash {

class TransparentActivateWindowButton : public views::ButtonListener {
 public:
  explicit TransparentActivateWindowButton(aura::Window* activate_window);
  virtual ~TransparentActivateWindowButton();

  
  void SetBounds(const gfx::Rect& bounds);

  
  
  void SendFocusAlert() const;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

 private:
  
  scoped_ptr<views::Widget> event_handler_widget_;

  
  aura::Window* activate_window_;

  DISALLOW_COPY_AND_ASSIGN(TransparentActivateWindowButton);
};

}  

#endif  
