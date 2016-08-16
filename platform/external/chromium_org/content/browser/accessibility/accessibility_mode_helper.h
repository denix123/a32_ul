// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ACCESSIBILITY_ACCESSIBILITY_MODE_HELPER_H_
#define CONTENT_BROWSER_ACCESSIBILITY_ACCESSIBILITY_MODE_HELPER_H_

#include "content/common/accessibility_mode_enums.h"
#include "content/common/content_export.h"

namespace content {

CONTENT_EXPORT AccessibilityMode GetBaseAccessibilityMode();

CONTENT_EXPORT AccessibilityMode
    AddAccessibilityModeTo(AccessibilityMode to, AccessibilityMode mode_to_add);

CONTENT_EXPORT AccessibilityMode
    RemoveAccessibilityModeFrom(AccessibilityMode to,
                                AccessibilityMode mode_to_remove);

} 

#endif  
