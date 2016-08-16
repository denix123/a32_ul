// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_POPUP_VIEW_DELEGATE_H_
#define CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_POPUP_VIEW_DELEGATE_H_

#include "ui/gfx/native_widget_types.h"

namespace gfx {
class Point;
class Rect;
}

namespace autofill {

class AutofillPopupViewDelegate {
 public:
  
  
  virtual void Hide() = 0;

  
  virtual void ViewDestroyed() = 0;

  
  
  virtual void SetSelectionAtPoint(const gfx::Point& point) = 0;

  
  
  virtual bool AcceptSelectedLine() = 0;

  
  
  virtual void SelectionCleared() = 0;

  
  virtual const gfx::Rect& popup_bounds() const = 0;

  
  virtual gfx::NativeView container_view() = 0;

 protected:
  virtual ~AutofillPopupViewDelegate() {}
};

}  

#endif  
