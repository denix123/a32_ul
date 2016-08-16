// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_VIEW_TARGETER_DELEGATE_H_
#define UI_VIEWS_VIEW_TARGETER_DELEGATE_H_

#include "base/macros.h"
#include "ui/views/views_export.h"

namespace gfx {
class Rect;
}

namespace views {
class View;

class VIEWS_EXPORT ViewTargeterDelegate {
 public:
  ViewTargeterDelegate() {}
  virtual ~ViewTargeterDelegate() {}

  
  
  
  virtual bool DoesIntersectRect(const View* target,
                                 const gfx::Rect& rect) const;

  
  
  
  
  
  
  
  
  virtual View* TargetForRect(View* root, const gfx::Rect& rect);

 private:
  DISALLOW_COPY_AND_ASSIGN(ViewTargeterDelegate);
};

}  

#endif  
