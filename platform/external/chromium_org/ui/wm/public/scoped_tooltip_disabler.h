// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_PUBLIC_SCOPED_TOOLTIP_DISABLER_H_
#define UI_WM_PUBLIC_SCOPED_TOOLTIP_DISABLER_H_

#include "ui/aura/window_observer.h"

namespace aura {
namespace client {

class AURA_EXPORT ScopedTooltipDisabler : aura::WindowObserver {
 public:
  
  
  
  explicit ScopedTooltipDisabler(aura::Window* window);
  virtual ~ScopedTooltipDisabler();

 private:
  
  void EnableTooltips();

  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

  
  
  aura::Window* root_;

  DISALLOW_COPY_AND_ASSIGN(ScopedTooltipDisabler);
};

}  
}  

#endif  
