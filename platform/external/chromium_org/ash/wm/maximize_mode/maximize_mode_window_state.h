// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_MAXIMIZE_MODE_MAXIMIZE_MODE_WINDOW_STATE_H_
#define ASH_WM_MAXIMIZE_MODE_MAXIMIZE_MODE_WINDOW_STATE_H_

#include "ash/wm/window_state.h"

namespace ash {
class MaximizeModeWindowManager;

class MaximizeModeWindowState : public wm::WindowState::State {
 public:
  
  static void UpdateWindowPosition(wm::WindowState* window_state,
                                   bool animated);

  
  
  
  
  MaximizeModeWindowState(aura::Window* window,
                          MaximizeModeWindowManager* creator);
  virtual ~MaximizeModeWindowState();

  
  void LeaveMaximizeMode(wm::WindowState* window_state);

  
  virtual void OnWMEvent(wm::WindowState* window_state,
                         const wm::WMEvent* event) OVERRIDE;

  virtual wm::WindowStateType GetType() const OVERRIDE;
  virtual void AttachState(wm::WindowState* window_state,
                           wm::WindowState::State* previous_state) OVERRIDE;
  virtual void DetachState(wm::WindowState* window_state) OVERRIDE;

 private:
  
  
  
  
  void UpdateWindow(wm::WindowState* window_state,
                    wm::WindowStateType new_state_type,
                    bool animate);

  
  
  wm::WindowStateType GetMaximizedOrCenteredWindowType(
      wm::WindowState* window_state);

  
  
  void UpdateBounds(wm::WindowState* window_state, bool animated);

  
  scoped_ptr<wm::WindowState::State> old_state_;

  
  aura::Window* window_;

  
  MaximizeModeWindowManager* creator_;

  
  
  wm::WindowStateType current_state_type_;

  DISALLOW_COPY_AND_ASSIGN(MaximizeModeWindowState);
};

}  

#endif  
