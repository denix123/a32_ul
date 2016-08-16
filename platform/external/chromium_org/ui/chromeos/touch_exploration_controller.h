// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_CHROMEOS_TOUCH_EXPLORATION_CONTROLLER_H_
#define UI_CHROMEOS_TOUCH_EXPLORATION_CONTROLLER_H_

#include "base/time/tick_clock.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "ui/chromeos/ui_chromeos_export.h"
#include "ui/events/event.h"
#include "ui/events/event_rewriter.h"
#include "ui/events/gesture_detection/gesture_detector.h"
#include "ui/events/gestures/gesture_provider_aura.h"
#include "ui/gfx/geometry/point.h"

namespace aura {
class Window;
}

namespace ui {

class Event;
class EventHandler;
class GestureEvent;
class GestureProviderAura;
class TouchEvent;

class TouchExplorationControllerDelegate {
 public:
  virtual ~TouchExplorationControllerDelegate() {}

  
  
  virtual void SetOutputLevel(int volume) = 0;

  
  virtual void SilenceSpokenFeedback() = 0;

  
  
  virtual void PlayVolumeAdjustEarcon() = 0;

  
  
  virtual void PlayPassthroughEarcon() = 0;

  
  
  virtual void PlayExitScreenEarcon() = 0;

  
  
  virtual void PlayEnterScreenEarcon() = 0;
};

class UI_CHROMEOS_EXPORT TouchExplorationController
    : public ui::EventRewriter,
      public ui::GestureProviderAuraClient {
 public:
  explicit TouchExplorationController(
      aura::Window* root_window,
      ui::TouchExplorationControllerDelegate* delegate);
  virtual ~TouchExplorationController();

 private:
  friend class TouchExplorationControllerTestApi;

  
  virtual ui::EventRewriteStatus RewriteEvent(
      const ui::Event& event,
      scoped_ptr<ui::Event>* rewritten_event) OVERRIDE;
  virtual ui::EventRewriteStatus NextDispatchEvent(
      const ui::Event& last_event, scoped_ptr<ui::Event>* new_event) OVERRIDE;

  
  ui::EventRewriteStatus InNoFingersDown(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InSingleTapPressed(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InSingleTapOrTouchExploreReleased(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InDoubleTapPending(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InTouchReleasePending(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InTouchExploration(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InCornerPassthrough(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InOneFingerPassthrough(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InGestureInProgress(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InTouchExploreSecondPress(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InWaitForNoFingers(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InSlideGesture(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus InTwoFingerTap(
      const ui::TouchEvent& event, scoped_ptr<ui::Event>* rewritten_event);

  
  base::TimeDelta Now();

  
  
  
  
  void StartTapTimer();
  void OnTapTimerFired();

  
  
  
  
  
  void OnPassthroughTimerFired();

  
  void DispatchEvent(ui::Event* event);

  
  
  
  
  
  
  virtual void OnGestureEvent(ui::GestureEvent* gesture) OVERRIDE;

  
  void ProcessGestureEvents();

  void OnSwipeEvent(ui::GestureEvent* swipe_gesture);

  void SideSlideControl(ui::GestureEvent* gesture);

  
  
  void DispatchShiftSearchKeyEvent(const ui::KeyboardCode third_key);

  
  base::Closure BindShiftSearchKeyEvent(const ui::KeyboardCode third_key);

  
  void DispatchKeyWithFlags(const ui::KeyboardCode key, int flags);

  
  base::Closure BindKeyEventWithFlags(const ui::KeyboardCode key, int flags);

  scoped_ptr<ui::Event> CreateMouseMoveEvent(const gfx::PointF& location,
                                             int flags);

  void EnterTouchToMouseMode();

  void PlaySoundForTimer();

  

  
  
  const float kLeavingScreenEdge = 6;

  
  
  const float kMaxDistanceFromEdge = 75;

  
  
  const float kSlopDistanceFromEdge = kMaxDistanceFromEdge + 40;

  
  
  const float GetSplitTapTouchSlop();

  enum State {
    
    NO_FINGERS_DOWN,

    
    
    SINGLE_TAP_PRESSED,

    
    
    
    
    SINGLE_TAP_RELEASED,

    
    
    
    
    
    TOUCH_EXPLORE_RELEASED,

    
    
    
    DOUBLE_TAP_PENDING,

    
    
    
    TOUCH_RELEASE_PENDING,

    
    // is ignored, and movements of the first finger are rewritten as mouse
    
    
    
    
    TOUCH_EXPLORATION,

    
    
    
    
    
    
    
    GESTURE_IN_PROGRESS,

    
    
    
    
    
    
    
    TOUCH_EXPLORE_SECOND_PRESS,

    
    
    
    
    ONE_FINGER_PASSTHROUGH,

    
    
    
    CORNER_PASSTHROUGH,

    
    
    
    
    
    
    WAIT_FOR_NO_FINGERS,

    
    
    
    SLIDE_GESTURE,

    
    
    TWO_FINGER_TAP,
  };

  enum ScreenLocation {
    
    NO_EDGE = 0,
    RIGHT_EDGE = 1 << 0,
    TOP_EDGE = 1 << 1,
    LEFT_EDGE = 1 << 2,
    BOTTOM_EDGE = 1 << 3,
    BOTTOM_LEFT_CORNER = LEFT_EDGE | BOTTOM_EDGE,
    BOTTOM_RIGHT_CORNER = RIGHT_EDGE | BOTTOM_EDGE,
  };

  
  
  
  
  int FindEdgesWithinBounds(gfx::Point point, float bounds);

  
  
  void SetState(State new_state, const char* function_name);

  void VlogState(const char* function_name);

  void VlogEvent(const ui::TouchEvent& event, const char* function_name);

  
  const char* EnumStateToString(State state);

  
  
  void InitializeSwipeGestureMaps();

  aura::Window* root_window_;

  
  ui::TouchExplorationControllerDelegate* delegate_;

  
  std::vector<int> current_touch_ids_;

  
  std::map<int, gfx::PointF> touch_locations_;

  
  State state_;

  
  scoped_ptr<ui::TouchEvent> initial_press_;

  
  
  std::map<int, gfx::Point> initial_presses_;

  
  
  gfx::Vector2d passthrough_offset_;

  
  
  
  scoped_ptr<ui::TouchEvent> last_unused_finger_event_;

  
  
  scoped_ptr<ui::TouchEvent> last_touch_exploration_;

  
  base::OneShotTimer<TouchExplorationController> tap_timer_;

  
  base::OneShotTimer<TouchExplorationController> passthrough_timer_;

  
  base::RepeatingTimer<TouchExplorationController> sound_timer_;

  
  
  ui::GestureDetector::Config gesture_detector_config_;

  
  scoped_ptr<ui::GestureProviderAura> gesture_provider_;

  
  State prev_state_;

  
  scoped_ptr<ui::TouchEvent> prev_event_;

  
  bool VLOG_on_;

  
  
  base::TickClock* tick_clock_;

  
  
  std::map<int, base::Closure> left_swipe_gestures_;
  std::map<int, base::Closure> right_swipe_gestures_;
  std::map<int, base::Closure> up_swipe_gestures_;
  std::map<int, base::Closure> down_swipe_gestures_;

  DISALLOW_COPY_AND_ASSIGN(TouchExplorationController);
};

}  

#endif  
