// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_ACCESSIBILITY_BLINK_AX_ENUM_CONVERSION_H_
#define CONTENT_RENDERER_ACCESSIBILITY_BLINK_AX_ENUM_CONVERSION_H_

#include "third_party/WebKit/public/web/WebAXObject.h"
#include "ui/accessibility/ax_enums.h"

namespace content {

ui::AXRole AXRoleFromBlink(blink::WebAXRole role);

ui::AXEvent AXEventFromBlink(blink::WebAXEvent event);

uint32 AXStateFromBlink(const blink::WebAXObject& o);

ui::AXTextDirection AXTextDirectionFromBlink(
    blink::WebAXTextDirection text_direction);

}  

#endif  
