// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_LOCK_WINDOW_STATE_H_
#define ASH_WM_LOCK_WINDOW_STATE_H_

#include "ash/wm/window_state.h"

namespace ash {

class LockWindowState : public wm::WindowState::State {
 public:
  
  
  explicit LockWindowState(aura::Window* window);
  virtual ~LockWindowState();

  
  virtual void OnWMEvent(wm::WindowState* window_state,
                         const wm::WMEvent* event) OVERRIDE;
  virtual wm::WindowStateType GetType() const OVERRIDE;
  virtual void AttachState(wm::WindowState* window_state,
                           wm::WindowState::State* previous_state) OVERRIDE;
  virtual void DetachState(wm::WindowState* window_state) OVERRIDE;

  
  static wm::WindowState* SetLockWindowState(aura::Window* window);

 private:
  
  
  
  void UpdateWindow(wm::WindowState* window_state,
                    wm::WindowStateType new_state_type);

  
  
  wm::WindowStateType GetMaximizedOrCenteredWindowType(
      wm::WindowState* window_state);

  
  void UpdateBounds(wm::WindowState* window_state);

  
  
  wm::WindowStateType current_state_type_;

  DISALLOW_COPY_AND_ASSIGN(LockWindowState);
};

}  

#endif  
