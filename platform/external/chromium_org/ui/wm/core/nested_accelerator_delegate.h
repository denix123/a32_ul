// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_CORE_NESTED_ACCELERATOR_DELEGATE_H_
#define UI_WM_CORE_NESTED_ACCELERATOR_DELEGATE_H_

namespace ui {
class Accelerator;
}

namespace wm {

class NestedAcceleratorDelegate {
 public:
  enum Result {
    RESULT_PROCESSED,
    RESULT_NOT_PROCESSED,
    
    
    RESULT_PROCESS_LATER,
  };

  virtual ~NestedAcceleratorDelegate() {}

  
  virtual Result ProcessAccelerator(const ui::Accelerator& accelerator) = 0;
};

}  

#endif  
