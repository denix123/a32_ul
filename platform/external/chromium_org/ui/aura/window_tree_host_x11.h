// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_WINDOW_TREE_HOST_X11_H_
#define UI_AURA_WINDOW_TREE_HOST_X11_H_

#include "base/memory/scoped_ptr.h"
#include "ui/aura/aura_export.h"
#include "ui/aura/window_tree_host.h"
#include "ui/events/event_source.h"
#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/gfx/insets.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/x/x11_atom_cache.h"

typedef struct _XDisplay XDisplay;
typedef unsigned long XID;
typedef XID Window;

namespace ui {
class MouseEvent;
}

namespace aura {

namespace internal {
class TouchEventCalibrate;
}

class AURA_EXPORT WindowTreeHostX11 : public WindowTreeHost,
                                      public ui::EventSource,
                                      public ui::PlatformEventDispatcher {

 public:
  explicit WindowTreeHostX11(const gfx::Rect& bounds);
  virtual ~WindowTreeHostX11();

  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

  
  virtual ui::EventSource* GetEventSource() OVERRIDE;
  virtual gfx::AcceleratedWidget GetAcceleratedWidget() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual gfx::Rect GetBounds() const OVERRIDE;
  virtual void SetBounds(const gfx::Rect& bounds) OVERRIDE;
  virtual gfx::Point GetLocationOnNativeScreen() const OVERRIDE;
  virtual void SetCapture() OVERRIDE;
  virtual void ReleaseCapture() OVERRIDE;
  virtual void PostNativeEvent(const base::NativeEvent& event) OVERRIDE;
  virtual void SetCursorNative(gfx::NativeCursor cursor_type) OVERRIDE;
  virtual void MoveCursorToNative(const gfx::Point& location) OVERRIDE;
  virtual void OnCursorVisibilityChangedNative(bool show) OVERRIDE;

  
  virtual ui::EventProcessor* GetEventProcessor() OVERRIDE;

 protected:
  
  virtual void OnConfigureNotify();

  
  
  virtual void TranslateAndDispatchLocatedEvent(ui::LocatedEvent* event);

  ::Window x_root_window() { return x_root_window_; }
  XDisplay* xdisplay() { return xdisplay_; }
  const gfx::Rect bounds() const { return bounds_; }
  ui::X11AtomCache* atom_cache() { return &atom_cache_; }

 private:
  
  
  
  void DispatchXI2Event(const base::NativeEvent& event);

  
  
  void SetCursorInternal(gfx::NativeCursor cursor);

  
  XDisplay* xdisplay_;
  ::Window xwindow_;

  
  ::Window x_root_window_;

  
  gfx::NativeCursor current_cursor_;

  
  bool window_mapped_;

  
  gfx::Rect bounds_;

  scoped_ptr<internal::TouchEventCalibrate> touch_calibrate_;

  ui::X11AtomCache atom_cache_;

  DISALLOW_COPY_AND_ASSIGN(WindowTreeHostX11);
};

namespace test {

AURA_EXPORT void SetUseOverrideRedirectWindowByDefault(bool override_redirect);

}  
}  

#endif  
