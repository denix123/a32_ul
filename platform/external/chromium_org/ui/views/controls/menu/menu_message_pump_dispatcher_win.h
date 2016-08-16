// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_MENU_MENU_MESSAGE_PUMP_DISPATCHER_WIN_H_
#define UI_VIEWS_CONTROLS_MENU_MENU_MESSAGE_PUMP_DISPATCHER_WIN_H_

#include "base/macros.h"
#include "base/message_loop/message_pump_dispatcher.h"

namespace views {

class MenuController;

namespace internal {

class MenuMessagePumpDispatcher : public base::MessagePumpDispatcher {
 public:
  explicit MenuMessagePumpDispatcher(MenuController* menu_controller);
  virtual ~MenuMessagePumpDispatcher();

 private:
  
  virtual uint32_t Dispatch(const base::NativeEvent& event) OVERRIDE;

  MenuController* menu_controller_;

  DISALLOW_COPY_AND_ASSIGN(MenuMessagePumpDispatcher);
};

}  
}  

#endif  
