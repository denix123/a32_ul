// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_VIEWS_INPUT_METHOD_MOJO_LINUX_H_
#define MOJO_VIEWS_INPUT_METHOD_MOJO_LINUX_H_

#include "ui/base/ime/input_method_auralinux.h"
#include "ui/base/ime/input_method_delegate.h"

namespace mojo {

class InputMethodMojoLinux : public ui::InputMethodAuraLinux {
 public:
  explicit InputMethodMojoLinux(ui::internal::InputMethodDelegate* delegate);
  virtual ~InputMethodMojoLinux();

  
  virtual bool DispatchKeyEvent(const ui::KeyEvent& event) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(InputMethodMojoLinux);
};

}  

#endif  
