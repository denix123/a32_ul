// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_FRAME_CUSTOM_FRAME_VIEW_ASH_H_
#define ASH_FRAME_CUSTOM_FRAME_VIEW_ASH_H_

#include "ash/ash_export.h"
#include "base/memory/scoped_ptr.h"
#include "ui/views/window/non_client_view.h"

namespace ash {
class FrameBorderHitTestController;
class FrameCaptionButtonContainerView;
class ImmersiveFullscreenController;
}
namespace views {
class Widget;
}

namespace ash {

class ASH_EXPORT CustomFrameViewAsh : public views::NonClientFrameView {
 public:
  
  static const char kViewClassName[];

  explicit CustomFrameViewAsh(views::Widget* frame);
  virtual ~CustomFrameViewAsh();

  
  
  
  
  void InitImmersiveFullscreenControllerForView(
      ImmersiveFullscreenController* immersive_fullscreen_controller);

  
  virtual gfx::Rect GetBoundsForClientView() const OVERRIDE;
  virtual gfx::Rect GetWindowBoundsForClientBounds(
      const gfx::Rect& client_bounds) const OVERRIDE;
  virtual int NonClientHitTest(const gfx::Point& point) OVERRIDE;
  virtual void GetWindowMask(const gfx::Size& size,
                             gfx::Path* window_mask) OVERRIDE;
  virtual void ResetWindowControls() OVERRIDE;
  virtual void UpdateWindowIcon() OVERRIDE;
  virtual void UpdateWindowTitle() OVERRIDE;
  virtual void SizeConstraintsChanged() OVERRIDE;

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual gfx::Size GetMaximumSize() const OVERRIDE;
  virtual void SchedulePaintInRect(const gfx::Rect& r) OVERRIDE;
  virtual void VisibilityChanged(views::View* starting_from,
                                 bool is_visible) OVERRIDE;

  
  views::View* GetHeaderView();

  const views::View* GetAvatarIconViewForTest() const;

 private:
  class OverlayView;
  friend class TestWidgetConstraintsDelegate;

  
  virtual bool DoesIntersectRect(const views::View* target,
                                 const gfx::Rect& rect) const OVERRIDE;

  
  
  FrameCaptionButtonContainerView* GetFrameCaptionButtonContainerViewForTest();

  
  int NonClientTopBorderHeight() const;

  
  views::Widget* frame_;

  
  class HeaderView;
  HeaderView* header_view_;

  
  scoped_ptr<FrameBorderHitTestController> frame_border_hit_test_controller_;

  DISALLOW_COPY_AND_ASSIGN(CustomFrameViewAsh);
};

}  

#endif  
