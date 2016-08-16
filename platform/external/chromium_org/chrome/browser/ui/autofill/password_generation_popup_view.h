// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_H_
#define CHROME_BROWSER_UI_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_H_

#include "third_party/skia/include/core/SkColor.h"

namespace gfx {
class Point;
class Size;
}

namespace autofill {

class PasswordGenerationPopupController;

class PasswordGenerationPopupView {
 public:
  
  static const int kHelpSectionAdditionalSpacing = 3;

  
  virtual void Show() = 0;

  
  virtual void Hide() = 0;

  
  virtual gfx::Size GetPreferredSizeOfPasswordView() = 0;

  
  virtual void UpdateBoundsAndRedrawPopup() = 0;

  
  virtual void PasswordSelectionUpdated() = 0;

  virtual bool IsPointInPasswordBounds(const gfx::Point& point) = 0;

  
  
  static PasswordGenerationPopupView* Create(
      PasswordGenerationPopupController* controller);

  static const SkColor kPasswordTextColor;
  static const SkColor kExplanatoryTextBackgroundColor;
  static const SkColor kExplanatoryTextColor;
  static const SkColor kDividerColor;
};

}  

#endif  
