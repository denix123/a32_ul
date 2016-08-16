// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_CONSTRAINED_WINDOW_CONSTRAINED_WINDOW_BUTTON_
#define CHROME_BROWSER_UI_COCOA_CONSTRAINED_WINDOW_CONSTRAINED_WINDOW_BUTTON_

#import <Cocoa/Cocoa.h>

#import "ui/base/cocoa/tracking_area.h"

namespace constrained_window_button {
const CGFloat kButtonMinWidth = 72;
}

@protocol ConstrainedWindowButtonDrawableCell
@property (nonatomic, assign) BOOL isMouseInside;
- (BOOL)isEnabled;
- (BOOL)isHighlighted;
@end

@interface ConstrainedWindowButton : NSButton {
 @private
  ui::ScopedCrTrackingArea trackingArea_;
}

extern const CGFloat buttonMinWidth_;

+ (void)DrawBackgroundAndShadowForPath:(NSBezierPath*)path
                          withCell:(id<ConstrainedWindowButtonDrawableCell>)cell
                            inView:(NSView*)view;

+ (void)DrawInnerHighlightForPath:(NSBezierPath*)path
                         withCell:(id<ConstrainedWindowButtonDrawableCell>)cell
                           inView:(NSView*)view;

+ (void)DrawBorderForPath:(NSBezierPath*)path
                 withCell:(id<ConstrainedWindowButtonDrawableCell>)cell
                   inView:(NSView*)view;
@end

@interface ConstrainedWindowButtonCell :
    NSButtonCell<ConstrainedWindowButtonDrawableCell> {
 @private
  BOOL isMouseInside_;
}

@end

#endif  
