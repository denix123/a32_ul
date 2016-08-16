// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_POPUP_VIEW_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_POPUP_VIEW_COCOA_H_

#import <Cocoa/Cocoa.h>

#import "chrome/browser/ui/cocoa/autofill/autofill_popup_base_view_cocoa.h"

namespace autofill {
class AutofillPopupController;
}  

@interface AutofillPopupViewCocoa : AutofillPopupBaseViewCocoa {
 @private
  
  __weak autofill::AutofillPopupController* controller_;
}

- (id)initWithController:(autofill::AutofillPopupController*)controller
                   frame:(NSRect)frame;

- (void)controllerDestroyed;

- (void)invalidateRow:(size_t)row;

@end

#endif  
