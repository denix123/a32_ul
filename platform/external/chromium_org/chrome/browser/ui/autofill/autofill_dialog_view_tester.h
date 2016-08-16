// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_DIALOG_VIEW_TESTER_H_
#define CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_DIALOG_VIEW_TESTER_H_

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/ui/autofill/autofill_dialog_types.h"
#include "components/autofill/core/browser/field_types.h"
#include "ui/gfx/size.h"

namespace content {
class WebContents;
}

namespace autofill {

class AutofillDialogView;

class AutofillDialogViewTester {
 public:
  
  static scoped_ptr<AutofillDialogViewTester> For(AutofillDialogView* view);

  virtual ~AutofillDialogViewTester() {}

  
  virtual void SubmitForTesting() = 0;

  
  virtual void CancelForTesting() = 0;

  
  virtual base::string16 GetTextContentsOfInput(ServerFieldType type) = 0;

  
  virtual void SetTextContentsOfInput(ServerFieldType type,
                                      const base::string16& contents) = 0;

  
  virtual void SetTextContentsOfSuggestionInput(DialogSection section,
                                                const base::string16& text) = 0;

  
  virtual void ActivateInput(ServerFieldType type) = 0;

  
  virtual gfx::Size GetSize() const = 0;

  
  virtual content::WebContents* GetSignInWebContents() = 0;

  
  virtual bool IsShowingOverlay() const = 0;

  
  virtual bool IsShowingSection(DialogSection section) const = 0;
};

}  

#endif  
