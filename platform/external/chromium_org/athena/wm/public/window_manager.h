// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_SCREEN_PUBLIC_WINDOW_MANAGER_H_
#define ATHENA_SCREEN_PUBLIC_WINDOW_MANAGER_H_

#include "athena/athena_export.h"

namespace athena {

class WindowListProvider;
class WindowManagerObserver;

class ATHENA_EXPORT WindowManager {
 public:
  
  
  static WindowManager* Create();
  static void Shutdown();
  static WindowManager* Get();

  virtual ~WindowManager() {}

  virtual void ToggleOverview() = 0;

  virtual bool IsOverviewModeActive() = 0;

  virtual void AddObserver(WindowManagerObserver* observer) = 0;
  virtual void RemoveObserver(WindowManagerObserver* observer) = 0;

  virtual void ToggleSplitViewForTest() = 0;

  
  
  virtual WindowListProvider* GetWindowListProvider() = 0;
};

}  

#endif  
