// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_INPUT_ACCELERATOR_MANAGER_H_
#define ATHENA_INPUT_ACCELERATOR_MANAGER_H_

#include "athena/input/public/accelerator_manager.h"

#include <map>

#include "base/macros.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/events/event_target_iterator.h"

namespace aura {
class Window;
}

namespace wm {
class AcceleratorFilter;
class NestedAcceleratorController;
}

namespace athena {

class AcceleratorManagerImpl : public AcceleratorManager,
                               public ui::AcceleratorTarget {
 public:
  class AcceleratorWrapper;

  
  
  static AcceleratorManagerImpl* CreateGlobalAcceleratorManager();

  
  static scoped_ptr<AcceleratorManager> CreateForFocusManager(
      views::FocusManager* focus_manager);

  virtual ~AcceleratorManagerImpl();

  void Init();

  void OnRootWindowCreated(aura::Window* root_window);

  bool Process(const ui::Accelerator& accelerator);

  
  
  virtual bool IsRegistered(const ui::Accelerator& accelerator,
                            int flags) const OVERRIDE;

 private:
  class InternalData;

  explicit AcceleratorManagerImpl(AcceleratorWrapper* wrapper);

  
  virtual void RegisterAccelerators(const AcceleratorData accelerators[],
                                    size_t num_accelerators,
                                    AcceleratorHandler* handler) OVERRIDE;
  virtual void SetDebugAcceleratorsEnabled(bool enabled) OVERRIDE;

  
  virtual bool AcceleratorPressed(const ui::Accelerator& accelerator) OVERRIDE;
  virtual bool CanHandleAccelerators() const OVERRIDE;

  void RegisterAccelerator(const AcceleratorData& accelerator,
                           AcceleratorHandler* handler);

  std::map<ui::Accelerator, InternalData> accelerators_;
  scoped_ptr<AcceleratorWrapper> accelerator_wrapper_;
  scoped_ptr<wm::AcceleratorFilter> accelerator_filter_;
  scoped_ptr<wm::NestedAcceleratorController> nested_accelerator_controller_;
  bool debug_accelerators_enabled_;

  DISALLOW_COPY_AND_ASSIGN(AcceleratorManagerImpl);
};

}  

#endif  
