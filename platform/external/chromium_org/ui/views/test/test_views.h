// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_TEST_TEST_VIEWS_H_
#define UI_VIEWS_TEST_TEST_VIEWS_H_

#include "base/memory/scoped_ptr.h"
#include "ui/views/view.h"

namespace views {

class StaticSizedView : public View {
 public:
  explicit StaticSizedView(const gfx::Size& size);
  virtual ~StaticSizedView();

  virtual gfx::Size GetPreferredSize() const OVERRIDE;

 private:
  gfx::Size size_;

  DISALLOW_COPY_AND_ASSIGN(StaticSizedView);
};

class ProportionallySizedView : public View {
 public:
  explicit ProportionallySizedView(int factor);
  virtual ~ProportionallySizedView();

  void set_preferred_width(int width) { preferred_width_ = width; }

  virtual int GetHeightForWidth(int w) const OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;

 private:
  
  
  int factor_;

  
  int preferred_width_;

  DISALLOW_COPY_AND_ASSIGN(ProportionallySizedView);
};

}  

#endif  
