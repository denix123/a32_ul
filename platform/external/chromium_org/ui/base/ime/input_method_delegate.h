// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_IME_INPUT_METHOD_DELEGATE_H_
#define UI_BASE_IME_INPUT_METHOD_DELEGATE_H_

#include "ui/base/ui_base_export.h"

namespace ui {

class KeyEvent;

namespace internal {

class UI_BASE_EXPORT InputMethodDelegate {
 public:
  virtual ~InputMethodDelegate() {}

  
  
  virtual bool DispatchKeyEventPostIME(const ui::KeyEvent& key_event) = 0;
};

}  
}  

#endif  
