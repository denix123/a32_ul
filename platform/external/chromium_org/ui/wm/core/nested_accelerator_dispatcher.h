// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_NESTED_ACCELERATOR_DISPATCHER_H_
#define UI_WM_CORE_NESTED_ACCELERATOR_DISPATCHER_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "ui/wm/wm_export.h"

namespace base {
class MessagePumpDispatcher;
class RunLoop;
}

namespace ui {
class KeyEvent;
}

namespace wm {

class NestedAcceleratorDelegate;

class WM_EXPORT NestedAcceleratorDispatcher {
 public:
  virtual ~NestedAcceleratorDispatcher();

  static scoped_ptr<NestedAcceleratorDispatcher> Create(
      NestedAcceleratorDelegate* dispatcher_delegate,
      base::MessagePumpDispatcher* nested_dispatcher);

  
  virtual scoped_ptr<base::RunLoop> CreateRunLoop() = 0;

 protected:
  explicit NestedAcceleratorDispatcher(NestedAcceleratorDelegate* delegate);

  NestedAcceleratorDelegate*
      delegate_;  

 private:
  DISALLOW_COPY_AND_ASSIGN(NestedAcceleratorDispatcher);
};

}  

#endif  
