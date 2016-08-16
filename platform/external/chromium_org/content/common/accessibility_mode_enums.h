// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_ACCESSIBILITY_MODE_ENUMS_H_
#define CONTENT_COMMON_ACCESSIBILITY_MODE_ENUMS_H_

enum AccessibilityModeFlag {
  
  
  AccessibilityModeFlagPlatform = 1 << 0,

  
  
  
  AccessibilityModeFlagFullTree = 1 << 1,
};

enum AccessibilityMode {
  
  AccessibilityModeOff = 0,

  
  
  AccessibilityModeEditableTextOnly = AccessibilityModeFlagPlatform,

  
  AccessibilityModeComplete =
      AccessibilityModeFlagPlatform | AccessibilityModeFlagFullTree,

  
  
  AccessibilityModeTreeOnly = AccessibilityModeFlagFullTree,
};

#endif  
