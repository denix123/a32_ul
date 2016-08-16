// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_SPRITE_VIEW_H_
#define CHROME_BROWSER_UI_COCOA_SPRITE_VIEW_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"

@class CAKeyframeAnimation;

@interface SpriteView : NSView {
 @private
  base::scoped_nsobject<CAKeyframeAnimation> spriteAnimation_;
  CALayer* imageLayer_;
}

- (void)setImage:(NSImage*)image;

- (void)setImage:(NSImage*)image withToastAnimation:(BOOL)animate;

@end

#endif  
