// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_NEVER_SAVE_VIEW_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_NEVER_SAVE_VIEW_CONTROLLER_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#import "chrome/browser/ui/cocoa/passwords/manage_passwords_bubble_content_view_controller.h"

class ManagePasswordsBubbleModel;

@protocol ManagePasswordsBubbleNeverSaveViewDelegate<
    ManagePasswordsBubbleContentViewDelegate>

- (void)neverSavePasswordCancelled;

@end

@interface ManagePasswordsBubbleNeverSaveViewController
    : ManagePasswordsBubbleContentViewController {
 @private
  ManagePasswordsBubbleModel* model_;  
  id<ManagePasswordsBubbleNeverSaveViewDelegate> delegate_;  
  base::scoped_nsobject<NSButton> confirmButton_;
  base::scoped_nsobject<NSButton> undoButton_;
}
- (id)initWithModel:(ManagePasswordsBubbleModel*)model
           delegate:(id<ManagePasswordsBubbleNeverSaveViewDelegate>)delegate;
@end

@interface ManagePasswordsBubbleNeverSaveViewController (Testing)
@property(readonly) NSButton* confirmButton;
@property(readonly) NSButton* undoButton;
@end

#endif  
