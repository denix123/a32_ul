// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_H_

#include "ui/views/controls/menu/menu_runner_impl_interface.h"

#include <set>

#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "ui/views/controls/menu/menu_controller_delegate.h"

namespace views {

class MenuController;
class MenuDelegate;
class MenuItemView;

namespace internal {

class MenuRunnerImpl : public MenuRunnerImplInterface,
                       public MenuControllerDelegate {
 public:
  explicit MenuRunnerImpl(MenuItemView* menu);

  virtual bool IsRunning() const OVERRIDE;
  virtual void Release() OVERRIDE;
  virtual MenuRunner::RunResult RunMenuAt(Widget* parent,
                                          MenuButton* button,
                                          const gfx::Rect& bounds,
                                          MenuAnchorPosition anchor,
                                          int32 run_types) OVERRIDE;
  virtual void Cancel() OVERRIDE;
  virtual base::TimeDelta GetClosingEventTime() const OVERRIDE;

  
  virtual void DropMenuClosed(NotifyType type, MenuItemView* menu) OVERRIDE;
  virtual void SiblingMenuCreated(MenuItemView* menu) OVERRIDE;

 private:
  virtual ~MenuRunnerImpl();

  
  
  MenuRunner::RunResult MenuDone(MenuItemView* result, int mouse_event_flags);

  
  bool ShouldShowMnemonics(MenuButton* button);

  
  
  MenuItemView* menu_;

  
  std::set<MenuItemView*> sibling_menus_;

  
  
  
  
  scoped_ptr<MenuDelegate> empty_delegate_;

  
  bool running_;

  
  bool delete_after_run_;

  
  bool for_drop_;

  
  MenuController* controller_;

  
  bool owns_controller_;

  
  base::TimeDelta closing_event_time_;

  
  base::WeakPtrFactory<MenuRunnerImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MenuRunnerImpl);
};

}  
}  

#endif  
