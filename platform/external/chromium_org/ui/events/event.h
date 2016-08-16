// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_EVENT_H_
#define UI_EVENTS_EVENT_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/event_types.h"
#include "base/gtest_prod_util.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "ui/events/event_constants.h"
#include "ui/events/gesture_event_details.h"
#include "ui/events/gestures/gesture_types.h"
#include "ui/events/keycodes/keyboard_codes.h"
#include "ui/events/latency_info.h"
#include "ui/gfx/point.h"
#include "ui/gfx/point_conversions.h"

namespace gfx {
class Transform;
}

namespace ui {
class EventTarget;

class EVENTS_EXPORT Event {
 public:
  static scoped_ptr<Event> Clone(const Event& event);

  virtual ~Event();

  class DispatcherApi {
   public:
    explicit DispatcherApi(Event* event) : event_(event) {}

    void set_target(EventTarget* target) {
      event_->target_ = target;
    }

    void set_phase(EventPhase phase) { event_->phase_ = phase; }
    void set_result(int result) {
      event_->result_ = static_cast<EventResult>(result);
    }

   private:
    DispatcherApi();
    Event* event_;

    DISALLOW_COPY_AND_ASSIGN(DispatcherApi);
  };

  const base::NativeEvent& native_event() const { return native_event_; }
  EventType type() const { return type_; }
  const std::string& name() const { return name_; }
  
  const base::TimeDelta& time_stamp() const { return time_stamp_; }
  int flags() const { return flags_; }

  
  
  void set_flags(int flags) { flags_ = flags; }

  EventTarget* target() const { return target_; }
  EventPhase phase() const { return phase_; }
  EventResult result() const { return result_; }

  LatencyInfo* latency() { return &latency_; }
  const LatencyInfo* latency() const { return &latency_; }
  void set_latency(const LatencyInfo& latency) { latency_ = latency; }

  int source_device_id() const { return source_device_id_; }

  
  
  
  
  bool cancelable() const { return cancelable_; }

  
  
  bool IsShiftDown() const { return (flags_ & EF_SHIFT_DOWN) != 0; }
  bool IsControlDown() const { return (flags_ & EF_CONTROL_DOWN) != 0; }
  bool IsCapsLockDown() const { return (flags_ & EF_CAPS_LOCK_DOWN) != 0; }
  bool IsAltDown() const { return (flags_ & EF_ALT_DOWN) != 0; }
  bool IsAltGrDown() const { return (flags_ & EF_ALTGR_DOWN) != 0; }
  bool IsCommandDown() const { return (flags_ & EF_COMMAND_DOWN) != 0; }
  bool IsRepeat() const { return (flags_ & EF_IS_REPEAT) != 0; }

  bool IsKeyEvent() const {
    return type_ == ET_KEY_PRESSED ||
           type_ == ET_KEY_RELEASED ||
           type_ == ET_TRANSLATED_KEY_PRESS ||
           type_ == ET_TRANSLATED_KEY_RELEASE;
  }

  bool IsMouseEvent() const {
    return type_ == ET_MOUSE_PRESSED ||
           type_ == ET_MOUSE_DRAGGED ||
           type_ == ET_MOUSE_RELEASED ||
           type_ == ET_MOUSE_MOVED ||
           type_ == ET_MOUSE_ENTERED ||
           type_ == ET_MOUSE_EXITED ||
           type_ == ET_MOUSEWHEEL ||
           type_ == ET_MOUSE_CAPTURE_CHANGED;
  }

  bool IsTouchEvent() const {
    return type_ == ET_TOUCH_RELEASED ||
           type_ == ET_TOUCH_PRESSED ||
           type_ == ET_TOUCH_MOVED ||
           type_ == ET_TOUCH_CANCELLED;
  }

