// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_MASKED_TARGETER_DELEGATE_H_
#define UI_VIEWS_MASKED_TARGETER_DELEGATE_H_

#include "ui/base/ui_base_types.h"
#include "ui/views/view_targeter_delegate.h"
#include "ui/views/views_export.h"

namespace gfx {
class Path;
class Rect;
}

namespace views {
class View;

class VIEWS_EXPORT MaskedTargeterDelegate : public ViewTargeterDelegate {
 public:
  MaskedTargeterDelegate() {}
  virtual ~MaskedTargeterDelegate() {}

  
  
  
  virtual bool GetHitTestMask(gfx::Path* mask) const = 0;

  
  virtual bool DoesIntersectRect(const View* target,
                                 const gfx::Rect& rect) const OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(MaskedTargeterDelegate);
};

}  

#endif  
