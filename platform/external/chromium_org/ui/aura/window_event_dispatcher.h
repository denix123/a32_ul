// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_WINDOW_EVENT_DISPATCHER_H_
#define UI_AURA_WINDOW_EVENT_DISPATCHER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/scoped_observer.h"
#include "ui/aura/aura_export.h"
#include "ui/aura/client/capture_delegate.h"
#include "ui/aura/env_observer.h"
#include "ui/aura/window_observer.h"
#include "ui/base/cursor/cursor.h"
#include "ui/events/event_constants.h"
#include "ui/events/event_processor.h"
#include "ui/events/event_targeter.h"
#include "ui/events/gestures/gesture_recognizer.h"
#include "ui/events/gestures/gesture_types.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/point.h"

namespace gfx {
class Size;
class Transform;
}

namespace ui {
class GestureEvent;
class GestureRecognizer;
class KeyEvent;
class MouseEvent;
class ScrollEvent;
class TouchEvent;
}

namespace aura {
class TestScreen;
class WindowTargeter;
class WindowTreeHost;

namespace test {
class WindowEventDispatcherTestApi;
}

class AURA_EXPORT WindowEventDispatcher : public ui::EventProcessor,
                                          public ui::GestureEventHelper,
                                          public client::CaptureDelegate,
                                          public WindowObserver,
                                          public EnvObserver {
 public:
  explicit WindowEventDispatcher(WindowTreeHost* host);
  virtual ~WindowEventDispatcher();

  Window* mouse_pressed_handler() { return mouse_pressed_handler_; }
  Window* mouse_moved_handler() { return mouse_moved_handler_; }

  
  
  
  void RepostEvent(const ui::LocatedEvent& event);

  
  void OnMouseEventsEnableStateChanged(bool enabled);

  void DispatchCancelModeEvent();

  
  
  ui::EventDispatchDetails DispatchMouseExitAtPoint(
      const gfx::Point& point) WARN_UNUSED_RESULT;

  

  
  
  
  
  
  
  
  void ProcessedTouchEvent(ui::TouchEvent* event,
                           Window* window,
                           ui::EventResult result);

  
  
  
  
  
  
  
  void HoldPointerMoves();
  void ReleasePointerMoves();

  
  
  gfx::Point GetLastMouseLocationInRoot() const;

  void OnHostLostMouseGrab();
  void OnCursorMovedToRootLocation(const gfx::Point& root_location);

  
  
  
  
  
  
  
  void OnPostNotifiedWindowDestroying(Window* window);

 private:
  FRIEND_TEST_ALL_PREFIXES(WindowEventDispatcherTest,
                           KeepTranslatedEventInRoot);

  friend class test::WindowEventDispatcherTestApi;
  friend class Window;
  friend class TestScreen;

  
  enum WindowHiddenReason {
    WINDOW_DESTROYED,  
    WINDOW_HIDDEN,     
    WINDOW_MOVING,     
                       
  };

  Window* window();
  const Window* window() const;

  
  
  
  
  
  void TransformEventForDeviceScaleFactor(ui::LocatedEvent* event);

  
  void DispatchMouseExitToHidingWindow(Window* window);

  
  
  ui::EventDispatchDetails DispatchMouseEnterOrExit(
      const ui::MouseEvent& event,
      ui::EventType type) WARN_UNUSED_RESULT;
  ui::EventDispatchDetails ProcessGestures(
      ui::GestureRecognizer::Gestures* gestures) WARN_UNUSED_RESULT;

  
  
  
  
  
  void OnWindowHidden(Window* invisible, WindowHiddenReason reason);

  
  Window* GetGestureTarget(ui::GestureEvent* event);

  
  virtual void UpdateCapture(Window* old_capture, Window* new_capture) OVERRIDE;
  virtual void OnOtherRootGotCapture() OVERRIDE;
  virtual void SetNativeCapture() OVERRIDE;
  virtual void ReleaseNativeCapture() OVERRIDE;

  
  virtual ui::EventTarget* GetRootTarget() OVERRIDE;
  virtual void PrepareEventForDispatch(ui::Event* event) OVERRIDE;

  
  virtual bool CanDispatchToTarget(ui::EventTarget* target) OVERRIDE;
  virtual ui::EventDispatchDetails PreDispatchEvent(ui::EventTarget* target,
                                                    ui::Event* event) OVERRIDE;
  virtual ui::EventDispatchDetails PostDispatchEvent(
      ui::EventTarget* target, const ui::Event& event) OVERRIDE;

  
  virtual bool CanDispatchToConsumer(ui::GestureConsumer* consumer) OVERRIDE;
  virtual void DispatchGestureEvent(ui::GestureEvent* event) OVERRIDE;
  virtual void DispatchCancelTouchEvent(ui::TouchEvent* event) OVERRIDE;

  
  virtual void OnWindowDestroying(Window* window) OVERRIDE;
  virtual void OnWindowDestroyed(Window* window) OVERRIDE;
  virtual void OnWindowAddedToRootWindow(Window* window) OVERRIDE;
  virtual void OnWindowRemovingFromRootWindow(Window* window,
                                              Window* new_root) OVERRIDE;
  virtual void OnWindowVisibilityChanging(Window* window,
                                          bool visible) OVERRIDE;
  virtual void OnWindowVisibilityChanged(Window* window, bool visible) OVERRIDE;
  virtual void OnWindowBoundsChanged(Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) OVERRIDE;
  virtual void OnWindowTransforming(Window* window) OVERRIDE;
  virtual void OnWindowTransformed(Window* window) OVERRIDE;

  
  virtual void OnWindowInitialized(Window* window) OVERRIDE;

  
  
  
  
  
  
  
  ui::EventDispatchDetails DispatchHeldEvents() WARN_UNUSED_RESULT;

  
  
  void PostSynthesizeMouseMove();

  
  
  ui::EventDispatchDetails SynthesizeMouseMoveEvent() WARN_UNUSED_RESULT;

  
  
  void SynthesizeMouseMoveAfterChangeToWindow(Window* window);

  void PreDispatchLocatedEvent(Window* target, ui::LocatedEvent* event);
  void PreDispatchMouseEvent(Window* target, ui::MouseEvent* event);
  void PreDispatchTouchEvent(Window* target, ui::TouchEvent* event);

  WindowTreeHost* host_;

  
  uint32 touch_ids_down_;

  Window* mouse_pressed_handler_;
  Window* mouse_moved_handler_;
  Window* event_dispatch_target_;
  Window* old_dispatch_target_;

  bool synthesize_mouse_move_;

  
  
  int move_hold_count_;
  
  scoped_ptr<ui::LocatedEvent> held_move_event_;

  
  scoped_ptr<ui::LocatedEvent> held_repostable_event_;

  
  bool dispatching_held_event_;

  ScopedObserver<aura::Window, aura::WindowObserver> observer_manager_;

  
  base::WeakPtrFactory<WindowEventDispatcher> repost_event_factory_;

  
  base::WeakPtrFactory<WindowEventDispatcher> held_event_factory_;

  DISALLOW_COPY_AND_ASSIGN(WindowEventDispatcher);
};

}  

#endif  
