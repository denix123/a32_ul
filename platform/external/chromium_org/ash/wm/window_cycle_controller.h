// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_WINDOW_CYCLE_CONTROLLER_H_
#define ASH_WM_WINDOW_CYCLE_CONTROLLER_H_

#include "ash/ash_export.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"

namespace ui {
class EventHandler;
}

namespace ash {

class WindowCycleList;

class ASH_EXPORT WindowCycleController {
 public:
  enum Direction {
    FORWARD,
    BACKWARD
  };

  WindowCycleController();
  virtual ~WindowCycleController();

  
  
  static bool CanCycle();

  
  void HandleCycleWindow(Direction direction);

  
  bool IsCycling() const { return window_cycle_list_.get() != NULL; }

  
  
  void StartCycling();

  
  void StopCycling();

  
  const WindowCycleList* window_cycle_list() const {
    return window_cycle_list_.get();
  }

 private:
  
  void Step(Direction direction);

  scoped_ptr<WindowCycleList> window_cycle_list_;

  
  scoped_ptr<ui::EventHandler> event_handler_;

  base::Time cycle_start_time_;

  DISALLOW_COPY_AND_ASSIGN(WindowCycleController);
};

}  

#endif  
