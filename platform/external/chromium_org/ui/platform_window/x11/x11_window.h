// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_PLATFORM_WINDOW_X11_X11_WINDOW_H_
#define UI_PLATFORM_WINDOW_X11_X11_WINDOW_H_

#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/x/x11_atom_cache.h"
#include "ui/platform_window/platform_window.h"
#include "ui/platform_window/platform_window_delegate.h"
#include "ui/platform_window/x11/x11_window_export.h"

typedef struct _XDisplay XDisplay;
typedef unsigned long XID;

namespace ui {

class X11_WINDOW_EXPORT X11Window : public PlatformWindow,
                                    public PlatformEventDispatcher {
 public:
  explicit X11Window(PlatformWindowDelegate* delegate);
  virtual ~X11Window();

 private:
  void Destroy();

  void ProcessXInput2Event(XEvent* xevent);

  
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual void SetBounds(const gfx::Rect& bounds) OVERRIDE;
  virtual gfx::Rect GetBounds() OVERRIDE;
  virtual void SetCapture() OVERRIDE;
  virtual void ReleaseCapture() OVERRIDE;
  virtual void ToggleFullscreen() OVERRIDE;
  virtual void Maximize() OVERRIDE;
  virtual void Minimize() OVERRIDE;
  virtual void Restore() OVERRIDE;
  virtual void SetCursor(PlatformCursor cursor) OVERRIDE;
  virtual void MoveCursorTo(const gfx::Point& location) OVERRIDE;

  
  virtual bool CanDispatchEvent(const PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const PlatformEvent& event) OVERRIDE;

  PlatformWindowDelegate* delegate_;

  XDisplay* xdisplay_;
  XID xwindow_;
  XID xroot_window_;
  X11AtomCache atom_cache_;

  
  
  
  gfx::Rect requested_bounds_;
  gfx::Rect confirmed_bounds_;

  bool window_mapped_;

  DISALLOW_COPY_AND_ASSIGN(X11Window);
};

}  

#endif  