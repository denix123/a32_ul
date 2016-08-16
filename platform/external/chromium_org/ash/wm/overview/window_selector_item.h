// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_OVERVIEW_WINDOW_SELECTOR_ITEM_H_
#define ASH_WM_OVERVIEW_WINDOW_SELECTOR_ITEM_H_

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/window_observer.h"
#include "ui/gfx/rect.h"
#include "ui/views/controls/button/button.h"

namespace aura {
class Window;
}

namespace views {
class Label;
class Widget;
}

namespace ash {
class TransparentActivateWindowButton;

class WindowSelectorItem : public views::ButtonListener,
                           public aura::WindowObserver {
 public:
  WindowSelectorItem();
  virtual ~WindowSelectorItem();

  
  
  static const int kFadeInMilliseconds;

  
  virtual aura::Window* GetRootWindow() = 0;

  
  
  virtual bool HasSelectableWindow(const aura::Window* window) = 0;

  
  virtual bool Contains(const aura::Window* target) = 0;

  
  
  virtual void RestoreWindowOnExit(aura::Window* window) = 0;

  
  virtual aura::Window* SelectionWindow() = 0;

  
  
  virtual void RemoveWindow(const aura::Window* window);

  
  
  virtual bool empty() const = 0;

  
  
  virtual void PrepareForOverview() = 0;

  
  
  void SetBounds(aura::Window* root_window,
                 const gfx::Rect& target_bounds,
                 bool animate);

  
  
  void RecomputeWindowTransforms();

  
  
  void SendFocusAlert() const;

  
  
  virtual void SetDimmed(bool dimmed);
  bool dimmed() const { return dimmed_; }

  const gfx::Rect& bounds() const { return bounds_; }
  const gfx::Rect& target_bounds() const { return target_bounds_; }

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void OnWindowTitleChanged(aura::Window* window) OVERRIDE;

 protected:
  
  
  
  virtual void SetItemBounds(aura::Window* root_window,
                             const gfx::Rect& target_bounds,
                             bool animate) = 0;

  
  void set_bounds(const gfx::Rect& bounds) { bounds_ = bounds; }

  
  virtual void SetOpacity(float opacity);

  
  
  bool dimmed_;

 private:
  friend class WindowSelectorTest;

  
  
  void UpdateCloseButtonBounds(aura::Window* root_window, bool animate);

  
  void UpdateWindowLabels(const gfx::Rect& target_bounds,
                          aura::Window* root_window,
                          bool animate);

  
  void CreateWindowLabel(const base::string16& title);

  
  aura::Window* root_window_;

  
  gfx::Rect target_bounds_;

  
  
  gfx::Rect bounds_;

  
  
  
  bool in_bounds_update_;

  
  scoped_ptr<views::Widget> window_label_;

  
  views::Label* window_label_view_;

  
  scoped_ptr<views::Widget> close_button_;

  
  
  scoped_ptr<TransparentActivateWindowButton> activate_window_button_;

  DISALLOW_COPY_AND_ASSIGN(WindowSelectorItem);
};

}  

#endif  
