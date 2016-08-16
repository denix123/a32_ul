// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_TEST_EVENT_GENERATOR_H_
#define UI_EVENTS_TEST_EVENT_GENERATOR_H_

#include <list>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "ui/events/event_constants.h"
#include "ui/events/keycodes/keyboard_codes.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/point.h"

namespace base {
class TickClock;
}

namespace ui {
class Event;
class EventProcessor;
class EventSource;
class EventTarget;
class KeyEvent;
class MouseEvent;
class ScrollEvent;
class TouchEvent;

namespace test {

typedef base::Callback<void(EventType, const gfx::Vector2dF&)>
        ScrollStepCallback;

class EventGenerator;

class EventGeneratorDelegate {
 public:
  virtual ~EventGeneratorDelegate() {}

  
  
  virtual void SetContext(EventGenerator* owner,
                          gfx::NativeWindow root_window,
                          gfx::NativeWindow window) {}

  
  virtual EventTarget* GetTargetAt(const gfx::Point& location) = 0;

  
  virtual EventSource* GetEventSource(EventTarget* target) = 0;

  
  virtual gfx::Point CenterOfTarget(const EventTarget* target) const = 0;
  virtual gfx::Point CenterOfWindow(gfx::NativeWindow window) const = 0;

  
  virtual void ConvertPointFromTarget(const EventTarget* target,
                                      gfx::Point* point) const = 0;
  virtual void ConvertPointToTarget(const EventTarget* target,
                                    gfx::Point* point) const = 0;

  
  
  virtual void ConvertPointFromHost(const EventTarget* hosted_target,
                                    gfx::Point* point) const = 0;
};

class EventGenerator {
 public:
  
  
  
  explicit EventGenerator(gfx::NativeWindow root_window);

  
  
  
  explicit EventGenerator(EventGeneratorDelegate* delegate);

  
  
  EventGenerator(gfx::NativeWindow root_window,
                 const gfx::Point& initial_location);

  
  
  
  EventGenerator(gfx::NativeWindow root_window, gfx::NativeWindow window);

  virtual ~EventGenerator();

  
  
  
  void set_current_location(const gfx::Point& location) {
    current_location_ = location;
  }
  const gfx::Point& current_location() const { return current_location_; }

  void set_async(bool async) { async_ = async; }
  bool async() const { return async_; }

  
  void set_flags(int flags) { flags_ = flags; }
  int flags() const { return flags_; }

  
  void PressLeftButton();

  
  void ReleaseLeftButton();

  
  void ClickLeftButton();

  
  void DoubleClickLeftButton();

  
  void PressRightButton();

  
  void ReleaseRightButton();

  
  void MoveMouseWheel(int delta_x, int delta_y);

  
  void SendMouseExit();

  
  
  void MoveMouseToInHost(const gfx::Point& point_in_host);
  void MoveMouseToInHost(int x, int y) {
    MoveMouseToInHost(gfx::Point(x, y));
  }

  
  
  void MoveMouseTo(const gfx::Point& point_in_screen, int count);
  void MoveMouseTo(const gfx::Point& point_in_screen) {
    MoveMouseTo(point_in_screen, 1);
  }
  void MoveMouseTo(int x, int y) {
    MoveMouseTo(gfx::Point(x, y));
  }

  
  
  void MoveMouseRelativeTo(const EventTarget* window, const gfx::Point& point);
  void MoveMouseRelativeTo(const EventTarget* window, int x, int y) {
    MoveMouseRelativeTo(window, gfx::Point(x, y));
  }

  void MoveMouseBy(int x, int y) {
    MoveMouseTo(current_location_ + gfx::Vector2d(x, y));
  }

  
  void DragMouseTo(const gfx::Point& point);

  void DragMouseTo(int x, int y) {
    DragMouseTo(gfx::Point(x, y));
  }

