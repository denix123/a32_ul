// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_CONTENT_VIEW_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_CONTENT_VIEW_CONTROLLER_H_

#import <Cocoa/Cocoa.h>

namespace password_manager {
namespace mac {
namespace ui {
const CGFloat kDesiredBubbleWidth = 370;
const CGFloat kFramePadding = 16;
const CGFloat kRelatedControlHorizontalPadding = 2;
const CGFloat kUnrelatedControlVerticalPadding = 20;
}  
}  
}  

@protocol ManagePasswordsBubbleContentViewDelegate

- (void)viewShouldDismiss;

@end

@interface ManagePasswordsBubbleContentViewController : NSViewController
- (NSButton*)addButton:(NSString*)title target:(id)target action:(SEL)action;
- (NSTextField*)addTitleLabel:(NSString*)title;
- (NSTextField*)addLabel:(NSString*)title;
- (void)bubbleWillDisappear;
@end

#endif  
