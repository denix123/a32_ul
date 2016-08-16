// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_COCOA_COCOA_EVENT_UTILS_H_
#define UI_EVENTS_COCOA_COCOA_EVENT_UTILS_H_

#import <Cocoa/Cocoa.h>

#include "ui/events/events_export.h"

namespace ui {

EVENTS_EXPORT int EventFlagsFromModifiers(NSUInteger modifiers);

EVENTS_EXPORT int EventFlagsFromNSEventWithModifiers(NSEvent* event,
                                                     NSUInteger modifiers);
}  

#endif  
