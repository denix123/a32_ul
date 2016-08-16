// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_BUBBLE_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_AUTOFILL_AUTOFILL_BUBBLE_CONTROLLER_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#import "chrome/browser/ui/cocoa/base_bubble_controller.h"
#import "chrome/browser/ui/cocoa/info_bubble_view.h"

@interface AutofillBubbleController : BaseBubbleController {
 @private
   base::scoped_nsobject<NSTextField> label_;
   NSSize inset_;  
}

- (id)initWithParentWindow:(NSWindow*)parentWindow
                   message:(NSString*)message;

- (id)initWithParentWindow:(NSWindow*)parentWindow
                   message:(NSString*)message
                     inset:(NSSize)inset
             arrowLocation:(info_bubble::BubbleArrowLocation)arrowLocation;

- (CGFloat)maxWidth;

- (void)setMessage:(NSString*)message;

@end


#endif  
