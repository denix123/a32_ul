// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_HEADER_PAINTER_ASH_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_HEADER_PAINTER_ASH_H_

#include "ash/frame/header_painter.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"  
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/animation/animation_delegate.h"

class BrowserView;

namespace ash {
class FrameCaptionButtonContainerView;
}

namespace gfx {
class ImageSkia;
class Rect;
class SlideAnimation;
}
namespace views {
class View;
class Widget;
}

class BrowserHeaderPainterAsh : public ash::HeaderPainter,
                                public gfx::AnimationDelegate {
 public:
  BrowserHeaderPainterAsh();
  virtual ~BrowserHeaderPainterAsh();

  
  void Init(
    views::Widget* frame,
    BrowserView* browser_view,
    views::View* header_view,
    views::View* window_icon,
    ash::FrameCaptionButtonContainerView* caption_button_container);

  
  virtual int GetMinimumHeaderWidth() const OVERRIDE;
  virtual void PaintHeader(gfx::Canvas* canvas, Mode mode) OVERRIDE;
  virtual void LayoutHeader() OVERRIDE;
  virtual int GetHeaderHeightForPainting() const OVERRIDE;
  virtual void SetHeaderHeightForPainting(int height) OVERRIDE;
  virtual void SchedulePaintForTitle() OVERRIDE;
  virtual void UpdateLeftViewXInset(int left_view_x_inset) OVERRIDE;

 private:
  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;

  
  void PaintHighlightForRestoredWindow(gfx::Canvas* canvas);

  
  void PaintTitleBar(gfx::Canvas* canvas);

  
  
  
  void GetFrameImages(Mode mode,
                      gfx::ImageSkia* frame_image,
                      gfx::ImageSkia* frame_overlay_image) const;

  
  
  
  void GetFrameImagesForTabbedBrowser(
      Mode mode,
      gfx::ImageSkia* frame_image,
      gfx::ImageSkia* frame_overlay_image) const;

  
  
  gfx::ImageSkia GetFrameImageForNonTabbedBrowser(Mode mode) const;

  
  void UpdateCaptionButtonImages();

  
  
  
  gfx::Rect GetPaintedBounds() const;

  
  gfx::Rect GetTitleBounds() const;

  views::Widget* frame_;

  
  bool is_tabbed_;

  
  bool is_incognito_;

  
  views::View* view_;

  views::View* window_icon_;
  int window_icon_x_inset_;
  ash::FrameCaptionButtonContainerView* caption_button_container_;
  int painted_height_;

  
  bool initial_paint_;

  
  Mode mode_;

  scoped_ptr<gfx::SlideAnimation> activation_animation_;

  DISALLOW_COPY_AND_ASSIGN(BrowserHeaderPainterAsh);
};

#endif  
