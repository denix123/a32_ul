// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PROFILES_AVATAR_BASE_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_PROFILES_AVATAR_BASE_CONTROLLER_H_

#import <AppKit/AppKit.h>

#import "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/browser_window.h"

@class BaseBubbleController;
class Browser;
class ProfileInfoUpdateObserver;

@interface AvatarBaseController : NSViewController {
 @protected
  Browser* browser_;

  
  base::scoped_nsobject<NSButton> button_;

 @private
  
  BaseBubbleController* menuController_;

  
  scoped_ptr<ProfileInfoUpdateObserver> profileInfoObserver_;
}

@property(readonly, nonatomic) NSButton* buttonView;

- (id)initWithBrowser:(Browser*)browser;

- (void)showAvatarBubbleAnchoredAt:(NSView*)anchor
                          withMode:(BrowserWindow::AvatarBubbleMode)mode
                   withServiceType:(signin::GAIAServiceType)serviceType;

@end

@interface AvatarBaseController (ExposedForTesting)
- (BaseBubbleController*)menuController;
@end

#endif  
