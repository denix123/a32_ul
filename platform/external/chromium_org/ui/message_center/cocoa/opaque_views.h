// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_COCOA_OPAQUE_VIEWS_H_
#define UI_MESSAGE_CENTER_COCOA_OPAQUE_VIEWS_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"

@interface MCDropDown : NSPopUpButton {
 @private
  base::scoped_nsobject<NSColor> backgroundColor_;
}

- (NSColor*)backgroundColor;
- (void)setBackgroundColor:(NSColor*)backgroundColor;
@end

@interface MCTextField : NSTextField {
 @private
  base::scoped_nsobject<NSColor> backgroundColor_;
}

- (id)initWithFrame:(NSRect)frameRect backgroundColor:(NSColor*)color;
@end

#endif  
