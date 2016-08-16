// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_PENDING_VIEW_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_PENDING_VIEW_CONTROLLER_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#import "chrome/browser/ui/cocoa/passwords/manage_passwords_bubble_content_view_controller.h"

namespace ui {
class ComboboxModel;
}  

@class BubbleCombobox;
class ManagePasswordsBubbleModel;
@class ManagePasswordItemViewController;

@protocol ManagePasswordsBubblePendingViewDelegate<
    ManagePasswordsBubbleContentViewDelegate>

- (void)passwordShouldNeverBeSavedOnSiteWithExistingPasswords;

@end

@interface ManagePasswordsBubblePendingViewController
    : ManagePasswordsBubbleContentViewController {
 @private
  ManagePasswordsBubbleModel* model_;  
  id<ManagePasswordsBubblePendingViewDelegate> delegate_;  
  base::scoped_nsobject<NSButton> saveButton_;
  base::scoped_nsobject<BubbleCombobox> nopeButton_;
  base::scoped_nsobject<ManagePasswordItemViewController> passwordItem_;
}
- (id)initWithModel:(ManagePasswordsBubbleModel*)model
           delegate:(id<ManagePasswordsBubblePendingViewDelegate>)delegate;
@end

@interface ManagePasswordsBubblePendingViewController (Testing)
@property(readonly) NSButton* saveButton;
@property(readonly) BubbleCombobox* nopeButton;
@end

#endif  