  void DragMouseBy(int dx, int dy) {
    DragMouseTo(current_location_ + gfx::Vector2d(dx, dy));
  }

  
  void MoveMouseToCenterOf(EventTarget* window);

  
  void PressTouch();

  
  void PressTouchId(int touch_id);

  
  void MoveTouch(const gfx::Point& point);

  
  void MoveTouchId(const gfx::Point& point, int touch_id);

  
  void ReleaseTouch();

  
  void ReleaseTouchId(int touch_id);

  
  
  void PressMoveAndReleaseTouchTo(const gfx::Point& point);

  void PressMoveAndReleaseTouchTo(int x, int y) {
    PressMoveAndReleaseTouchTo(gfx::Point(x, y));
  }

  void PressMoveAndReleaseTouchBy(int x, int y) {
    PressMoveAndReleaseTouchTo(current_location_ + gfx::Vector2d(x, y));
  }

  
  
  void PressMoveAndReleaseTouchToCenterOf(EventTarget* window);

  
  
  
  void GestureEdgeSwipe();

  
  
  
  void GestureTapAt(const gfx::Point& point);

  
  
  
  void GestureTapDownAndUp(const gfx::Point& point);

  
  
  
  
  
  void GestureScrollSequence(const gfx::Point& start,
                             const gfx::Point& end,
                             const base::TimeDelta& duration,
                             int steps);

  
  
  
  
  void GestureScrollSequenceWithCallback(const gfx::Point& start,
                                         const gfx::Point& end,
                                         const base::TimeDelta& duration,
                                         int steps,
                                         const ScrollStepCallback& callback);

  
  
  
  
  
  
  
  
  
  void GestureMultiFingerScroll(int count,
                                const gfx::Point start[],
                                int event_separation_time_ms,
                                int steps,
                                int move_x,
                                int move_y);

  
  
  
  
  
  
  
  
  
  
  void GestureMultiFingerScrollWithDelays(int count,
                                          const gfx::Point start[],
                                          const int delay_adding_finger_ms[],
                                          int event_separation_time_ms,
                                          int steps,
                                          int move_x,
                                          int move_y);

  
  
  void ScrollSequence(const gfx::Point& start,
                      const base::TimeDelta& step_delay,
                      float x_offset,
                      float y_offset,
                      int steps,
                      int num_fingers);

  
  
  void ScrollSequence(const gfx::Point& start,
                      const base::TimeDelta& step_delay,
                      const std::vector<gfx::Point>& offsets,
                      int num_fingers);

  
  
  
  
  void PressKey(KeyboardCode key_code, int flags);

  
  
  
  
  void ReleaseKey(KeyboardCode key_code, int flags);

  
  void Dispatch(Event* event);

  void set_current_target(EventTarget* target) {
    current_target_ = target;
  }

  
  void SetTickClock(scoped_ptr<base::TickClock> tick_clock);

  
  base::TimeDelta Now();

  
  static EventGeneratorDelegate* default_delegate;

 private:
  
  void Init(gfx::NativeWindow root_window, gfx::NativeWindow window_context);

  
  void DispatchKeyEvent(bool is_press, KeyboardCode key_code, int flags);

  void UpdateCurrentDispatcher(const gfx::Point& point);
  void PressButton(int flag);
  void ReleaseButton(int flag);

  gfx::Point GetLocationInCurrentRoot() const;
  gfx::Point CenterOfWindow(const EventTarget* window) const;

  void DispatchNextPendingEvent();
  void DoDispatchEvent(Event* event, bool async);

  const EventGeneratorDelegate* delegate() const;
  EventGeneratorDelegate* delegate();

  scoped_ptr<EventGeneratorDelegate> delegate_;
  gfx::Point current_location_;
  EventTarget* current_target_;
  int flags_;
  bool grab_;
  std::list<Event*> pending_events_;
  
  bool async_;
  scoped_ptr<base::TickClock> tick_clock_;

  DISALLOW_COPY_AND_ASSIGN(EventGenerator);
};

}  
}  

#endif  
