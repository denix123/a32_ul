// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APPS_UI_VIEWS_APP_WINDOW_FRAME_VIEW_H_
#define APPS_UI_VIEWS_APP_WINDOW_FRAME_VIEW_H_

#include <string>

#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/path.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/window/non_client_view.h"

class SkRegion;

namespace extensions {
class NativeAppWindow;
}

namespace gfx {
class Canvas;
class Point;
}

namespace ui {
class Event;
}

namespace views {
class ImageButton;
class Widget;
}

namespace apps {

class AppWindowFrameView : public views::NonClientFrameView,
                           public views::ButtonListener {
 public:
  static const char kViewClassName[];

  
  
  
  
  
  
  
  
  AppWindowFrameView(views::Widget* widget,
                     extensions::NativeAppWindow* window,
                     bool draw_frame,
                     const SkColor& active_frame_color,
                     const SkColor& inactive_frame_color);
  virtual ~AppWindowFrameView();

  void Init();

  void SetResizeSizes(int resize_inside_bounds_size,
                      int resize_outside_bounds_size,
                      int resize_area_corner_size);
  int resize_inside_bounds_size() const {
    return resize_inside_bounds_size_;
  };

 private:
  
  virtual gfx::Rect GetBoundsForClientView() const OVERRIDE;
  virtual gfx::Rect GetWindowBoundsForClientBounds(
      const gfx::Rect& client_bounds) const OVERRIDE;
  virtual int NonClientHitTest(const gfx::Point& point) OVERRIDE;
  virtual void GetWindowMask(const gfx::Size& size,
                             gfx::Path* window_mask) OVERRIDE;
  virtual void ResetWindowControls() OVERRIDE {}
  virtual void UpdateWindowIcon() OVERRIDE {}
  virtual void UpdateWindowTitle() OVERRIDE {}
  virtual void SizeConstraintsChanged() OVERRIDE;

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual gfx::Size GetMaximumSize() const OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  
  void SetButtonImagesForFrame();

  
  SkColor CurrentFrameColor();

  views::Widget* widget_;
  extensions::NativeAppWindow* window_;
  bool draw_frame_;
  SkColor active_frame_color_;
  SkColor inactive_frame_color_;
  views::ImageButton* close_button_;
  views::ImageButton* maximize_button_;
  views::ImageButton* restore_button_;
  views::ImageButton* minimize_button_;

  
  int resize_inside_bounds_size_;

  
  int resize_outside_bounds_size_;

  
  int resize_area_corner_size_;

  DISALLOW_COPY_AND_ASSIGN(AppWindowFrameView);
};

}  

#endif  
