// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_ACCESSIBILITY_NATIVE_VIEW_ACCESSIBILITY_H_
#define UI_VIEWS_ACCESSIBILITY_NATIVE_VIEW_ACCESSIBILITY_H_

#include "ui/accessibility/ax_node_data.h"
#include "ui/accessibility/platform/ax_platform_node.h"
#include "ui/accessibility/platform/ax_platform_node_delegate.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/views/views_export.h"

namespace views {

class View;

class VIEWS_EXPORT NativeViewAccessibility : public ui::AXPlatformNodeDelegate {
 public:
  static NativeViewAccessibility* Create(View* view);

  virtual gfx::NativeViewAccessible GetNativeObject();

  
  
  virtual void Destroy();

  
  
  
  static void RegisterWebView(View* web_view);
  static void UnregisterWebView(View* web_view);

  
  virtual ui::AXNodeData* GetData() OVERRIDE;
  virtual int GetChildCount() OVERRIDE;
  virtual gfx::NativeViewAccessible ChildAtIndex(int index) OVERRIDE;
  virtual gfx::NativeViewAccessible GetParent() OVERRIDE;
  virtual gfx::Vector2d GetGlobalCoordinateOffset() OVERRIDE;
  virtual void NotifyAccessibilityEvent(ui::AXEvent event_type) OVERRIDE;

 protected:
  NativeViewAccessibility();
  virtual ~NativeViewAccessibility();

  void set_view(views::View* view) { view_ = view; }
  const View* view() const { return view_; }

  View* view_;  

 private:
  
  
  ui::AXPlatformNode* ax_node_;

  ui::AXNodeData data_;

  DISALLOW_COPY_AND_ASSIGN(NativeViewAccessibility);
};

}  

#endif  