  bool IsGestureEvent() const {
    switch (type_) {
      case ET_GESTURE_SCROLL_BEGIN:
      case ET_GESTURE_SCROLL_END:
      case ET_GESTURE_SCROLL_UPDATE:
      case ET_GESTURE_TAP:
      case ET_GESTURE_TAP_CANCEL:
      case ET_GESTURE_TAP_DOWN:
      case ET_GESTURE_BEGIN:
      case ET_GESTURE_END:
      case ET_GESTURE_TWO_FINGER_TAP:
      case ET_GESTURE_PINCH_BEGIN:
      case ET_GESTURE_PINCH_END:
      case ET_GESTURE_PINCH_UPDATE:
      case ET_GESTURE_LONG_PRESS:
      case ET_GESTURE_LONG_TAP:
      case ET_GESTURE_SWIPE:
      case ET_GESTURE_SHOW_PRESS:
      case ET_GESTURE_WIN8_EDGE_SWIPE:
        
        
        return true;

      case ET_SCROLL_FLING_CANCEL:
      case ET_SCROLL_FLING_START:
        
        
        return (flags_ & EF_FROM_TOUCH) == EF_FROM_TOUCH;

      default:
        break;
    }
    return false;
  }

  
  
  bool IsEndingEvent() const {
    switch(type_) {
      case ui::ET_TOUCH_CANCELLED:
      case ui::ET_GESTURE_TAP_CANCEL:
      case ui::ET_GESTURE_END:
      case ui::ET_GESTURE_SCROLL_END:
      case ui::ET_GESTURE_PINCH_END:
        return true;
      default:
        return false;
    }
  }

  bool IsScrollEvent() const {
    
    
    return type_ == ET_SCROLL ||
           ((type_ == ET_SCROLL_FLING_START ||
           type_ == ET_SCROLL_FLING_CANCEL) &&
           !(flags() & EF_FROM_TOUCH));
  }

  bool IsScrollGestureEvent() const {
    return type_ == ET_GESTURE_SCROLL_BEGIN ||
           type_ == ET_GESTURE_SCROLL_UPDATE ||
           type_ == ET_GESTURE_SCROLL_END;
  }

  bool IsFlingScrollEvent() const {
    return type_ == ET_SCROLL_FLING_CANCEL ||
           type_ == ET_SCROLL_FLING_START;
  }

  bool IsMouseWheelEvent() const {
    return type_ == ET_MOUSEWHEEL;
  }

  bool IsLocatedEvent() const {
    return IsMouseEvent() || IsScrollEvent() || IsTouchEvent() ||
           IsGestureEvent();
  }

  
  
  GestureEvent* AsGestureEvent();
  const GestureEvent* AsGestureEvent() const;

  
  bool HasNativeEvent() const;

  
  
  
  
  void StopPropagation();
  bool stopped_propagation() const { return !!(result_ & ER_CONSUMED); }

  
  
  
  
  
  void SetHandled();
  bool handled() const { return result_ != ER_UNHANDLED; }

 protected:
  Event(EventType type, base::TimeDelta time_stamp, int flags);
  Event(const base::NativeEvent& native_event, EventType type, int flags);
  Event(const Event& copy);
  void SetType(EventType type);
  void set_delete_native_event(bool delete_native_event) {
    delete_native_event_ = delete_native_event;
  }
  void set_cancelable(bool cancelable) { cancelable_ = cancelable; }

  void set_time_stamp(const base::TimeDelta& time_stamp) {
    time_stamp_ = time_stamp;
  }

  void set_name(const std::string& name) { name_ = name; }

 private:
  friend class EventTestApi;

  EventType type_;
  std::string name_;
  base::TimeDelta time_stamp_;
  LatencyInfo latency_;
  int flags_;
  base::NativeEvent native_event_;
  bool delete_native_event_;
  bool cancelable_;
  EventTarget* target_;
  EventPhase phase_;
  EventResult result_;

  
  
  int source_device_id_;
};

class EVENTS_EXPORT CancelModeEvent : public Event {
 public:
  CancelModeEvent();
  virtual ~CancelModeEvent();
};

class EVENTS_EXPORT LocatedEvent : public Event {
 public:
  virtual ~LocatedEvent();

