// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import <Cocoa/Cocoa.h>

#include "ui/base/ui_base_export.h"

@class NSColor;

UI_BASE_EXPORT
@interface HyperlinkTextView : NSTextView {
 @private
  BOOL refusesFirstResponder_;
  BOOL drawsBackgroundUsingSuperview_;
}

@property(nonatomic, assign) BOOL drawsBackgroundUsingSuperview;

- (void)setMessageAndLink:(NSString*)message
                 withLink:(NSString*)link
                 atOffset:(NSUInteger)linkOffset
                     font:(NSFont*)font
             messageColor:(NSColor*)messageColor
                linkColor:(NSColor*)linkColor;

- (void)setMessage:(NSString*)message
          withFont:(NSFont*)font
      messageColor:(NSColor*)messageColor;

- (void)addLinkRange:(NSRange)range
            withName:(id)name
           linkColor:(NSColor*)linkColor;

- (void)setRefusesFirstResponder:(BOOL)refusesFirstResponder;

@end
