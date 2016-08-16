// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TABS_MEDIA_INDICATOR_BUTTON_H_
#define CHROME_BROWSER_UI_VIEWS_TABS_MEDIA_INDICATOR_BUTTON_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/tabs/tab_utils.h"
#include "ui/views/controls/button/image_button.h"
#include "ui/views/view_targeter_delegate.h"

namespace gfx {
class Animation;
class AnimationDelegate;
}

class MediaIndicatorButton : public views::ImageButton,
                             public views::ViewTargeterDelegate {
 public:
  
  static const char kViewClassName[];

  MediaIndicatorButton();
  virtual ~MediaIndicatorButton();

  
  
  TabMediaState showing_media_state() const {
    return showing_media_state_;
  }

  
  
  void TransitionToMediaState(TabMediaState next_state);

 protected:
  
  virtual const char* GetClassName() const OVERRIDE;
  virtual View* GetTooltipHandlerForPoint(const gfx::Point& point) OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  
  virtual bool DoesIntersectRect(const View* target,
                                 const gfx::Rect& rect) const OVERRIDE;

  
  virtual void NotifyClick(const ui::Event& event) OVERRIDE;

 private:
  class FadeAnimationDelegate;

  TabMediaState media_state_;

  
  
  scoped_ptr<gfx::AnimationDelegate> fade_animation_delegate_;
  scoped_ptr<gfx::Animation> fade_animation_;
  TabMediaState showing_media_state_;

  DISALLOW_COPY_AND_ASSIGN(MediaIndicatorButton);
};

#endif  