  float x() const { return location_.x(); }
  float y() const { return location_.y(); }
  void set_location(const gfx::PointF& location) { location_ = location; }
  
  
  gfx::Point location() const { return gfx::ToFlooredPoint(location_); }
  const gfx::PointF& location_f() const { return location_; }
  void set_root_location(const gfx::PointF& root_location) {
    root_location_ = root_location;
  }
  gfx::Point root_location() const {
    return gfx::ToFlooredPoint(root_location_);
  }
  const gfx::PointF& root_location_f() const {
    return root_location_;
  }

  
  
  virtual void UpdateForRootTransform(
      const gfx::Transform& inverted_root_transform);

  template <class T> void ConvertLocationToTarget(T* source, T* target) {
    if (!target || target == source)
      return;
    
    
    gfx::Point offset = gfx::ToFlooredPoint(location_);
    T::ConvertPointToTarget(source, target, &offset);
    gfx::Vector2d diff = gfx::ToFlooredPoint(location_) - offset;
    location_= location_ - diff;
  }

 protected:
  friend class LocatedEventTestApi;
  explicit LocatedEvent(const base::NativeEvent& native_event);

  
  
  
  template <class T>
  LocatedEvent(const LocatedEvent& model, T* source, T* target)
      : Event(model),
        location_(model.location_),
        root_location_(model.root_location_) {
    ConvertLocationToTarget(source, target);
  }

  
  LocatedEvent(EventType type,
               const gfx::PointF& location,
               const gfx::PointF& root_location,
               base::TimeDelta time_stamp,
               int flags);

  gfx::PointF location_;

  
  
  gfx::PointF root_location_;
};

class EVENTS_EXPORT MouseEvent : public LocatedEvent {
 public:
  explicit MouseEvent(const base::NativeEvent& native_event);

  
  
  
  
  template <class T>
  MouseEvent(const MouseEvent& model, T* source, T* target)
      : LocatedEvent(model, source, target),
        changed_button_flags_(model.changed_button_flags_) {
  }

  template <class T>
  MouseEvent(const MouseEvent& model,
             T* source,
             T* target,
             EventType type,
             int flags)
      : LocatedEvent(model, source, target),
        changed_button_flags_(model.changed_button_flags_) {
    SetType(type);
    set_flags(flags);
  }

  
  MouseEvent(EventType type,
             const gfx::PointF& location,
             const gfx::PointF& root_location,
             int flags,
             int changed_button_flags);

  
  bool IsOnlyLeftMouseButton() const {
    return (flags() & EF_LEFT_MOUSE_BUTTON) &&
      !(flags() & (EF_MIDDLE_MOUSE_BUTTON | EF_RIGHT_MOUSE_BUTTON));
  }

  bool IsLeftMouseButton() const {
    return (flags() & EF_LEFT_MOUSE_BUTTON) != 0;
  }

  bool IsOnlyMiddleMouseButton() const {
    return (flags() & EF_MIDDLE_MOUSE_BUTTON) &&
      !(flags() & (EF_LEFT_MOUSE_BUTTON | EF_RIGHT_MOUSE_BUTTON));
  }

  bool IsMiddleMouseButton() const {
    return (flags() & EF_MIDDLE_MOUSE_BUTTON) != 0;
  }

  bool IsOnlyRightMouseButton() const {
    return (flags() & EF_RIGHT_MOUSE_BUTTON) &&
      !(flags() & (EF_LEFT_MOUSE_BUTTON | EF_MIDDLE_MOUSE_BUTTON));
  }

  bool IsRightMouseButton() const {
    return (flags() & EF_RIGHT_MOUSE_BUTTON) != 0;
  }

  bool IsAnyButton() const {
    return (flags() & (EF_LEFT_MOUSE_BUTTON | EF_MIDDLE_MOUSE_BUTTON |
                       EF_RIGHT_MOUSE_BUTTON)) != 0;
  }

  
  
  static bool IsRepeatedClickEvent(
      const MouseEvent& event1,
      const MouseEvent& event2);

  
  int GetClickCount() const;

  
  void SetClickCount(int click_count);

  
  
  
  
  
  int changed_button_flags() const { return changed_button_flags_; }

  
  void set_changed_button_flags(int flags) { changed_button_flags_ = flags; }

