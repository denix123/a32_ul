// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/macros.h"
#include "ui/events/platform/platform_event_dispatcher.h"

namespace views {

class MenuController;

namespace internal {

class MenuEventDispatcher : public ui::PlatformEventDispatcher {
 public:
  explicit MenuEventDispatcher(MenuController* menu_controller);
  virtual ~MenuEventDispatcher();

 private:
  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

  MenuController* menu_controller_;

  DISALLOW_COPY_AND_ASSIGN(MenuEventDispatcher);
};

}  
}  
