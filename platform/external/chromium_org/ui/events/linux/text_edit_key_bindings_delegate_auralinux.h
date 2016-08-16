// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_X_TEXT_EDIT_KEY_BINDINGS_DELEGATE_X11_H_
#define UI_EVENTS_X_TEXT_EDIT_KEY_BINDINGS_DELEGATE_X11_H_

#include <vector>

#include "ui/events/events_export.h"

namespace ui {
class Event;
class TextEditCommandAuraLinux;

class EVENTS_EXPORT TextEditKeyBindingsDelegateAuraLinux {
 public:
  
  
  
  
  virtual bool MatchEvent(const ui::Event& event,
                          std::vector<TextEditCommandAuraLinux>* commands) = 0;

 protected:
  virtual ~TextEditKeyBindingsDelegateAuraLinux() {}
};

EVENTS_EXPORT void SetTextEditKeyBindingsDelegate(
    TextEditKeyBindingsDelegateAuraLinux* delegate);
EVENTS_EXPORT TextEditKeyBindingsDelegateAuraLinux*
    GetTextEditKeyBindingsDelegate();

}  

#endif  