 private:
  FRIEND_TEST_ALL_PREFIXES(EventTest, DoubleClickRequiresRelease);
  FRIEND_TEST_ALL_PREFIXES(EventTest, SingleClickRightLeft);

  
  
  static int GetRepeatCount(const MouseEvent& click_event);

  
  static void ResetLastClickForTest();

  
  int changed_button_flags_;

  static MouseEvent* last_click_event_;

  
  
  
  static bool last_click_complete_;
};

class ScrollEvent;

class EVENTS_EXPORT MouseWheelEvent : public MouseEvent {
 public:
  
  static const int kWheelDelta;

  explicit MouseWheelEvent(const base::NativeEvent& native_event);
  explicit MouseWheelEvent(const ScrollEvent& scroll_event);
  MouseWheelEvent(const MouseEvent& mouse_event, int x_offset, int y_offset);
  MouseWheelEvent(const MouseWheelEvent& mouse_wheel_event);

  template <class T>
  MouseWheelEvent(const MouseWheelEvent& model,
                  T* source,
                  T* target)
      : MouseEvent(model, source, target, model.type(), model.flags()),
        offset_(model.x_offset(), model.y_offset()) {
  }

  
  MouseWheelEvent(const gfx::Vector2d& offset,
                  const gfx::PointF& location,
                  const gfx::PointF& root_location,
                  int flags,
                  int changed_button_flags);

  
  
  int x_offset() const { return offset_.x(); }
  int y_offset() const { return offset_.y(); }
  const gfx::Vector2d& offset() const { return offset_; }

  
  virtual void UpdateForRootTransform(
      const gfx::Transform& inverted_root_transform) OVERRIDE;

 private:
  gfx::Vector2d offset_;
};

class EVENTS_EXPORT TouchEvent : public LocatedEvent {
 public:
  explicit TouchEvent(const base::NativeEvent& native_event);

  
  
  
  template <class T>
  TouchEvent(const TouchEvent& model, T* source, T* target)
      : LocatedEvent(model, source, target),
        touch_id_(model.touch_id_),
        radius_x_(model.radius_x_),
        radius_y_(model.radius_y_),
        rotation_angle_(model.rotation_angle_),
        force_(model.force_) {
  }

  TouchEvent(EventType type,
             const gfx::PointF& location,
             int touch_id,
             base::TimeDelta time_stamp);

  TouchEvent(EventType type,
             const gfx::PointF& location,
             int flags,
             int touch_id,
             base::TimeDelta timestamp,
             float radius_x,
             float radius_y,
             float angle,
             float force);

  virtual ~TouchEvent();

  int touch_id() const { return touch_id_; }
  float radius_x() const { return radius_x_; }
  float radius_y() const { return radius_y_; }
  float rotation_angle() const { return rotation_angle_; }
  float force() const { return force_; }

  
  void set_radius_x(const float r) { radius_x_ = r; }
  void set_radius_y(const float r) { radius_y_ = r; }

  
  virtual void UpdateForRootTransform(
      const gfx::Transform& inverted_root_transform) OVERRIDE;

 protected:
  void set_radius(float radius_x, float radius_y) {
    radius_x_ = radius_x;
    radius_y_ = radius_y;
  }

  void set_rotation_angle(float rotation_angle) {
    rotation_angle_ = rotation_angle;
  }

  void set_force(float force) { force_ = force; }

 private:
  
  
  const int touch_id_;

  
  float radius_x_;

  
  float radius_y_;

  
  float rotation_angle_;

  
  float force_;
};

class EVENTS_EXPORT ExtendedKeyEventData {
 public:
  virtual ~ExtendedKeyEventData() {}

  virtual ExtendedKeyEventData* Clone() const = 0;
};

class EVENTS_EXPORT KeyEvent : public Event {
 public:
  
  
  
  explicit KeyEvent(const base::NativeEvent& native_event);

  
  KeyEvent(EventType type, KeyboardCode key_code, int flags);

  
  KeyEvent(base::char16 character, KeyboardCode key_code, int flags);

  
  
