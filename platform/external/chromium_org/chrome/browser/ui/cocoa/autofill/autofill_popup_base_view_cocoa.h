// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_POPUP_BASE_VIEW_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_POPUP_BASE_VIEW_COCOA_H_

#import <Cocoa/Cocoa.h>

#import "ui/base/cocoa/base_view.h"

namespace autofill {
class AutofillPopupViewDelegate;
}

@interface AutofillPopupBaseViewCocoa : BaseView {
 @private
   __weak autofill::AutofillPopupViewDelegate* delegate_;
}

- (NSColor*)backgroundColor;
- (NSColor*)borderColor;
- (NSColor*)highlightColor;
- (NSColor*)nameColor;
- (NSColor*)separatorColor;
- (NSColor*)subtextColor;
- (NSColor*)warningColor;

- (id)initWithDelegate:(autofill::AutofillPopupViewDelegate*)delegate
                 frame:(NSRect)frame;

- (void)delegateDestroyed;

- (void)drawBackgroundAndBorder;

- (void)drawSeparatorWithBounds:(NSRect)bounds;

- (void)updateBoundsAndRedrawPopup;
- (void)showPopup;
- (void)hidePopup;
@end

#endif  
