// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_AUTOFILL_AUTOFILL_POPUP_VIEW_VIEWS_H_
#define CHROME_BROWSER_UI_VIEWS_AUTOFILL_AUTOFILL_POPUP_VIEW_VIEWS_H_

#include "chrome/browser/ui/autofill/autofill_popup_view.h"
#include "chrome/browser/ui/views/autofill/autofill_popup_base_view.h"

class AutofillPopupController;

namespace autofill {

class AutofillPopupViewViews : public AutofillPopupBaseView,
                               public AutofillPopupView {
 public:
  
  
  
  AutofillPopupViewViews(AutofillPopupController* controller,
                         views::Widget* observing_widget);

 private:
  virtual ~AutofillPopupViewViews();

  
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual void InvalidateRow(size_t row) OVERRIDE;
  virtual void UpdateBoundsAndRedrawPopup() OVERRIDE;

  
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  
  void DrawAutofillEntry(gfx::Canvas* canvas,
                         int index,
                         const gfx::Rect& entry_rect);

  AutofillPopupController* controller_;  

  DISALLOW_COPY_AND_ASSIGN(AutofillPopupViewViews);
};

}  

#endif  
