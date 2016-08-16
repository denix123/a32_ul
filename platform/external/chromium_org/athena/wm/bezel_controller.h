// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_WM_BEZEL_CONTROLLER_H_
#define ATHENA_WM_BEZEL_CONTROLLER_H_

#include "ui/events/event_handler.h"

namespace aura {
class Window;
}

namespace gfx {
class PointF;
}

namespace ui {
class EventTarget;
}

namespace athena {

class BezelController : public ui::EventHandler {
 public:
  enum Bezel { BEZEL_NONE, BEZEL_LEFT, BEZEL_RIGHT, BEZEL_TOP, BEZEL_BOTTOM };

  
  
  
  class ScrollDelegate {
   public:
    virtual ~ScrollDelegate() {}

    
    
    
    virtual void BezelScrollBegin(Bezel bezel, float delta) = 0;

    
    virtual void BezelScrollEnd() = 0;

    
    
    virtual void BezelScrollUpdate(float delta) = 0;

    
    
    virtual bool BezelCanScroll() = 0;
  };

  explicit BezelController(aura::Window* container);
  virtual ~BezelController() {}

  
  
  
  void set_left_right_delegate(ScrollDelegate* delegate) {
    left_right_delegate_ = delegate;
  }

 private:
  enum State {
    NONE,
    IGNORE_CURRENT_SCROLL,
    BEZEL_GESTURE_STARTED,
    BEZEL_SCROLLING_ONE_FINGER,
    BEZEL_SCROLLING_TWO_FINGERS,
  };

  void SetState(State state);
  
  
  void SetState(State state, float scroll_delta);

  
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  aura::Window* container_;

  State state_;

  
  Bezel scroll_bezel_;

  
  
  ui::EventTarget* scroll_target_;

  
  
  ScrollDelegate* left_right_delegate_;

  DISALLOW_COPY_AND_ASSIGN(BezelController);
};

}  

#endif  
