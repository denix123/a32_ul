// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PRESENTATION_MODE_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_PRESENTATION_MODE_CONTROLLER_H_

#include <Carbon/Carbon.h>
#import <Cocoa/Cocoa.h>

#include "base/mac/mac_util.h"
#include "chrome/browser/ui/cocoa/location_bar/location_bar_view_mac.h"

@class BrowserWindowController;
@class DropdownAnimation;

namespace fullscreen_mac {
enum SlidingStyle {
  OMNIBOX_TABS_PRESENT = 0,  
  OMNIBOX_TABS_HIDDEN,       
};
}  


@interface PresentationModeController : NSObject<NSAnimationDelegate> {
 @private
  
  BrowserWindowController* browserController_;  

  
  
  NSView* contentView_;  

  
  BOOL enteringPresentationMode_;

  
  BOOL inPresentationMode_;

  
  
  
  
  
  base::scoped_nsobject<NSTrackingArea> trackingArea_;

  
  
  base::scoped_nsobject<DropdownAnimation> currentAnimation_;

  
  
  base::scoped_nsobject<NSTimer> showTimer_;
  base::scoped_nsobject<NSTimer> hideTimer_;

  
  
  
  NSRect trackingAreaBounds_;

  
  
  
  
  
  
  
  
  
  base::mac::FullScreenMode systemFullscreenMode_;

  
  fullscreen_mac::SlidingStyle slidingStyle_;

  
  
  CGFloat menubarFraction_;

  
  
  CGFloat toolbarFraction_;

  
  EventHandlerRef menuBarTrackingHandler_;
}

@property(readonly, nonatomic) BOOL inPresentationMode;
@property(nonatomic, assign) fullscreen_mac::SlidingStyle slidingStyle;
@property(nonatomic, assign) CGFloat toolbarFraction;

- (id)initWithBrowserController:(BrowserWindowController*)controller
                          style:(fullscreen_mac::SlidingStyle)style;

- (void)enterPresentationModeForContentView:(NSView*)contentView
                               showDropdown:(BOOL)showDropdown;
- (void)exitPresentationMode;

- (CGFloat)floatingBarVerticalOffset;

- (void)overlayFrameChanged:(NSRect)frame;

- (void)ensureOverlayShownWithAnimation:(BOOL)animate delay:(BOOL)delay;
- (void)ensureOverlayHiddenWithAnimation:(BOOL)animate delay:(BOOL)delay;

- (void)cancelAnimationAndTimers;

- (CGFloat)menubarOffset;

@end

@interface PresentationModeController (ExposedForTesting)
- (void)setSystemFullscreenModeTo:(base::mac::FullScreenMode)mode;

- (void)setMenuBarRevealProgress:(CGFloat)progress;

- (void)changeToolbarFraction:(CGFloat)fraction;
@end

extern NSString* const kWillEnterFullscreenNotification;
extern NSString* const kWillLeaveFullscreenNotification;

#endif  
