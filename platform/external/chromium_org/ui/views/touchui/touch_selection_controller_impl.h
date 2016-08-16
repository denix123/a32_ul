// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_UI_VIEWS_TOUCHUI_TOUCH_SELECTION_CONTROLLER_IMPL_H_
#define UI_UI_VIEWS_TOUCHUI_TOUCH_SELECTION_CONTROLLER_IMPL_H_

#include "base/timer/timer.h"
#include "ui/aura/window_observer.h"
#include "ui/base/touch/touch_editing_controller.h"
#include "ui/gfx/point.h"
#include "ui/views/touchui/touch_editing_menu.h"
#include "ui/views/view.h"
#include "ui/views/views_export.h"

namespace views {

namespace test {
class WidgetTestInteractive;
}

class VIEWS_EXPORT TouchSelectionControllerImpl
    : public ui::TouchSelectionController,
      public TouchEditingMenuController,
      public aura::WindowObserver,
      public WidgetObserver,
      public ui::EventHandler {
 public:
  class EditingHandleView;

  
  explicit TouchSelectionControllerImpl(
      ui::TouchEditable* client_view);

  virtual ~TouchSelectionControllerImpl();

  
  virtual void SelectionChanged() OVERRIDE;
  virtual bool IsHandleDragInProgress() OVERRIDE;
  virtual void HideHandles(bool quick) OVERRIDE;

 private:
  friend class TouchSelectionControllerImplTest;
  friend class test::WidgetTestInteractive;

  void SetDraggingHandle(EditingHandleView* handle);

  
  
  void SelectionHandleDragged(const gfx::Point& drag_pos);

  
  
  void ConvertPointToClientView(EditingHandleView* source, gfx::Point* point);

  
  
  void SetHandleSelectionRect(EditingHandleView* handle, const gfx::Rect& rect,
                              const gfx::Rect& rect_in_screen);

  
  
  bool ShouldShowHandleFor(const gfx::Rect& rect) const;

  
  virtual bool IsCommandIdEnabled(int command_id) const OVERRIDE;
  virtual void ExecuteCommand(int command_id, int event_flags) OVERRIDE;
  virtual void OpenContextMenu() OVERRIDE;
  virtual void OnMenuClosed(TouchEditingMenuView* menu) OVERRIDE;

  
  virtual void OnAncestorWindowTransformed(aura::Window* source,
                                           aura::Window* window) OVERRIDE;

  
  
  
  virtual void OnWidgetClosing(Widget* widget) OVERRIDE;
  virtual void OnWidgetBoundsChanged(Widget* widget,
                                     const gfx::Rect& new_bounds) OVERRIDE;

  
  virtual void OnKeyEvent(ui::KeyEvent* event) OVERRIDE;
  virtual void OnMouseEvent(ui::MouseEvent* event) OVERRIDE;
  virtual void OnScrollEvent(ui::ScrollEvent* event) OVERRIDE;

  
  void ContextMenuTimerFired();

  void StartContextMenuTimer();

  
  void UpdateContextMenu();

  
  void HideContextMenu();

  
  gfx::NativeView GetCursorHandleNativeView();
  gfx::Point GetSelectionHandle1Position();
  gfx::Point GetSelectionHandle2Position();
  gfx::Point GetCursorHandlePosition();
  bool IsSelectionHandle1Visible();
  bool IsSelectionHandle2Visible();
  bool IsCursorHandleVisible();

  ui::TouchEditable* client_view_;
  Widget* client_widget_;
  scoped_ptr<EditingHandleView> selection_handle_1_;
  scoped_ptr<EditingHandleView> selection_handle_2_;
  scoped_ptr<EditingHandleView> cursor_handle_;
  TouchEditingMenuView* context_menu_;

  
  
  
  base::OneShotTimer<TouchSelectionControllerImpl> context_menu_timer_;

  
  EditingHandleView* dragging_handle_;

  
  
  
  
  
  gfx::Rect selection_end_point_1_;
  gfx::Rect selection_end_point_2_;
  
  gfx::Rect selection_end_point_1_clipped_;
  gfx::Rect selection_end_point_2_clipped_;

  DISALLOW_COPY_AND_ASSIGN(TouchSelectionControllerImpl);
};

}  

#endif  
