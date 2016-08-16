// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_DEFAULT_HEADER_PAINTER_H_
#define ASH_FRAME_DEFAULT_HEADER_PAINTER_H_

#include "ash/ash_export.h"
#include "ash/frame/header_painter.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"  
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/animation/animation_delegate.h"

namespace gfx {
class ImageSkia;
class Rect;
class SlideAnimation;
}
namespace views {
class View;
class Widget;
}

namespace ash {
class FrameCaptionButtonContainerView;

class ASH_EXPORT DefaultHeaderPainter : public HeaderPainter,
                                        public gfx::AnimationDelegate {
 public:
  DefaultHeaderPainter();
  virtual ~DefaultHeaderPainter();

  
  void Init(views::Widget* frame,
            views::View* header_view,
            FrameCaptionButtonContainerView* caption_button_container);

  
  virtual int GetMinimumHeaderWidth() const OVERRIDE;
  virtual void PaintHeader(gfx::Canvas* canvas, Mode mode) OVERRIDE;
  virtual void LayoutHeader() OVERRIDE;
  virtual int GetHeaderHeightForPainting() const OVERRIDE;
  virtual void SetHeaderHeightForPainting(int height) OVERRIDE;
  virtual void SchedulePaintForTitle() OVERRIDE;
  virtual void UpdateLeftViewXInset(int left_view_x_inset) OVERRIDE;

  
  void UpdateLeftHeaderView(views::View* left_header_view);

 private:
  FRIEND_TEST_ALL_PREFIXES(DefaultHeaderPainterTest, TitleIconAlignment);

  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;

  
  
  void PaintHighlightForInactiveRestoredWindow(gfx::Canvas* canvas);

  
  void PaintTitleBar(gfx::Canvas* canvas);

  
  void PaintHeaderContentSeparator(gfx::Canvas* canvas);

  
  void LayoutLeftHeaderView();

  
  void UpdateSizeButtonImages();

  
  
  
  gfx::Rect GetLocalBounds() const;

  
  gfx::Rect GetTitleBounds() const;

  
  SkColor GetInactiveFrameColor() const;

  views::Widget* frame_;
  views::View* view_;
  views::View* left_header_view_;  
  int left_view_x_inset_;
  FrameCaptionButtonContainerView* caption_button_container_;

  
  int height_;

  
  Mode mode_;

  
  bool initial_paint_;

  scoped_ptr<gfx::SlideAnimation> activation_animation_;

  DISALLOW_COPY_AND_ASSIGN(DefaultHeaderPainter);
};

}  

#endif  
