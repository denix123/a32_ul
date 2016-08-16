// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_OVERVIEW_WINDOW_GRID_H_
#define ASH_WM_OVERVIEW_WINDOW_GRID_H_

#include <vector>

#include "ash/wm/overview/window_selector.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/window_observer.h"

namespace aura {
class Window;
}

namespace views {
class Widget;
}

namespace ash {

class WindowSelectorItem;

class ASH_EXPORT WindowGrid : public aura::WindowObserver {
 public:
  WindowGrid(aura::Window* root_window,
             const std::vector<aura::Window*>& window_list,
             WindowSelector* window_selector);
  virtual ~WindowGrid();

  
  
  void PrepareForOverview();

  
  void PositionWindows(bool animate);

  
  
  
  bool Move(WindowSelector::Direction direction, bool animate);

  
  WindowSelectorItem* SelectedWindow() const;

  
  
  bool Contains(const aura::Window* window) const;

  
  
  
  
  void FilterItems(const base::string16& pattern);

  
  bool empty() const { return window_list_.empty(); }

  
  size_t size() const { return window_list_.size(); }

  
  bool is_selecting() const { return selection_widget_ != NULL; }

  
  const aura::Window* root_window() const { return root_window_; }

  const std::vector<WindowSelectorItem*>& window_list() const {
    return window_list_.get();
  }

  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;
  
  virtual void OnWindowBoundsChanged(aura::Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) OVERRIDE;

 private:
  friend class WindowSelectorTest;

  
  void InitSelectionWidget(WindowSelector::Direction direction);

  
  void MoveSelectionWidget(WindowSelector::Direction direction,
                           bool recreate_selection_widget,
                           bool out_of_bounds,
                           bool animate);

  
  void MoveSelectionWidgetToTarget(bool animate);

  
  const gfx::Rect GetSelectionBounds() const;

  
  aura::Window* root_window_;

  
  WindowSelector* window_selector_;

  
  ScopedVector<WindowSelectorItem> window_list_;

  
  std::set<aura::Window*> observed_windows_;

  
  scoped_ptr<views::Widget> selection_widget_;

  
  size_t selected_index_;

  
  size_t num_columns_;

  DISALLOW_COPY_AND_ASSIGN(WindowGrid);
};

}  

#endif  
