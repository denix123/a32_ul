// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_SCREEN_PUBLIC_SCREEN_MANAGER_H_
#define ATHENA_SCREEN_PUBLIC_SCREEN_MANAGER_H_

#include <string>

#include "athena/athena_export.h"
#include "ui/gfx/display.h"

namespace aura {
class Window;
}

namespace athena {
class ScreenManagerDelegate;

class ATHENA_EXPORT ScreenManager {
 public:
  struct ContainerParams {
    ContainerParams(const std::string& name, int z_order_priority);
    std::string name;

    
    bool can_activate_children;

    
    bool grab_inputs;

    
    int z_order_priority;
  };

  
  
  static ScreenManager* Create(aura::Window* root);
  static ScreenManager* Get();
  static void Shutdown();

  virtual ~ScreenManager() {}

  
  
  virtual aura::Window* CreateDefaultContainer(
      const ContainerParams& params) = 0;

  
  virtual aura::Window* CreateContainer(const ContainerParams& params) = 0;

  
  virtual aura::Window* GetContext() = 0;

  
  
  
  virtual void SetRotation(gfx::Display::Rotation rotation) = 0;
  virtual void SetRotationLocked(bool rotation_locked) = 0;
};

}  

#endif  
