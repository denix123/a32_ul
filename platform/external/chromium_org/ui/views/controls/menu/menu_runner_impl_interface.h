// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_INTERFACE_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_INTERFACE_H_

#include "ui/views/controls/menu/menu_runner.h"

namespace views {

class MenuItemView;

namespace internal {

class MenuRunnerImplInterface {
 public:
  
  
  static MenuRunnerImplInterface* Create(ui::MenuModel* menu_model,
                                         int32 run_types);

  
  virtual bool IsRunning() const = 0;

  
  virtual void Release() = 0;

  
  virtual MenuRunner::RunResult RunMenuAt(Widget* parent,
                                          MenuButton* button,
                                          const gfx::Rect& bounds,
                                          MenuAnchorPosition anchor,
                                          int32 run_types)
      WARN_UNUSED_RESULT = 0;

  
  virtual void Cancel() = 0;

  
  virtual base::TimeDelta GetClosingEventTime() const = 0;

 protected:
  
  virtual ~MenuRunnerImplInterface() {}
};

}  
}  

#endif  
