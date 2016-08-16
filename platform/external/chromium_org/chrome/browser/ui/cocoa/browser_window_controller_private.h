// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_BROWSER_WINDOW_CONTROLLER_PRIVATE_H_
#define CHROME_BROWSER_UI_COCOA_BROWSER_WINDOW_CONTROLLER_PRIVATE_H_

#import "chrome/browser/ui/cocoa/browser_window_controller.h"
#import "chrome/browser/ui/cocoa/presentation_mode_controller.h"

@class BrowserWindowLayout;

@interface BrowserWindowController(Private)

- (void)createTabStripController;

- (void)saveWindowPositionIfNeeded;

- (NSRect)window:(NSWindow*)window
    willPositionSheet:(NSWindow*)sheet
            usingRect:(NSRect)defaultSheetRect;

- (void)layoutSubviews;

- (void)showFullscreenExitBubbleIfNecessary;
- (void)destroyFullscreenExitBubbleIfNecessary;

- (CGFloat)layoutTabStripAtMaxY:(CGFloat)maxY
                          width:(CGFloat)width
                     fullscreen:(BOOL)fullscreen;

- (BOOL)placeBookmarkBarBelowInfoBar;


- (void)layoutTabContentArea:(NSRect)frame;

- (void)adjustToolbarAndBookmarkBarForCompression:(CGFloat)compression;

- (void)moveViewsForImmersiveFullscreen:(BOOL)fullscreen
                          regularWindow:(NSWindow*)regularWindow
                       fullscreenWindow:(NSWindow*)fullscreenWindow;

- (void)permissionBubbleWindowWillClose:(NSNotification*)notification;

- (void)enterImmersiveFullscreen;
- (void)exitImmersiveFullscreen;

- (void)registerForContentViewResizeNotifications;
- (void)deregisterForContentViewResizeNotifications;

- (void)enableBarVisibilityUpdates;
- (void)disableBarVisibilityUpdates;

- (void)hideOverlayIfPossibleWithAnimation:(BOOL)animation delay:(BOOL)delay;

- (CGFloat)toolbarDividerOpacity;

- (void)updateLayerOrdering:(NSView*)view;

- (void)updateInfoBarTipVisibility;

- (NSInteger)pageInfoBubblePointY;

- (void)configurePresentationModeController;

- (void)adjustUIForSlidingFullscreenStyle:(fullscreen_mac::SlidingStyle)style;

- (void)adjustUIForExitingFullscreenAndStopOmniboxSliding;

- (PresentationModeController*)newPresentationModeControllerWithStyle:
    (fullscreen_mac::SlidingStyle)style;

- (void)enterAppKitFullscreen;
- (void)exitAppKitFullscreen;

- (void)updateLayoutParameters:(BrowserWindowLayout*)layout;

- (void)applyLayout:(BrowserWindowLayout*)layout;

- (void)updateSubviewZOrder;

- (void)updateSubviewZOrderNormal;

- (void)updateSubviewZOrderFullscreen;

- (void)setContentViewSubviews:(NSArray*)subviews;

- (void)updateSubviewZOrderHack;

@end  

#endif  
