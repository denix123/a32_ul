// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_BROWSER_WINDOW_CONTROLLER_LAYOUT_H_
#define CHROME_BROWSER_UI_COCOA_BROWSER_WINDOW_CONTROLLER_LAYOUT_H_

#import <Cocoa/Cocoa.h>

#import "chrome/browser/ui/cocoa/presentation_mode_controller.h"

namespace chrome {

extern const CGFloat kTabStripHeight;

struct LayoutParameters {
  
  NSSize contentViewSize;
  
  NSSize windowSize;

  
  
  BOOL inAnyFullscreen;
  
  
  fullscreen_mac::SlidingStyle slidingStyle;
  
  
  CGFloat menubarOffset;
  
  
  CGFloat toolbarFraction;

  BOOL hasTabStrip;

  BOOL hasToolbar;
  BOOL hasLocationBar;
  CGFloat toolbarHeight;

  BOOL bookmarkBarHidden;
  
  
  
  BOOL placeBookmarkBarBelowInfoBar;
  CGFloat bookmarkBarHeight;

  
  CGFloat infoBarHeight;
  
  
  CGFloat pageInfoBubblePointY;

  BOOL hasDownloadShelf;
  CGFloat downloadShelfHeight;
};

struct LayoutOutput {
  NSRect tabStripFrame;
  NSRect toolbarFrame;
  NSRect bookmarkFrame;
  NSRect fullscreenBackingBarFrame;
  CGFloat findBarMaxY;
  CGFloat fullscreenExitButtonMaxY;
  NSRect infoBarFrame;
  CGFloat infoBarMaxTopArrowHeight;
  NSRect downloadShelfFrame;
  NSRect contentAreaFrame;
};

}  

@interface BrowserWindowLayout : NSObject {
 @private
  
  chrome::LayoutParameters parameters_;

  
  chrome::LayoutOutput output_;

  
  CGFloat fullscreenYOffset_;

  
  
  CGFloat maxY_;
}

- (chrome::LayoutOutput)computeLayout;

- (void)setContentViewSize:(NSSize)size;
- (void)setWindowSize:(NSSize)size;

- (void)setInAnyFullscreen:(BOOL)inAnyFullscreen;
- (void)setFullscreenSlidingStyle:(fullscreen_mac::SlidingStyle)slidingStyle;
- (void)setFullscreenMenubarOffset:(CGFloat)menubarOffset;
- (void)setFullscreenToolbarFraction:(CGFloat)toolbarFraction;

- (void)setHasTabStrip:(BOOL)hasTabStrip;

- (void)setHasToolbar:(BOOL)hasToolbar;
- (void)setHasLocationBar:(BOOL)hasLocationBar;
- (void)setToolbarHeight:(CGFloat)toolbarHeight;

- (void)setBookmarkBarHidden:(BOOL)bookmarkBarHidden;
- (void)setPlaceBookmarkBarBelowInfoBar:(BOOL)placeBookmarkBarBelowInfoBar;
- (void)setBookmarkBarHeight:(CGFloat)bookmarkBarHeight;

- (void)setInfoBarHeight:(CGFloat)infoBarHeight;
- (void)setPageInfoBubblePointY:(CGFloat)pageInfoBubblePointY;

- (void)setHasDownloadShelf:(BOOL)hasDownloadShelf;
- (void)setDownloadShelfHeight:(CGFloat)downloadShelfHeight;

@end

#endif  
