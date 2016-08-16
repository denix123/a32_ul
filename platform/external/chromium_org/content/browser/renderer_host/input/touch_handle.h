// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_HANDLE_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_HANDLE_H_

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "ui/events/gesture_detection/motion_event.h"
#include "ui/gfx/geometry/point_f.h"
#include "ui/gfx/geometry/rect_f.h"
#include "ui/gfx/geometry/vector2d_f.h"

namespace content {

class TouchHandle;

enum TouchHandleOrientation {
  TOUCH_HANDLE_LEFT,
  TOUCH_HANDLE_CENTER,
  TOUCH_HANDLE_RIGHT,
  TOUCH_HANDLE_ORIENTATION_UNDEFINED,
};

class CONTENT_EXPORT TouchHandleDrawable {
 public:
  virtual ~TouchHandleDrawable() {}
  virtual void SetEnabled(bool enabled) = 0;
  virtual void SetOrientation(TouchHandleOrientation orientation) = 0;
  virtual void SetAlpha(float alpha) = 0;
  virtual void SetFocus(const gfx::PointF& position) = 0;
  virtual void SetVisible(bool visible) = 0;
  virtual bool IntersectsWith(const gfx::RectF& rect) const = 0;
};

class CONTENT_EXPORT TouchHandleClient {
 public:
  virtual ~TouchHandleClient() {}
  virtual void OnHandleDragBegin(const TouchHandle& handle) = 0;
  virtual void OnHandleDragUpdate(const TouchHandle& handle,
                                  const gfx::PointF& new_position) = 0;
  virtual void OnHandleDragEnd(const TouchHandle& handle) = 0;
  virtual void OnHandleTapped(const TouchHandle& handle) = 0;
  virtual void SetNeedsAnimate() = 0;
  virtual scoped_ptr<TouchHandleDrawable> CreateDrawable() = 0;
  virtual base::TimeDelta GetTapTimeout() const = 0;
  virtual float GetTapSlop() const = 0;
};

class CONTENT_EXPORT TouchHandle {
 public:
  
  TouchHandle(TouchHandleClient* client, TouchHandleOrientation orientation);
  ~TouchHandle();

  
  
  
  
  
  void SetEnabled(bool enabled);

  enum AnimationStyle { ANIMATION_NONE, ANIMATION_SMOOTH };
  
  
  void SetVisible(bool visible, AnimationStyle animation_style);

  
  
  
  void SetPosition(const gfx::PointF& position);

  
  
  
  void SetOrientation(TouchHandleOrientation orientation);

  
  
  bool WillHandleTouchEvent(const ui::MotionEvent& event);

  
  
  bool Animate(base::TimeTicks frame_time);

  bool is_dragging() const { return is_dragging_; }
  const gfx::PointF& position() const { return position_; }
  TouchHandleOrientation orientation() const { return orientation_; }

 private:
  void BeginDrag();
  void EndDrag();
  void BeginFade();
  void EndFade();
  void SetAlpha(float alpha);

  scoped_ptr<TouchHandleDrawable> drawable_;

  TouchHandleClient* const client_;

  gfx::PointF position_;
  TouchHandleOrientation orientation_;
  TouchHandleOrientation deferred_orientation_;

  gfx::PointF touch_down_position_;
  gfx::Vector2dF touch_to_focus_offset_;
  base::TimeTicks touch_down_time_;

  
  
  
  base::TimeTicks fade_end_time_;
  gfx::PointF fade_start_position_;
  float alpha_;
  bool animate_deferred_fade_;

  bool enabled_;
  bool is_visible_;
  bool is_dragging_;
  bool is_drag_within_tap_region_;

  DISALLOW_COPY_AND_ASSIGN(TouchHandle);
};

}  

#endif  
