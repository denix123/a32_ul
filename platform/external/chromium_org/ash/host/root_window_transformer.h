// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_HOST_ROOT_WINDOW_TRANSFORMER_H_
#define ASH_HOST_ROOT_WINDOW_TRANSFORMER_H_

#include "ash/ash_export.h"

namespace gfx {
class Insets;
class Rect;
class Size;
class Transform;
}

namespace ash {

class ASH_EXPORT RootWindowTransformer {
 public:
  virtual ~RootWindowTransformer() {}

  
  virtual gfx::Transform GetTransform() const = 0;

  
  
  
  virtual gfx::Transform GetInverseTransform() const = 0;

  
  
  
  virtual gfx::Rect GetRootWindowBounds(const gfx::Size& host_size) const = 0;

  
  
  virtual gfx::Insets GetHostInsets() const = 0;
};

}  

#endif  
