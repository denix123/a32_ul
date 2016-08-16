// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_OVERSCROLL_CONTROLLER_H_
#define CONTENT_BROWSER_RENDERER_HOST_OVERSCROLL_CONTROLLER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"

namespace ui {
struct LatencyInfo;
}

namespace content {

class RenderWidgetHostViewAuraOverscrollTest;
class OverscrollControllerDelegate;

enum OverscrollMode {
  OVERSCROLL_NONE,
  OVERSCROLL_NORTH,
  OVERSCROLL_SOUTH,
  OVERSCROLL_WEST,
  OVERSCROLL_EAST,
  OVERSCROLL_COUNT
};

class OverscrollController {
 public:
  OverscrollController();
  virtual ~OverscrollController();

  
  
  
  
  bool WillHandleEvent(const blink::WebInputEvent& event);

  
  
  void ReceivedEventACK(const blink::WebInputEvent& event, bool processed);

  
  
  void DiscardingGestureEvent(const blink::WebGestureEvent& event);

  OverscrollMode overscroll_mode() const { return overscroll_mode_; }

  void set_delegate(OverscrollControllerDelegate* delegate) {
    delegate_ = delegate;
  }

  
  void Reset();

  
  
  void Cancel();

 private:
  friend class RenderWidgetHostViewAuraOverscrollTest;

  
  enum ScrollState {
    STATE_UNKNOWN,
    STATE_PENDING,
    STATE_CONTENT_SCROLLING,
    STATE_OVERSCROLLING,
  };

  
  
  bool DispatchEventCompletesAction(
      const blink::WebInputEvent& event) const;

  
  
  bool DispatchEventResetsState(const blink::WebInputEvent& event) const;

  
  
  bool ProcessEventForOverscroll(const blink::WebInputEvent& event);

  
  
  
  
  bool ProcessOverscroll(float delta_x,
                         float delta_y,
                         blink::WebInputEvent::Type event_type);

  
  void CompleteAction();

  
  
  void SetOverscrollMode(OverscrollMode new_mode);

  
  OverscrollMode overscroll_mode_;

  
  
  
  
  
  ScrollState scroll_state_;

  
  
  float overscroll_delta_x_;
  float overscroll_delta_y_;

  
  
  OverscrollControllerDelegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(OverscrollController);
};

}  

#endif  
