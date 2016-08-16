// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_PLATFORM_AX_PLATFORM_NODE_DELEGATE_H_
#define UI_ACCESSIBILITY_PLATFORM_AX_PLATFORM_NODE_DELEGATE_H_

#include "ui/accessibility/ax_enums.h"
#include "ui/accessibility/ax_export.h"
#include "ui/gfx/geometry/vector2d.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {

struct AXNodeData;
class AXPlatformNode;

class AX_EXPORT AXPlatformNodeDelegate {
 public:
  
  virtual AXNodeData* GetData() = 0;

  
  virtual gfx::NativeViewAccessible GetParent() = 0;

  
  virtual int GetChildCount() = 0;

  
  virtual gfx::NativeViewAccessible ChildAtIndex(int index) = 0;

  
  virtual gfx::Vector2d GetGlobalCoordinateOffset() = 0;

  
  
  
  virtual void NotifyAccessibilityEvent(ui::AXEvent event_type) = 0;

};

}  

#endif  
