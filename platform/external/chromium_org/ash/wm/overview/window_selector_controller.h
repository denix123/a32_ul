// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_OVERVIEW_WINDOW_SELECTOR_CONTROLLER_H_
#define ASH_WM_OVERVIEW_WINDOW_SELECTOR_CONTROLLER_H_

#include <list>
#include <vector>

#include "ash/ash_export.h"
#include "ash/wm/overview/window_selector.h"
#include "ash/wm/overview/window_selector_delegate.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "ui/aura/window_observer.h"

namespace aura {
class Window;
}

namespace ash {
class WindowSelector;
class WindowSelectorTest;

class ASH_EXPORT WindowSelectorController
    : public WindowSelectorDelegate {
 public:
  WindowSelectorController();
  virtual ~WindowSelectorController();

  
  
  static bool CanSelect();

  
  
  
  void ToggleOverview();

  
  bool IsSelecting();

  
  virtual void OnSelectionEnded() OVERRIDE;

 private:
  friend class WindowSelectorTest;

  
  void OnSelectionStarted();

  scoped_ptr<WindowSelector> window_selector_;
  base::Time last_selection_time_;

  DISALLOW_COPY_AND_ASSIGN(WindowSelectorController);
};

}  

#endif  
