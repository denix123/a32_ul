// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_PLATFORM_AX_PLATFORM_NODE_H_
#define UI_ACCESSIBILITY_PLATFORM_AX_PLATFORM_NODE_H_

#include "ui/accessibility/ax_export.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {

class AXPlatformNodeDelegate;

class AX_EXPORT AXPlatformNode {
 public:
  
  static AXPlatformNode* Create(AXPlatformNodeDelegate* delegate);

  
  
  virtual void Destroy() = 0;

  virtual gfx::NativeViewAccessible GetNativeViewAccessible() = 0;

 protected:
  AXPlatformNode();
  virtual ~AXPlatformNode();
};

}  

#endif  
