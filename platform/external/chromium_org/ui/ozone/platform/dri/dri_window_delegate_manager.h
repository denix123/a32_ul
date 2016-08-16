// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_WINDOW_DELEGATE_MANAGER_H_
#define UI_OZONE_PLATFORM_DRI_DRI_WINDOW_DELEGATE_MANAGER_H_

#include "base/containers/scoped_ptr_hash_map.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {

class DriWindowDelegate;

class DriWindowDelegateManager {
 public:
  DriWindowDelegateManager();
  ~DriWindowDelegateManager();

  
  
  void AddWindowDelegate(gfx::AcceleratedWidget widget,
                         scoped_ptr<DriWindowDelegate> surface);

  
  
  scoped_ptr<DriWindowDelegate> RemoveWindowDelegate(
      gfx::AcceleratedWidget widget);

  
  
  DriWindowDelegate* GetWindowDelegate(gfx::AcceleratedWidget widget);

  
  bool HasWindowDelegate(gfx::AcceleratedWidget widget);

 private:
  typedef base::ScopedPtrHashMap<gfx::AcceleratedWidget, DriWindowDelegate>
      WidgetToDelegateMap;

  WidgetToDelegateMap delegate_map_;

  DISALLOW_COPY_AND_ASSIGN(DriWindowDelegateManager);
};

}  

#endif  
