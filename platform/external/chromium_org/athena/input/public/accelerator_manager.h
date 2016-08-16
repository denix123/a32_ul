// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_INPUT_PUBLIC_ACCELERATOR_MANAGER_H_
#define ATHENA_INPUT_PUBLIC_ACCELERATOR_MANAGER_H_

#include "athena/athena_export.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/keycodes/keyboard_codes.h"

namespace ui {
class Accelerator;
}

namespace views {
class FocusManager;
}

namespace athena {

enum TriggerEvent {
  TRIGGER_ON_PRESS,
  TRIGGER_ON_RELEASE,
};

enum AcceleratorFlags {
  AF_NONE = 0,
  
  
  AF_NON_AUTO_REPEATABLE = 1 << 0,
  
  
  
  AF_RESERVED = 1 << 1,
  
  AF_DEBUG = 1 << 2,
};

struct AcceleratorData {
  
  TriggerEvent trigger_event;
  ui::KeyboardCode keycode;  
  int keyevent_flags;        
  int command_id;            
  int accelerator_flags;     
};

class ATHENA_EXPORT AcceleratorHandler {
 public:
  virtual ~AcceleratorHandler() {}

  virtual bool IsCommandEnabled(int command_id) const = 0;
  virtual bool OnAcceleratorFired(int command_id,
                                  const ui::Accelerator& accelerator) = 0;
};

class ATHENA_EXPORT AcceleratorManager {
 public:
  
  static AcceleratorManager* Get();

  
  
  static scoped_ptr<AcceleratorManager> CreateForFocusManager(
      views::FocusManager* focus_manager);

  virtual ~AcceleratorManager() {}

  
  
  
  virtual bool IsRegistered(const ui::Accelerator& accelerator,
                            int flags) const = 0;

  
  
  virtual void RegisterAccelerators(const AcceleratorData accelerators[],
                                    size_t num_accelerators,
                                    AcceleratorHandler* handler) = 0;

  
  virtual void SetDebugAcceleratorsEnabled(bool enabled) = 0;
};

}  

#endif  
