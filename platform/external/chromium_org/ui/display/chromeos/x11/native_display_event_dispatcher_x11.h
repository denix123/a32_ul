// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_CHROMEOS_X11_NATIVE_DISPLAY_EVENT_DISPATCHER_X11_H_
#define UI_DISPLAY_CHROMEOS_X11_NATIVE_DISPLAY_EVENT_DISPATCHER_X11_H_

#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "ui/display/chromeos/x11/native_display_delegate_x11.h"
#include "ui/events/platform/platform_event_dispatcher.h"

namespace ui {

class DISPLAY_EXPORT NativeDisplayEventDispatcherX11
    : public ui::PlatformEventDispatcher {
 public:
  NativeDisplayEventDispatcherX11(
      NativeDisplayDelegateX11::HelperDelegate* delegate,
      int xrandr_event_base);
  virtual ~NativeDisplayEventDispatcherX11();

  
  virtual bool CanDispatchEvent(const PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const PlatformEvent& event) OVERRIDE;

  void SetTickClockForTest(scoped_ptr<base::TickClock> tick_clock);

  
  static const int kUseCacheAfterStartupMs;

 private:
  NativeDisplayDelegateX11::HelperDelegate* delegate_;  

  
  
  int xrandr_event_base_;

  base::TimeTicks startup_time_;

  scoped_ptr<base::TickClock> tick_clock_;

  DISALLOW_COPY_AND_ASSIGN(NativeDisplayEventDispatcherX11);
};

}  

#endif  
