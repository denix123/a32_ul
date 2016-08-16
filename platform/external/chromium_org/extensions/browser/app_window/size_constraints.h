// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_APP_WINDOW_SIZE_CONSTRAINTS_H_
#define EXTENSIONS_BROWSER_APP_WINDOW_SIZE_CONSTRAINTS_H_

#include "ui/gfx/geometry/size.h"

namespace gfx {
class Insets;
}

namespace extensions {

class SizeConstraints {
 public:
  
  
  enum { kUnboundedSize = 0 };

  SizeConstraints();
  SizeConstraints(const gfx::Size& min_size, const gfx::Size& max_size);
  ~SizeConstraints();

  
  static gfx::Size AddFrameToConstraints(const gfx::Size& size_constraints,
                                         const gfx::Insets& frame_insets);

  
  gfx::Size ClampSize(gfx::Size size) const;

  
  
  
  
  bool HasMinimumSize() const;
  bool HasMaximumSize() const;

  
  
  bool HasFixedSize() const;

  gfx::Size GetMaximumSize() const;
  gfx::Size GetMinimumSize() const;

  void set_minimum_size(const gfx::Size& min_size);
  void set_maximum_size(const gfx::Size& max_size);

 private:
  gfx::Size minimum_size_;
  gfx::Size maximum_size_;
};

}  

#endif  
