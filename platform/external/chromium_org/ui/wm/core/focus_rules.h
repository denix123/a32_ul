// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_FOCUS_RULES_H_
#define UI_WM_CORE_FOCUS_RULES_H_

#include "ui/wm/wm_export.h"

namespace aura {
class Window;
}

namespace wm {

class WM_EXPORT FocusRules {
 public:
  virtual ~FocusRules() {}

  
  
  
  
  virtual bool IsToplevelWindow(aura::Window* window) const = 0;
  
  virtual bool CanActivateWindow(aura::Window* window) const = 0;
  
  
  virtual bool CanFocusWindow(aura::Window* window) const = 0;

  
  
  
  
  
  virtual aura::Window* GetToplevelWindow(aura::Window* window) const = 0;
  
  
  
  
  
  
  
  
  
  virtual aura::Window* GetActivatableWindow(aura::Window* window) const = 0;
  virtual aura::Window* GetFocusableWindow(aura::Window* window) const = 0;

  
  
  
  
  
  
  
  
  
  virtual aura::Window* GetNextActivatableWindow(
      aura::Window* ignore) const = 0;
};

}  

#endif  
