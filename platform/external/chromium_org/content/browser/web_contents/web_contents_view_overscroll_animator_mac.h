// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_VIEW_OVERSCROLL_ANIMATOR_MAC_H_
#define CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_VIEW_OVERSCROLL_ANIMATOR_MAC_H_

#import <Cocoa/Cocoa.h>

namespace content {
class WebContentsImpl;

enum OverscrollAnimatorDirection {
  OVERSCROLL_ANIMATOR_DIRECTION_BACKWARDS,
  OVERSCROLL_ANIMATOR_DIRECTION_FORWARDS,
};
}  

@protocol WebContentsOverscrollAnimator
- (BOOL)needsNavigationSnapshot;

- (void)beginOverscrollInDirection:
            (content::OverscrollAnimatorDirection)direction
                navigationSnapshot:(NSImage*)snapshot;

- (void)addRenderWidgetHostNativeView:(NSView*)view;

- (void)updateOverscrollProgress:(CGFloat)progress;

- (void)completeOverscroll:(content::WebContentsImpl*)webContents;

- (void)cancelOverscroll;
@end

#endif  
