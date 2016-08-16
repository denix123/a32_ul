// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_AUTOFILL_PASSWORD_GENERATION_POPUP_VIEW_COCOA_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "chrome/browser/ui/autofill/password_generation_popup_controller.h"
#import "chrome/browser/ui/cocoa/autofill/autofill_popup_base_view_cocoa.h"

namespace autofill {
class AutofillPopupController;
}  

@class HyperlinkTextView;

@interface PasswordGenerationPopupViewCocoa
    : AutofillPopupBaseViewCocoa <NSTextViewDelegate> {
 @private
  
  __weak autofill::PasswordGenerationPopupController* controller_;

  base::scoped_nsobject<NSView> passwordSection_;
  base::scoped_nsobject<NSTextField> passwordField_;
  base::scoped_nsobject<NSTextField> passwordTitleField_;
  base::scoped_nsobject<NSImageView> keyIcon_;
  base::scoped_nsobject<NSBox> divider_;
  base::scoped_nsobject<HyperlinkTextView> helpTextView_;
}

- (id)initWithController:
    (autofill::PasswordGenerationPopupController*)controller
                   frame:(NSRect)frame;

- (BOOL)isPointInPasswordBounds:(NSPoint)point;

- (void)controllerDestroyed;

- (NSSize)preferredSize;

@end

#endif  
