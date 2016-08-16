// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_SCREEN_X11_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_DESKTOP_SCREEN_X11_H_

#include "base/timer/timer.h"
#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/gfx/display_change_notifier.h"
#include "ui/gfx/screen.h"
#include "ui/views/views_export.h"

namespace gfx {
class Display;
}

typedef unsigned long XID;
typedef XID Window;
typedef struct _XDisplay Display;

namespace views {
class DesktopScreenX11Test;

class VIEWS_EXPORT DesktopScreenX11 : public gfx::Screen,
                                      public ui::PlatformEventDispatcher {
 public:
  DesktopScreenX11();

  virtual ~DesktopScreenX11();

  
  virtual bool IsDIPEnabled() OVERRIDE;
  virtual gfx::Point GetCursorScreenPoint() OVERRIDE;
  virtual gfx::NativeWindow GetWindowUnderCursor() OVERRIDE;
  virtual gfx::NativeWindow GetWindowAtScreenPoint(const gfx::Point& point)
      OVERRIDE;
  virtual int GetNumDisplays() const OVERRIDE;
  virtual std::vector<gfx::Display> GetAllDisplays() const OVERRIDE;
  virtual gfx::Display GetDisplayNearestWindow(
      gfx::NativeView window) const OVERRIDE;
  virtual gfx::Display GetDisplayNearestPoint(
      const gfx::Point& point) const OVERRIDE;
  virtual gfx::Display GetDisplayMatching(
      const gfx::Rect& match_rect) const OVERRIDE;
  virtual gfx::Display GetPrimaryDisplay() const OVERRIDE;
  virtual void AddObserver(gfx::DisplayObserver* observer) OVERRIDE;
  virtual void RemoveObserver(gfx::DisplayObserver* observer) OVERRIDE;

  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

 private:
  friend class DesktopScreenX11Test;

  
  DesktopScreenX11(const std::vector<gfx::Display>& test_displays);

  
  
  std::vector<gfx::Display> BuildDisplaysFromXRandRInfo();

  
  void ConfigureTimerFired();

  Display* xdisplay_;
  ::Window x_root_window_;

  
  bool has_xrandr_;

  
  
  int xrandr_event_base_;

  
  std::vector<gfx::Display> displays_;

  
  
  scoped_ptr<base::OneShotTimer<DesktopScreenX11> > configure_timer_;

  gfx::DisplayChangeNotifier change_notifier_;

  DISALLOW_COPY_AND_ASSIGN(DesktopScreenX11);
};

}  

#endif  