  KeyEvent(EventType type,
           KeyboardCode key_code,
           const std::string& code,
           int flags);

  KeyEvent(const KeyEvent& rhs);

  KeyEvent& operator=(const KeyEvent& rhs);

  virtual ~KeyEvent();

  
  
  
  
  
  
  void SetExtendedKeyEventData(scoped_ptr<ExtendedKeyEventData> data);
  const ExtendedKeyEventData* extended_key_event_data() const {
    return extended_key_event_data_.get();
  }

  
  
  
  
  void set_character(base::char16 character) { character_ = character; }

  
  
  base::char16 GetCharacter() const;

  
  
  base::char16 GetUnmodifiedText() const;

  
  
  
  base::char16 GetText() const;

  
  void set_platform_keycode(uint32 keycode) { platform_keycode_ = keycode; }
  uint32 platform_keycode() const { return platform_keycode_; }

  
  
  
  
  
  KeyboardCode key_code() const { return key_code_; }

  
  bool is_char() const { return is_char_; }

  
  
  void set_key_code(KeyboardCode key_code) { key_code_ = key_code; }

  
  
  
  
  KeyboardCode GetLocatedWindowsKeyboardCode() const;

  
  
  
  uint16 GetConflatedWindowsKeyCode() const;

  
  
  bool IsUnicodeKeyCode() const;

  std::string code() const { return code_; }

  
  
  void NormalizeFlags();

  
  
  bool IsTranslated() const;
  
  void SetTranslated(bool translated);

 protected:
  friend class KeyEventTestApi;

  
  void set_is_char(bool is_char) { is_char_ = is_char; }

 private:
  
  bool IsRightSideKey() const;

  KeyboardCode key_code_;

  
  
  
  
  
  std::string code_;

  
  bool is_char_;

  
  
  uint32 platform_keycode_;

  
  
  
  
  
  
  mutable base::char16 character_;

  
  
  
  
  scoped_ptr<ExtendedKeyEventData> extended_key_event_data_;

  static bool IsRepeated(const KeyEvent& event);

  static KeyEvent* last_key_event_;
};

class EVENTS_EXPORT ScrollEvent : public MouseEvent {
 public:
  explicit ScrollEvent(const base::NativeEvent& native_event);
  template <class T>
  ScrollEvent(const ScrollEvent& model,
              T* source,
              T* target)
      : MouseEvent(model, source, target),
        x_offset_(model.x_offset_),
        y_offset_(model.y_offset_),
        x_offset_ordinal_(model.x_offset_ordinal_),
        y_offset_ordinal_(model.y_offset_ordinal_),
        finger_count_(model.finger_count_){
  }

  
  ScrollEvent(EventType type,
              const gfx::PointF& location,
              base::TimeDelta time_stamp,
              int flags,
              float x_offset,
              float y_offset,
              float x_offset_ordinal,
              float y_offset_ordinal,
              int finger_count);

  
  
  
  void Scale(const float factor);

  float x_offset() const { return x_offset_; }
  float y_offset() const { return y_offset_; }
  float x_offset_ordinal() const { return x_offset_ordinal_; }
  float y_offset_ordinal() const { return y_offset_ordinal_; }
  int finger_count() const { return finger_count_; }

 private:
  
  float x_offset_;
  float y_offset_;
  
  float x_offset_ordinal_;
  float y_offset_ordinal_;
  
  int finger_count_;
};

class EVENTS_EXPORT GestureEvent : public LocatedEvent {
 public:
  GestureEvent(float x,
               float y,
               int flags,
               base::TimeDelta time_stamp,
               const GestureEventDetails& details);

  
  
  
  template <typename T>
  GestureEvent(const GestureEvent& model, T* source, T* target)
      : LocatedEvent(model, source, target),
        details_(model.details_) {
  }

  virtual ~GestureEvent();

  const GestureEventDetails& details() const { return details_; }

 private:
  GestureEventDetails details_;
};

}  

#endif  
