// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_TEST_X11_PROPERTY_CHANGE_WAITER_H_
#define UI_VIEWS_TEST_X11_PROPERTY_CHANGE_WAITER_H_

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/events/platform/platform_event_types.h"
#include "ui/gfx/x/x11_types.h"

namespace ui {
class ScopedEventDispatcher;
class X11AtomCache;
}

namespace views {

class X11PropertyChangeWaiter : public ui::PlatformEventDispatcher {
 public:
  X11PropertyChangeWaiter(XID window, const char* property);
  virtual ~X11PropertyChangeWaiter();

  
  virtual void Wait();

 protected:
  
  virtual bool ShouldKeepOnWaiting(const ui::PlatformEvent& event);

  XID xwindow() const {
    return x_window_;
  }

 private:
  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

  XID x_window_;
  const char* property_;

  
  bool wait_;

  
  base::Closure quit_closure_;

  
  long old_event_mask_;

  scoped_ptr<ui::ScopedEventDispatcher> dispatcher_;

  scoped_ptr<ui::X11AtomCache> atom_cache_;

  DISALLOW_COPY_AND_ASSIGN(X11PropertyChangeWaiter);
};

}  

#endif  
