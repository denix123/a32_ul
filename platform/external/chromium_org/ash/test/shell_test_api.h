// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_SHELL_TEST_API_H_
#define ASH_TEST_SHELL_TEST_API_H_

#include "base/basictypes.h"

namespace wm {
class InputMethodEventFilter;
}  

namespace ash {
class AppListController;
class AshNativeCursorManager;
class DragDropController;
class MaximizeModeWindowManager;
class RootWindowLayoutManager;
class SessionStateDelegate;
class ScreenPositionController;
class ShelfDelegate;
class ShelfModel;
class Shell;
class SystemGestureEventFilter;
class WorkspaceController;

namespace test {

class ShellTestApi {
public:
  explicit ShellTestApi(Shell* shell);

  RootWindowLayoutManager* root_window_layout();
  ::wm::InputMethodEventFilter* input_method_event_filter();
  SystemGestureEventFilter* system_gesture_event_filter();
  WorkspaceController* workspace_controller();
  ScreenPositionController* screen_position_controller();
  AshNativeCursorManager* ash_native_cursor_manager();
  ShelfModel* shelf_model();
  DragDropController* drag_drop_controller();
  AppListController* app_list_controller();
  MaximizeModeWindowManager* maximize_mode_window_manager();
  void DisableDisplayConfiguratorAnimation();

  
  void SetShelfDelegate(ShelfDelegate* delegate);

  
  void SetSessionStateDelegate(SessionStateDelegate* session_state_delegate);

 private:
  Shell* shell_;  

  DISALLOW_COPY_AND_ASSIGN(ShellTestApi);
};

}  
}  

#endif  
