// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_VIEWS_H_
#define CHROME_BROWSER_UI_VIEWS_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_VIEWS_H_

#include "chrome/browser/ui/autofill/password_generation_popup_view.h"
#include "chrome/browser/ui/views/autofill/autofill_popup_base_view.h"
#include "ui/gfx/font_list.h"
#include "ui/views/controls/styled_label_listener.h"

namespace views {
class StyledLabel;
class View;
}

namespace autofill {

class PasswordGenerationPopupController;

class PasswordGenerationPopupViewViews : public AutofillPopupBaseView,
                                         public PasswordGenerationPopupView,
                                         public views::StyledLabelListener {
 public:
  PasswordGenerationPopupViewViews(
      PasswordGenerationPopupController* controller,
      views::Widget* observing_widget);

  
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual gfx::Size GetPreferredSizeOfPasswordView() OVERRIDE;
  virtual void UpdateBoundsAndRedrawPopup() OVERRIDE;
  virtual void PasswordSelectionUpdated() OVERRIDE;
  virtual bool IsPointInPasswordBounds(const gfx::Point& point) OVERRIDE;

 private:
  
  class PasswordBox;

  virtual ~PasswordGenerationPopupViewViews();

  
  void CreatePasswordView();

  
  virtual void Layout() OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  
  virtual void StyledLabelLinkClicked(const gfx::Range& range,
                                      int event_flags) OVERRIDE;

  
  PasswordBox* password_view_;
  views::StyledLabel* help_label_;

  
  gfx::FontList font_list_;

  
  gfx::Rect divider_bounds_;

  
  PasswordGenerationPopupController* controller_;

  DISALLOW_COPY_AND_ASSIGN(PasswordGenerationPopupViewViews);
};

}  

#endif  
