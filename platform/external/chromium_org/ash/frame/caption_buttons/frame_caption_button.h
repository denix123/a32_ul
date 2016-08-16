// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_CAPTION_BUTTONS_FRAME_CAPTION_BUTTON_H_
#define ASH_FRAME_CAPTION_BUTTONS_FRAME_CAPTION_BUTTON_H_

#include "ash/ash_export.h"
#include "ash/frame/caption_buttons/caption_button_types.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/views/controls/button/custom_button.h"

namespace gfx {
class SlideAnimation;
}

namespace ash {

class ASH_EXPORT FrameCaptionButton : public views::CustomButton {
 public:
  enum Animate {
    ANIMATE_YES,
    ANIMATE_NO
  };

  static const char kViewClassName[];

  FrameCaptionButton(views::ButtonListener* listener, CaptionButtonIcon icon);
  virtual ~FrameCaptionButton();

  
  
  
  
  void SetImages(CaptionButtonIcon icon,
                 Animate animate,
                 int icon_image_id,
                 int inactive_icon_image_id,
                 int hovered_background_image_id,
                 int pressed_background_image_id);

  
  
  bool IsAnimatingImageSwap() const;

  
  void SetAlpha(int alpha);

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  void set_paint_as_active(bool paint_as_active) {
    paint_as_active_ = paint_as_active;
  }

  CaptionButtonIcon icon() const {
    return icon_;
  }

 protected:
  
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

 private:
  
  const gfx::ImageSkia& GetIconImageToPaint() const;

  
  void PaintCentered(gfx::Canvas* canvas,
                     const gfx::ImageSkia& to_center,
                     int alpha);

  
  CaptionButtonIcon icon_;

  
  bool paint_as_active_;

  
  int alpha_;

  
  int icon_image_id_;
  int inactive_icon_image_id_;
  int hovered_background_image_id_;
  int pressed_background_image_id_;
  gfx::ImageSkia icon_image_;
  gfx::ImageSkia inactive_icon_image_;
  gfx::ImageSkia hovered_background_image_;
  gfx::ImageSkia pressed_background_image_;

  
  gfx::ImageSkia crossfade_icon_image_;

  
  
  scoped_ptr<gfx::SlideAnimation> swap_images_animation_;

  DISALLOW_COPY_AND_ASSIGN(FrameCaptionButton);
};

}  

#endif  
