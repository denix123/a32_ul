// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#import "chrome/browser/ui/cocoa/base_bubble_controller.h"
#include "chrome/browser/ui/website_settings/permission_bubble_view.h"
#include "ui/base/models/simple_menu_model.h"

@class MenuController;
class PermissionBubbleCocoa;
class PermissionBubbleRequest;

@interface PermissionBubbleController :
    BaseBubbleController<NSTextViewDelegate> {
 @private
  
  
  base::scoped_nsobject<NSMutableArray> checkboxes_;

  
  PermissionBubbleView::Delegate* delegate_;  

  
  scoped_ptr<ui::SimpleMenuModel::Delegate> menuDelegate_;

  
  PermissionBubbleCocoa* bridge_;  
}

- (id)initWithParentWindow:(NSWindow*)parentWindow
                    bridge:(PermissionBubbleCocoa*)bridge;

- (void)showAtAnchor:(NSPoint)anchor
         withDelegate:(PermissionBubbleView::Delegate*)delegate
          forRequests:(const std::vector<PermissionBubbleRequest*>&)requests
         acceptStates:(const std::vector<bool>&)acceptStates
    customizationMode:(BOOL)customizationMode;

- (void)onMenuItemClicked:(int)commandId;

@end
