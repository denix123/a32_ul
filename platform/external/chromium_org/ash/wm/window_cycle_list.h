// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WINDOW_CYCLE_LIST_H_
#define ASH_WM_WINDOW_CYCLE_LIST_H_

#include <vector>

#include "ash/ash_export.h"
#include "ash/wm/window_cycle_controller.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/window_observer.h"

namespace ash {

class ScopedShowWindow;

class ASH_EXPORT WindowCycleList : public aura::WindowObserver {
 public:
  typedef std::vector<aura::Window*> WindowList;

  explicit WindowCycleList(const WindowList& windows);
  virtual ~WindowCycleList();

  bool empty() const { return windows_.empty(); }

  
  void Step(WindowCycleController::Direction direction);

  const WindowList& windows() const { return windows_; }

 private:
  
  
  
  
  virtual void OnWindowDestroyed(aura::Window* window) OVERRIDE;

  
  
  
  
  WindowList windows_;

  
  int current_index_;

  
  scoped_ptr<ScopedShowWindow> showing_window_;

  DISALLOW_COPY_AND_ASSIGN(WindowCycleList);
};

}  

#endif  
