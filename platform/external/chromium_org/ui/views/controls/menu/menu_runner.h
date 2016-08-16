// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_RUNNER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/base/ui_base_types.h"
#include "ui/views/controls/menu/menu_types.h"
#include "ui/views/views_export.h"

namespace base {
class TimeDelta;
}

namespace gfx {
class Rect;
}

namespace ui {
class MenuModel;
}

namespace views {

class MenuButton;
class MenuItemView;
class MenuModelAdapter;
class MenuRunnerHandler;
class Widget;

namespace internal {
class DisplayChangeListener;
class MenuRunnerImplInterface;
}

namespace test {
class MenuRunnerTestAPI;
}

class VIEWS_EXPORT MenuRunner {
 public:
  enum RunTypes {
    
    HAS_MNEMONICS = 1 << 0,

    
    
    IS_NESTED     = 1 << 1,

    
    
    
    FOR_DROP      = 1 << 2,

    
    
    CONTEXT_MENU  = 1 << 3,

    
    
    COMBOBOX  = 1 << 4,

    
    
    
    
    NESTED_DRAG = 1 << 5,
  };

  enum RunResult {
    
    MENU_DELETED,

    
    NORMAL_EXIT
  };

  
  
  MenuRunner(ui::MenuModel* menu_model, int32 run_types);
  MenuRunner(MenuItemView* menu, int32 run_types);
  ~MenuRunner();

  
  
  
  
  
  
  RunResult RunMenuAt(Widget* parent,
                      MenuButton* button,
                      const gfx::Rect& bounds,
                      MenuAnchorPosition anchor,
                      ui::MenuSourceType source_type) WARN_UNUSED_RESULT;

  
  bool IsRunning() const;

  
  void Cancel();

  
  base::TimeDelta closing_event_time() const;

 private:
  friend class test::MenuRunnerTestAPI;

  
  void SetRunnerHandler(scoped_ptr<MenuRunnerHandler> runner_handler);

  const int32 run_types_;

  
  internal::MenuRunnerImplInterface* impl_;

  
  
  scoped_ptr<MenuRunnerHandler> runner_handler_;

  scoped_ptr<internal::DisplayChangeListener> display_change_listener_;

  DISALLOW_COPY_AND_ASSIGN(MenuRunner);
};

namespace internal {

class DisplayChangeListener {
 public:
  virtual ~DisplayChangeListener() {}

  
  
  static DisplayChangeListener* Create(Widget* parent,
                                       MenuRunner* runner);

 protected:
  DisplayChangeListener() {}
};

}  

}  

#endif  
