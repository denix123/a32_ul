// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_TEST_TEST_EVENT_HANDLER_H_
#define UI_EVENTS_TEST_TEST_EVENT_HANDLER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/events/event_handler.h"

typedef std::vector<std::string> HandlerSequenceRecorder;

namespace ui {
namespace test {

class TestEventHandler : public EventHandler {
 public:
  TestEventHandler();
  virtual ~TestEventHandler();

  int num_key_events() const { return num_key_events_; }
  int num_mouse_events() const { return num_mouse_events_; }
  int num_scroll_events() const { return num_scroll_events_; }
  int num_touch_events() const { return num_touch_events_; }
  int num_gesture_events() const { return num_gesture_events_; }

  void Reset();

  void set_recorder(HandlerSequenceRecorder* recorder) {
    recorder_ = recorder;
  }
  void set_handler_name(const std::string& handler_name) {
    handler_name_ = handler_name;
  }

  
  virtual void OnKeyEvent(KeyEvent* event) OVERRIDE;
  virtual void OnMouseEvent(MouseEvent* event) OVERRIDE;
  virtual void OnScrollEvent(ScrollEvent* event) OVERRIDE;
  virtual void OnTouchEvent(TouchEvent* event) OVERRIDE;
  virtual void OnGestureEvent(GestureEvent* event) OVERRIDE;

 private:
  
  int num_key_events_;
  int num_mouse_events_;
  int num_scroll_events_;
  int num_touch_events_;
  int num_gesture_events_;

  HandlerSequenceRecorder* recorder_;
  std::string handler_name_;

  DISALLOW_COPY_AND_ASSIGN(TestEventHandler);
};

}  
}  

#endif 
