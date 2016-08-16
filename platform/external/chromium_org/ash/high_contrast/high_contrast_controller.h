// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_HIGH_CONTRAST_HIGH_CONTRAST_CONTROLLER_H_
#define ASH_HIGH_CONTRAST_HIGH_CONTRAST_CONTROLLER_H_

#include "ash/ash_export.h"
#include "ash/shell_observer.h"
#include "base/basictypes.h"

namespace aura {
class Window;
}

namespace ash {

class ASH_EXPORT HighContrastController : public ShellObserver {
 public:
  HighContrastController();
  virtual ~HighContrastController();

  
  void SetEnabled(bool enabled);

  
  virtual void OnRootWindowAdded(aura::Window* root_window) OVERRIDE;

 private:
  
  void UpdateDisplay(aura::Window* root_window);

  
  bool enabled_;

  DISALLOW_COPY_AND_ASSIGN(HighContrastController);
};

}  

#endif  
