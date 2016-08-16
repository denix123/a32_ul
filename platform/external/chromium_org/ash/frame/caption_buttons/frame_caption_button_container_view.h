// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_CAPTION_BUTTONS_FRAME_CAPTION_BUTTON_CONTAINER_VIEW_H_
#define ASH_FRAME_CAPTION_BUTTONS_FRAME_CAPTION_BUTTON_CONTAINER_VIEW_H_

#include <map>

#include "ash/ash_export.h"
#include "ash/frame/caption_buttons/frame_size_button_delegate.h"
#include "ui/gfx/animation/animation_delegate.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/view.h"

namespace gfx {
class SlideAnimation;
}

namespace views {
class Widget;
}

namespace ash {

class ASH_EXPORT FrameCaptionButtonContainerView
    : public views::View,
      public views::ButtonListener,
      public FrameSizeButtonDelegate,
      public gfx::AnimationDelegate {
 public:
  static const char kViewClassName[];

  
  
  enum MinimizeAllowed {
    MINIMIZE_ALLOWED,
    MINIMIZE_DISALLOWED
  };

  
  
  
  FrameCaptionButtonContainerView(views::Widget* frame,
                                  MinimizeAllowed minimize_allowed);
  virtual ~FrameCaptionButtonContainerView();

  
  class ASH_EXPORT TestApi {
   public:
    explicit TestApi(FrameCaptionButtonContainerView* container_view)
        : container_view_(container_view) {
    }

    void EndAnimations();

    FrameCaptionButton* minimize_button() const {
      return container_view_->minimize_button_;
    }

    FrameCaptionButton* size_button() const {
      return container_view_->size_button_;
    }

    FrameCaptionButton* close_button() const {
      return container_view_->close_button_;
    }

   private:
    FrameCaptionButtonContainerView* container_view_;

    DISALLOW_COPY_AND_ASSIGN(TestApi);
  };

  
  
  
  void SetButtonImages(CaptionButtonIcon icon,
                       int icon_image_id,
                       int inactive_icon_image_id,
                       int hovered_background_image_id,
                       int pressed_background_image_id);

  
  
  void SetPaintAsActive(bool paint_as_active);

  
  void ResetWindowControls();

  
  
  
  int NonClientHitTest(const gfx::Point& point) const;

  
  
  
  void UpdateSizeButtonVisibility();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;

  
  virtual void AnimationEnded(const gfx::Animation* animation) OVERRIDE;
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;

 private:
  friend class FrameCaptionButtonContainerViewTest;

  struct ButtonIconIds {
    ButtonIconIds();
    ButtonIconIds(int icon_id,
                  int inactive_icon_id,
                  int hovered_background_id,
                  int pressed_background_id);
    ~ButtonIconIds();

    int icon_image_id;
    int inactive_icon_image_id;
    int hovered_background_image_id;
    int pressed_background_image_id;
  };

  
  
  
  
  void SetButtonIcon(FrameCaptionButton* button,
                     CaptionButtonIcon icon,
                     Animate animate);

  
  
  bool ShouldSizeButtonBeVisible() const;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual bool IsMinimizeButtonVisible() const OVERRIDE;
  virtual void SetButtonsToNormal(Animate animate) OVERRIDE;
  virtual void SetButtonIcons(CaptionButtonIcon minimize_button_icon,
                              CaptionButtonIcon close_button_icon,
                              Animate animate) OVERRIDE;
  virtual const FrameCaptionButton* GetButtonClosestTo(
      const gfx::Point& position_in_screen) const OVERRIDE;
  virtual void SetHoveredAndPressedButtons(
      const FrameCaptionButton* to_hover,
      const FrameCaptionButton* to_press) OVERRIDE;

  
  views::Widget* frame_;

  
  
  FrameCaptionButton* minimize_button_;
  FrameCaptionButton* size_button_;
  FrameCaptionButton* close_button_;

  
  
  std::map<CaptionButtonIcon, ButtonIconIds> button_icon_id_map_;

  
  
  scoped_ptr<gfx::SlideAnimation> maximize_mode_animation_;

  DISALLOW_COPY_AND_ASSIGN(FrameCaptionButtonContainerView);
};

}  

#endif  
