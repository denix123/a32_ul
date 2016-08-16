// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_VIEWS_PROPORTIONAL_IMAGE_VIEW_H_
#define UI_MESSAGE_CENTER_VIEWS_PROPORTIONAL_IMAGE_VIEW_H_

#include "ui/gfx/image/image_skia.h"
#include "ui/views/view.h"

namespace message_center {

class ProportionalImageView : public views::View {
 public:
  ProportionalImageView(const gfx::ImageSkia& image, const gfx::Size& max_size);
  virtual ~ProportionalImageView();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual int GetHeightForWidth(int width) const OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

 private:
  gfx::Size GetImageDrawingSize();

  gfx::ImageSkia image_;
  gfx::Size max_size_;

  DISALLOW_COPY_AND_ASSIGN(ProportionalImageView);
};

}  

#endif 
