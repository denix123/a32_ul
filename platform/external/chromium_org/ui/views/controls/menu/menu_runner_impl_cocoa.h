// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_COCOA_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_IMPL_COCOA_H_

#include "ui/views/controls/menu/menu_runner_impl_interface.h"

#import "base/mac/scoped_nsobject.h"
#include "base/time/time.h"

@class MenuController;

namespace views {
namespace internal {

class VIEWS_EXPORT MenuRunnerImplCocoa : public MenuRunnerImplInterface {
 public:
  explicit MenuRunnerImplCocoa(ui::MenuModel* menu);

  virtual bool IsRunning() const OVERRIDE;
  virtual void Release() OVERRIDE;
  virtual MenuRunner::RunResult RunMenuAt(Widget* parent,
                                          MenuButton* button,
                                          const gfx::Rect& bounds,
                                          MenuAnchorPosition anchor,
                                          int32 run_types) OVERRIDE;
  virtual void Cancel() OVERRIDE;
  virtual base::TimeDelta GetClosingEventTime() const OVERRIDE;

 private:
  virtual ~MenuRunnerImplCocoa();

  
  base::scoped_nsobject<MenuController> menu_controller_;

  
  bool delete_after_run_;

  
  base::TimeDelta closing_event_time_;

  DISALLOW_COPY_AND_ASSIGN(MenuRunnerImplCocoa);
};

}  
}  

#endif  
