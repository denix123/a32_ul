// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_ADAPTER_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_ADAPTER_H_

#include "ui/views/controls/menu/menu_runner_impl_interface.h"

namespace views {
namespace internal {

class MenuRunnerImpl;

class MenuRunnerImplAdapter : public MenuRunnerImplInterface {
 public:
  explicit MenuRunnerImplAdapter(ui::MenuModel* menu_model);

  
  virtual bool IsRunning() const OVERRIDE;
  virtual void Release() OVERRIDE;
  virtual MenuRunner::RunResult RunMenuAt(Widget* parent,
                                          MenuButton* button,
                                          const gfx::Rect& bounds,
                                          MenuAnchorPosition anchor,
                                          int32 types) OVERRIDE;
  virtual void Cancel() OVERRIDE;
  virtual base::TimeDelta GetClosingEventTime() const OVERRIDE;

 private:
  virtual ~MenuRunnerImplAdapter();

  scoped_ptr<MenuModelAdapter> menu_model_adapter_;
  MenuRunnerImpl* impl_;

  DISALLOW_COPY_AND_ASSIGN(MenuRunnerImplAdapter);
};

}  
}  

#endif  
