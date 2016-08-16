// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_UI_ACCESSIBILITY_FOCUS_RING_LAYER_H_
#define CHROME_BROWSER_CHROMEOS_UI_ACCESSIBILITY_FOCUS_RING_LAYER_H_

#include "chrome/browser/chromeos/ui/accessibility_focus_ring.h"
#include "chrome/browser/chromeos/ui/focus_ring_layer.h"

namespace chromeos {

class AccessibilityFocusRingLayer : public FocusRingLayer {
 public:
  explicit AccessibilityFocusRingLayer(FocusRingLayerDelegate* delegate);
  virtual ~AccessibilityFocusRingLayer();

  
  void Set(const AccessibilityFocusRing& ring);

 private:
  
  virtual void OnPaintLayer(gfx::Canvas* canvas) OVERRIDE;

  
  AccessibilityFocusRing ring_;

  DISALLOW_COPY_AND_ASSIGN(AccessibilityFocusRingLayer);
};

}  

#endif  
