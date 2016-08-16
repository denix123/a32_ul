// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_TEST_COCOA_TEST_EVENT_UTILS_H_
#define UI_EVENTS_TEST_COCOA_TEST_EVENT_UTILS_H_

#include <utility>

#import <objc/objc-class.h>

#include "base/basictypes.h"

namespace cocoa_test_event_utils {

NSEvent* MouseEventWithType(NSEventType type, NSUInteger modifiers);
NSEvent* MouseEventAtPoint(NSPoint point, NSEventType type,
                           NSUInteger modifiers);
NSEvent* LeftMouseDownAtPoint(NSPoint point);
NSEvent* LeftMouseDownAtPointInWindow(NSPoint point, NSWindow* window);
NSEvent* RightMouseDownAtPoint(NSPoint point);
NSEvent* RightMouseDownAtPointInWindow(NSPoint point, NSWindow* window);

std::pair<NSEvent*, NSEvent*> MouseClickInView(NSView* view,
                                               NSUInteger clickCount);

NSEvent* KeyEventWithCharacter(unichar c);

NSEvent* KeyEventWithType(NSEventType event_type, NSUInteger modifiers);

NSEvent* KeyEventWithKeyCode(unsigned short key_code,
                             unichar c,
                             NSEventType event_type,
                             NSUInteger modifiers);

NSEvent* EnterExitEventWithType(NSEventType event_type);

NSEvent* OtherEventWithType(NSEventType event_type);

}  

#endif  
