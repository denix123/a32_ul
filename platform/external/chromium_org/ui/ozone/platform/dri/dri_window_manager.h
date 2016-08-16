// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_WINDOW_MANAGER_H_
#define UI_OZONE_PLATFORM_DRI_DRI_WINDOW_MANAGER_H_

#include <map>

#include "base/memory/scoped_ptr.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {

class DriCursor;
class DriWindow;
class HardwareCursorDelegate;

class DriWindowManager {
 public:
  explicit DriWindowManager(HardwareCursorDelegate* cursor_delegate);
  ~DriWindowManager();

  gfx::AcceleratedWidget NextAcceleratedWidget();

  
  
  void AddWindow(gfx::AcceleratedWidget widget, DriWindow* window);

  
  
  void RemoveWindow(gfx::AcceleratedWidget widget);

  
  
  DriWindow* GetWindow(gfx::AcceleratedWidget widget);

  DriCursor* cursor() const { return cursor_.get(); }

 private:
  
  void ResetCursorLocation();

  typedef std::map<gfx::AcceleratedWidget, DriWindow*> WidgetToWindowMap;

  gfx::AcceleratedWidget last_allocated_widget_;
  WidgetToWindowMap window_map_;

  scoped_ptr<DriCursor> cursor_;

  DISALLOW_COPY_AND_ASSIGN(DriWindowManager);
};

}  

#endif  
