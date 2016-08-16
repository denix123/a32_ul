// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_USER_ROUNDED_IMAGE_VIEW_H_
#define ASH_SYSTEM_USER_ROUNDED_IMAGE_VIEW_H_

#include "base/macros.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/views/view.h"

namespace ash {
namespace tray {

class RoundedImageView : public views::View {
 public:
  
  
  
  RoundedImageView(int corner_radius, bool active_user);
  virtual ~RoundedImageView();

  
  
  void SetImage(const gfx::ImageSkia& img, const gfx::Size& size);

  
  void SetCornerRadii(int top_left,
                      int top_right,
                      int bottom_right,
                      int bottom_left);

 private:
  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  gfx::ImageSkia image_;
  gfx::ImageSkia resized_;
  gfx::Size image_size_;
  int corner_radius_[4];

  
  
  bool active_user_;

  DISALLOW_COPY_AND_ASSIGN(RoundedImageView);
};

}  
}  

#endif  
