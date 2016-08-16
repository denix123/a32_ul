// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_DEFAULT_STATE_H_
#define ASH_WM_DEFAULT_STATE_H_

#include "ash/wm/window_state.h"
#include "ui/gfx/display.h"

namespace ash {
namespace wm {
class SetBoundsEvent;

class DefaultState : public WindowState::State {
 public:
  explicit DefaultState(WindowStateType initial_state_type);
  virtual ~DefaultState();

  
  virtual void OnWMEvent(WindowState* window_state,
                         const WMEvent* event) OVERRIDE;
  virtual WindowStateType GetType() const OVERRIDE;
  virtual void AttachState(WindowState* window_state,
                           WindowState::State* previous_state) OVERRIDE;
  virtual void DetachState(WindowState* window_state) OVERRIDE;

 private:
  
  
  static bool ProcessCompoundEvents(WindowState* window_state,
                                    const WMEvent* event);

  
  static bool ProcessWorkspaceEvents(WindowState* window_state,
                                     const WMEvent* event);

  
  static bool SetMaximizedOrFullscreenBounds(wm::WindowState* window_state);

  static void SetBounds(WindowState* window_state,
                        const SetBoundsEvent* bounds_event);

  static void CenterWindow(WindowState* window_state);

  
  
  void EnterToNextState(wm::WindowState* window_state,
                        wm::WindowStateType next_state_type);

  
  
  
  void ReenterToCurrentState(wm::WindowState* window_state,
                             wm::WindowState::State* state_in_previous_mode);

  
  void UpdateBoundsFromState(wm::WindowState* window_state,
                             wm::WindowStateType old_state_type);

  
  WindowStateType state_type_;

  
  gfx::Rect stored_bounds_;
  gfx::Rect stored_restore_bounds_;

  
  gfx::Display stored_display_state_;

  
  WindowState* stored_window_state_;

  DISALLOW_COPY_AND_ASSIGN(DefaultState);
};

}  
}  

#endif  
