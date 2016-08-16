// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_WINDOW_TREE_HOST_H_
#define UI_AURA_WINDOW_TREE_HOST_H_

#include <vector>

#include "base/event_types.h"
#include "base/message_loop/message_loop.h"
#include "ui/aura/aura_export.h"
#include "ui/base/cursor/cursor.h"
#include "ui/events/event_source.h"
#include "ui/gfx/native_widget_types.h"

namespace gfx {
class Insets;
class Point;
class Rect;
class Size;
class Transform;
}

namespace ui {
class Compositor;
class EventProcessor;
class ViewProp;
}

namespace aura {
namespace test {
class WindowTreeHostTestApi;
}

class WindowEventDispatcher;
class WindowTreeHostObserver;

class AURA_EXPORT WindowTreeHost {
 public:
  virtual ~WindowTreeHost();

  
  static WindowTreeHost* Create(const gfx::Rect& bounds);

  
  
  static WindowTreeHost* GetForAcceleratedWidget(gfx::AcceleratedWidget widget);

  void InitHost();

  void InitCompositor();

  void AddObserver(WindowTreeHostObserver* observer);
  void RemoveObserver(WindowTreeHostObserver* observer);

  Window* window() { return window_; }
  const Window* window() const { return window_; }

  ui::EventProcessor* event_processor();

  WindowEventDispatcher* dispatcher() {
    return const_cast<WindowEventDispatcher*>(
        const_cast<const WindowTreeHost*>(this)->dispatcher());
  }
  const WindowEventDispatcher* dispatcher() const { return dispatcher_.get(); }

  ui::Compositor* compositor() { return compositor_.get(); }

  
  virtual gfx::Transform GetRootTransform() const;
  virtual void SetRootTransform(const gfx::Transform& transform);
  virtual gfx::Transform GetInverseRootTransform() const;

  
  
  virtual void UpdateRootWindowSize(const gfx::Size& host_size);

  
  
  static gfx::Size GetNativeScreenSize();

  
  
  void ConvertPointToNativeScreen(gfx::Point* point) const;

  
  void ConvertPointFromNativeScreen(gfx::Point* point) const;

  
  
  void ConvertPointToHost(gfx::Point* point) const;

  
  
  void ConvertPointFromHost(gfx::Point* point) const;

  
  
  
  
  
  void SetCursor(gfx::NativeCursor cursor);

  
  void OnCursorVisibilityChanged(bool visible);

  
  void MoveCursorTo(const gfx::Point& location);

  
  void MoveCursorToHostLocation(const gfx::Point& host_location);

  gfx::NativeCursor last_cursor() const { return last_cursor_; }

  
  
  virtual ui::EventSource* GetEventSource() = 0;

  
  virtual gfx::AcceleratedWidget GetAcceleratedWidget() = 0;

  
  virtual void Show() = 0;

  
  virtual void Hide() = 0;

  
  virtual gfx::Rect GetBounds() const = 0;
  virtual void SetBounds(const gfx::Rect& bounds) = 0;

  
  virtual void SetCapture() = 0;

  
  virtual void ReleaseCapture() = 0;

  
  virtual void PostNativeEvent(const base::NativeEvent& native_event) = 0;

 protected:
  friend class TestScreen;  

  WindowTreeHost();
  void DestroyCompositor();
  void DestroyDispatcher();

  void CreateCompositor(gfx::AcceleratedWidget accelerated_widget);

  
  virtual gfx::Point GetLocationOnNativeScreen() const = 0;

  void OnHostMoved(const gfx::Point& new_location);
  void OnHostResized(const gfx::Size& new_size);
  void OnHostCloseRequested();
  void OnHostActivated();
  void OnHostLostWindowCapture();

  
  virtual void SetCursorNative(gfx::NativeCursor cursor) = 0;

  
  virtual void MoveCursorToNative(const gfx::Point& location) = 0;

  
  virtual void OnCursorVisibilityChangedNative(bool show) = 0;

 private:
  friend class test::WindowTreeHostTestApi;

  
  
  void MoveCursorToInternal(const gfx::Point& root_location,
                            const gfx::Point& host_location);

  
  
  
  
  Window* window_;  

  ObserverList<WindowTreeHostObserver> observers_;

  scoped_ptr<WindowEventDispatcher> dispatcher_;

  scoped_ptr<ui::Compositor> compositor_;

  
  gfx::NativeCursor last_cursor_;
  gfx::Point last_cursor_request_position_in_host_;

  scoped_ptr<ui::ViewProp> prop_;

  DISALLOW_COPY_AND_ASSIGN(WindowTreeHost);
};

}  

#endif  
