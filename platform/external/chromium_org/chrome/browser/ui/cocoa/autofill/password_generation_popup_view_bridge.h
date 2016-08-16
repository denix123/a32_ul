// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_BRIDGE_H_
#define CHROME_BROWSER_UI_COCOA_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_BRIDGE_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/mac/scoped_nsobject.h"
#include "chrome/browser/ui/autofill/password_generation_popup_view.h"

@class PasswordGenerationPopupViewCocoa;

namespace autofill {

class AutofillPopupController;

class PasswordGenerationPopupViewBridge : public PasswordGenerationPopupView {
 public:
  explicit PasswordGenerationPopupViewBridge(
      PasswordGenerationPopupController* controller);

 private:
  virtual ~PasswordGenerationPopupViewBridge();

  
  virtual void Hide() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual gfx::Size GetPreferredSizeOfPasswordView() OVERRIDE;
  virtual void UpdateBoundsAndRedrawPopup() OVERRIDE;
  virtual void PasswordSelectionUpdated() OVERRIDE;
  virtual bool IsPointInPasswordBounds(const gfx::Point& point) OVERRIDE;

  
  base::scoped_nsobject<PasswordGenerationPopupViewCocoa> view_;

  DISALLOW_COPY_AND_ASSIGN(PasswordGenerationPopupViewBridge);
};

}  

#endif  
