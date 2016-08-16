// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_CAPTION_BUTTONS_FRAME_SIZE_BUTTON_DELEGATE_H_
#define ASH_FRAME_CAPTION_BUTTONS_FRAME_SIZE_BUTTON_DELEGATE_H_

#include "ash/ash_export.h"
#include "ash/frame/caption_buttons/caption_button_types.h"

namespace gfx {
class Insets;
class Point;
class Vector2d;
}

namespace ash {
class FrameCaptionButton;

class ASH_EXPORT FrameSizeButtonDelegate {
 public:
  enum Animate {
    ANIMATE_YES,
    ANIMATE_NO
  };

  
  virtual bool IsMinimizeButtonVisible() const = 0;

  
  
  
  virtual void SetButtonsToNormal(Animate animate) = 0;

  
  
  virtual void SetButtonIcons(CaptionButtonIcon minimize_button_icon,
                              CaptionButtonIcon close_button_icon,
                              Animate animate) = 0;

  
  virtual const FrameCaptionButton* GetButtonClosestTo(
      const gfx::Point& position_in_screen) const = 0;

  
  
  virtual void SetHoveredAndPressedButtons(
      const FrameCaptionButton* to_hover,
      const FrameCaptionButton* to_press) = 0;

 protected:
  virtual ~FrameSizeButtonDelegate() {}
};

}  

#endif  
