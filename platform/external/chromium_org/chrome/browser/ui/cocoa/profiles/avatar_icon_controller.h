// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PROFILES_AVATAR_ICON_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_PROFILES_AVATAR_ICON_CONTROLLER_H_

#import <AppKit/AppKit.h>

#import "base/mac/scoped_nsobject.h"
#import "chrome/browser/ui/cocoa/profiles/avatar_base_controller.h"

@class AvatarLabelButton;
class Browser;

@interface AvatarIconController : AvatarBaseController {
 @private
  
  
  base::scoped_nsobject<AvatarLabelButton> labelButton_;
}

@property(readonly, nonatomic) NSButton* labelButtonView;

- (id)initWithBrowser:(Browser*)browser;

- (void)setImage:(NSImage*)image;

@end

#endif  
