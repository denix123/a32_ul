// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_OVERVIEW_WINDOW_SELECTOR_H_
#define ASH_WM_OVERVIEW_WINDOW_SELECTOR_H_

#include <set>
#include <vector>

#include "ash/ash_export.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"
#include "ui/aura/window_observer.h"
#include "ui/aura/window_tracker.h"
#include "ui/events/event_handler.h"
#include "ui/gfx/display_observer.h"
#include "ui/views/controls/textfield/textfield_controller.h"
#include "ui/wm/public/activation_change_observer.h"

namespace aura {
class RootWindow;
class Window;
}

namespace gfx {
class Rect;
}

namespace ui {
class LocatedEvent;
}

namespace views {
class Textfield;
class Widget;
}

namespace ash {
class WindowSelectorDelegate;
class WindowSelectorItem;
class WindowSelectorTest;
class WindowGrid;

class ASH_EXPORT WindowSelector
    : public gfx::DisplayObserver,
      public aura::WindowObserver,
      public aura::client::ActivationChangeObserver,
      public views::TextfieldController {
 public:
  
  
  static const int kTextFilterBottomEdge;

  enum Direction {
    LEFT,
    UP,
    RIGHT,
    DOWN
  };

  typedef std::vector<aura::Window*> WindowList;
  typedef ScopedVector<WindowSelectorItem> WindowSelectorItemList;

  WindowSelector(const WindowList& windows,
                 WindowSelectorDelegate* delegate);
  virtual ~WindowSelector();

  
  void CancelSelection();

  
  void OnGridEmpty(WindowGrid* grid);

  
  virtual void OnDisplayAdded(const gfx::Display& display) OVERRIDE;
  virtual void OnDisplayRemoved(const gfx::Display& display) OVERRIDE;
  virtual void OnDisplayMetricsChanged(const gfx::Display& display,
                                       uint32_t metrics) OVERRIDE;

  
  virtual void OnWindowAdded(aura::Window* new_window) OVERRIDE;
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

  
  virtual void OnWindowActivated(aura::Window* gained_active,
                                 aura::Window* lost_active) OVERRIDE;
  virtual void OnAttemptToReactivateWindow(
      aura::Window* request_active,
      aura::Window* actual_active) OVERRIDE;

  
  virtual void ContentsChanged(views::Textfield* sender,
                               const base::string16& new_contents) OVERRIDE;
  virtual bool HandleKeyEvent(views::Textfield* sender,
                              const ui::KeyEvent& key_event) OVERRIDE;

 private:
  friend class WindowSelectorTest;

  
  void StartOverview();

  
  void PositionWindows(bool animate);

  
  void HideAndTrackNonOverviewWindows();

  
  void ResetFocusRestoreWindow(bool focus);

  
  
  void Move(Direction direction, bool animate);

  
  std::set<aura::Window*> observed_windows_;

  
  
  WindowSelectorDelegate* delegate_;

  
  
  
  aura::Window* restore_focus_window_;

  
  
  bool ignore_activations_;

  
  ScopedVector<WindowGrid> grid_list_;

  
  
  aura::WindowTracker hidden_windows_;

  
  size_t selected_grid_index_;

  
  
  
  base::Time overview_start_time_;

  
  size_t num_key_presses_;

  
  size_t num_items_;

  
  bool showing_selection_widget_;

  
  
  
  scoped_ptr<views::Widget> text_filter_widget_;

  
  size_t text_filter_string_length_;

  
  
  size_t num_times_textfield_cleared_;

  DISALLOW_COPY_AND_ASSIGN(WindowSelector);
};

}  

#endif  
