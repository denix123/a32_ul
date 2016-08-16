// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WIDGET_DESKTOP_AURA_X11_TOPMOST_WINDOW_FINDER_H_
#define UI_VIEWS_WIDGET_DESKTOP_AURA_X11_TOPMOST_WINDOW_FINDER_H_

#include <set>

#include "ui/base/x/x11_util.h"
#include "ui/gfx/point.h"
#include "ui/views/views_export.h"

namespace aura {
class Window;
}

namespace views {

class VIEWS_EXPORT X11TopmostWindowFinder
    : public ui::EnumerateWindowsDelegate {
 public:
  X11TopmostWindowFinder();
  virtual ~X11TopmostWindowFinder();

  
  
  
  aura::Window* FindLocalProcessWindowAt(const gfx::Point& screen_loc,
                                         const std::set<aura::Window*>& ignore);

  
  XID FindWindowAt(const gfx::Point& screen_loc);

 private:
  
  virtual bool ShouldStopIterating(XID xid) OVERRIDE;

  
  
  bool ShouldStopIteratingAtLocalProcessWindow(aura::Window* window);

  gfx::Point screen_loc_;
  std::set<aura::Window*> ignore_;
  XID toplevel_;

  DISALLOW_COPY_AND_ASSIGN(X11TopmostWindowFinder);
};

}  

#endif  
