// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_X11_DESKTOP_HANDLER_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_X11_DESKTOP_HANDLER_H_

#include <X11/Xlib.h>
#undef RootWindow

#include <vector>

#include "ui/aura/env_observer.h"
#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/gfx/x/x11_atom_cache.h"
#include "ui/gfx/x/x11_types.h"
#include "ui/views/views_export.h"

template <typename T> struct DefaultSingletonTraits;

namespace views {

class VIEWS_EXPORT X11DesktopHandler : public ui::PlatformEventDispatcher,
                                       public aura::EnvObserver {
 public:
  
  static X11DesktopHandler* get();

  
  
  int wm_user_time_ms() const {
    return wm_user_time_ms_;
  }
  void set_wm_user_time_ms(unsigned long time_ms) {
    wm_user_time_ms_ = time_ms;
  }

  
  
  void ActivateWindow(::Window window);

  
  
  
  void DeactivateWindow(::Window window);

  
  bool IsActiveWindow(::Window window) const;

  
  
  
  void ProcessXEvent(XEvent* event);

  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

  
  virtual void OnWindowInitialized(aura::Window* window) OVERRIDE;
  virtual void OnWillDestroyEnv() OVERRIDE;

 private:
  enum ActiveState {
    ACTIVE,
    NOT_ACTIVE
  };

  X11DesktopHandler();
  virtual ~X11DesktopHandler();

  
  void OnActiveWindowChanged(::Window window, ActiveState active_state);

  
  
  void OnWindowCreatedOrDestroyed(int event_type, XID window);

  
  XDisplay* xdisplay_;

  
  ::Window x_root_window_;

  
  
  unsigned long wm_user_time_ms_;

  
  ::Window current_window_;

  
  
  ActiveState current_window_active_state_;

  ui::X11AtomCache atom_cache_;

  bool wm_supports_active_window_;

  DISALLOW_COPY_AND_ASSIGN(X11DesktopHandler);
};

}  

#endif  
