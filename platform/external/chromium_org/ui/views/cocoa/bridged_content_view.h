// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_COCOA_BRIDGED_CONTENT_VIEW_H_
#define UI_VIEWS_COCOA_BRIDGED_CONTENT_VIEW_H_

#import <Cocoa/Cocoa.h>

#import "ui/base/cocoa/tracking_area.h"

namespace ui {
class TextInputClient;
}

namespace views {
class View;
}

@interface BridgedContentView : NSView<NSTextInputClient> {
 @private
  
  views::View* hostedView_;

  
  
  ui::TextInputClient* textInputClient_;

  
  ui::ScopedCrTrackingArea trackingArea_;
}

@property(readonly, nonatomic) views::View* hostedView;
@property(assign, nonatomic) ui::TextInputClient* textInputClient;

- (id)initWithView:(views::View*)viewToHost;

- (void)clearView;

@end

#endif  
