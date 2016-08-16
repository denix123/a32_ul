// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_COCOA_VIEWS_NSWINDOW_DELEGATE_H_
#define UI_VIEWS_COCOA_VIEWS_NSWINDOW_DELEGATE_H_

#import <Cocoa/Cocoa.h>

namespace views {
class NativeWidgetMac;
class BridgedNativeWidget;
}

@interface ViewsNSWindowDelegate : NSObject<NSWindowDelegate> {
 @private
  views::BridgedNativeWidget* parent_;  
}

@property(nonatomic, readonly) views::NativeWidgetMac* nativeWidgetMac;

- (id)initWithBridgedNativeWidget:(views::BridgedNativeWidget*)parent;

@end

#endif  
