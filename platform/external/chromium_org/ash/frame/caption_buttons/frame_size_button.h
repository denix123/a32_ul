// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_CAPTION_BUTTONS_FRAME_SIZE_BUTTON_H_
#define ASH_FRAME_CAPTION_BUTTONS_FRAME_SIZE_BUTTON_H_

#include "ash/ash_export.h"
#include "ash/frame/caption_buttons/frame_caption_button.h"
#include "ash/frame/caption_buttons/frame_size_button_delegate.h"
#include "base/timer/timer.h"

namespace views {
class Widget;
}

namespace ash {
class FrameSizeButtonDelegate;
class PhantomWindowController;

class ASH_EXPORT FrameSizeButton : public FrameCaptionButton {
 public:
  FrameSizeButton(views::ButtonListener* listener,
                  views::Widget* frame,
                  FrameSizeButtonDelegate* delegate);

  virtual ~FrameSizeButton();

  
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseCaptureLost() OVERRIDE;
  virtual void OnMouseMoved(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  void set_delay_to_set_buttons_to_snap_mode(int delay_ms) {
    set_buttons_to_snap_mode_delay_ms_ = delay_ms;
  }

 private:
  enum SnapType {
    SNAP_LEFT,
    SNAP_RIGHT,
    SNAP_NONE
  };

  
  void StartSetButtonsToSnapModeTimer(const ui::LocatedEvent& event);

  
  void AnimateButtonsToSnapMode();

  
  
  void SetButtonsToSnapMode(FrameSizeButtonDelegate::Animate animate);

  
  
  void UpdateSnapType(const ui::LocatedEvent& event);

  
  
  const FrameCaptionButton* GetButtonToHover(
      const gfx::Point& event_location_in_screen) const;

  
  
  bool CommitSnap(const ui::LocatedEvent& event);

  
  
  
  void SetButtonsToNormalMode(FrameSizeButtonDelegate::Animate animate);

  
  views::Widget* frame_;

  
  FrameSizeButtonDelegate* delegate_;

  
  
  gfx::Point set_buttons_to_snap_mode_timer_event_location_;

  
  
  
  int set_buttons_to_snap_mode_delay_ms_;

  base::OneShotTimer<FrameSizeButton> set_buttons_to_snap_mode_timer_;

  
  
  bool in_snap_mode_;

  
  
  
  SnapType snap_type_;

  
  
  
  scoped_ptr<PhantomWindowController> phantom_window_controller_;

  DISALLOW_COPY_AND_ASSIGN(FrameSizeButton);
};

}  

#endif  
