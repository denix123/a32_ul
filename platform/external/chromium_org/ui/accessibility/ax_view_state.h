// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_AX_VIEW_STATE_H_
#define UI_ACCESSIBILITY_AX_VIEW_STATE_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/strings/string16.h"
#include "ui/accessibility/ax_enums.h"
#include "ui/accessibility/ax_export.h"

namespace ui {

struct AX_EXPORT AXViewState {
 public:
  AXViewState();
  ~AXViewState();

  
  void AddStateFlag(ui::AXState state);
  bool HasStateFlag(ui::AXState state) const;

  
  
  
  uint32 state() { return state_; }

  
  AXRole role;

  
  base::string16 name;

  
  base::string16 value;

  
  base::string16 default_action;

  
  base::string16 keyboard_shortcut;

  
  
  int selection_start;
  int selection_end;

  
  
  
  int index;
  int count;

  
  
  
  
  
  
  
  
  
  base::Callback<void(const base::string16&)> set_value_callback;

 private:
  uint32 state_;
};

}  

#endif  
