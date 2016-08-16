// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_UI_ACCESSIBILITY_FOCUS_RING_H_
#define CHROME_BROWSER_CHROMEOS_UI_ACCESSIBILITY_FOCUS_RING_H_

#include "ui/gfx/point.h"
#include "ui/gfx/rect.h"

namespace chromeos {


struct AccessibilityFocusRing {
  
  static AccessibilityFocusRing CreateWithRect(
      const gfx::Rect& bounds, int margin);

  
  
  static AccessibilityFocusRing Interpolate(
      const AccessibilityFocusRing& r1,
      const AccessibilityFocusRing& r2,
      double fraction);

  
  
  static AccessibilityFocusRing CreateWithParagraphShape(
      const gfx::Rect& top_line,
      const gfx::Rect& body,
      const gfx::Rect& bottom_line,
      int margin);

  gfx::Rect GetBounds() const;

  gfx::Point points[36];
};

}  

#endif  
