// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_GLOBAL_SHORTCUT_LISTENER_X11_H_
#define CHROME_BROWSER_EXTENSIONS_GLOBAL_SHORTCUT_LISTENER_X11_H_

#include <X11/Xlib.h>
#include <set>

#include "chrome/browser/extensions/global_shortcut_listener.h"
#include "ui/events/platform/platform_event_dispatcher.h"

namespace extensions {

class GlobalShortcutListenerX11 : public GlobalShortcutListener,
                                  public ui::PlatformEventDispatcher {
 public:
  GlobalShortcutListenerX11();
  virtual ~GlobalShortcutListenerX11();

  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

 private:
  
  virtual void StartListening() OVERRIDE;
  virtual void StopListening() OVERRIDE;
  virtual bool RegisterAcceleratorImpl(
      const ui::Accelerator& accelerator) OVERRIDE;
  virtual void UnregisterAcceleratorImpl(
      const ui::Accelerator& accelerator) OVERRIDE;

  
  void OnXKeyPressEvent(::XEvent* x_event);

  
  bool is_listening_;

  
  ::Display* x_display_;
  ::Window x_root_window_;

  
  typedef std::set<ui::Accelerator> RegisteredHotKeys;
  RegisteredHotKeys registered_hot_keys_;

  DISALLOW_COPY_AND_ASSIGN(GlobalShortcutListenerX11);
};

}  

#endif  
