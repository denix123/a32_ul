// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_SELECTION_CONTROLLER_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_SELECTION_CONTROLLER_H_

#include "cc/output/viewport_selection_bound.h"
#include "content/browser/renderer_host/input/selection_event_type.h"
#include "content/browser/renderer_host/input/touch_handle.h"
#include "content/common/content_export.h"
#include "ui/gfx/geometry/point_f.h"
#include "ui/gfx/geometry/rect_f.h"

namespace blink {
class WebInputEvent;
}

namespace ui {
class MotionEvent;
}

namespace content {

class CONTENT_EXPORT TouchSelectionControllerClient {
 public:
  virtual ~TouchSelectionControllerClient() {}

  virtual bool SupportsAnimation() const = 0;
  virtual void SetNeedsAnimate() = 0;
  virtual void MoveCaret(const gfx::PointF& position) = 0;
  virtual void SelectBetweenCoordinates(const gfx::PointF& start,
                                        const gfx::PointF& end) = 0;
  virtual void OnSelectionEvent(SelectionEventType event,
                                const gfx::PointF& position) = 0;
  virtual scoped_ptr<TouchHandleDrawable> CreateDrawable() = 0;
};

class CONTENT_EXPORT TouchSelectionController : public TouchHandleClient {
 public:
  TouchSelectionController(TouchSelectionControllerClient* client,
                           base::TimeDelta tap_timeout,
                           float tap_slop);
  virtual ~TouchSelectionController();

  
  
  
  void OnSelectionBoundsChanged(const cc::ViewportSelectionBound& start,
                                const cc::ViewportSelectionBound& end);

  
  
  
  bool WillHandleTouchEvent(const ui::MotionEvent& event);

  
  
  void OnTapEvent();

  
  
  void OnLongPressEvent();

  
  
  void HideAndDisallowShowingAutomatically();

  
  void SetTemporarilyHidden(bool hidden);

  
  void OnSelectionEditable(bool editable);

  
  void OnSelectionEmpty(bool empty);

  
  
  bool Animate(base::TimeTicks animate_time);

 private:
  enum InputEventType { TAP, LONG_PRESS, INPUT_EVENT_TYPE_NONE };

  
  virtual void OnHandleDragBegin(const TouchHandle& handle) OVERRIDE;
  virtual void OnHandleDragUpdate(const TouchHandle& handle,
                                  const gfx::PointF& new_position) OVERRIDE;
  virtual void OnHandleDragEnd(const TouchHandle& handle) OVERRIDE;
  virtual void OnHandleTapped(const TouchHandle& handle) OVERRIDE;
  virtual void SetNeedsAnimate() OVERRIDE;
  virtual scoped_ptr<TouchHandleDrawable> CreateDrawable() OVERRIDE;
  virtual base::TimeDelta GetTapTimeout() const OVERRIDE;
  virtual float GetTapSlop() const OVERRIDE;

  void ShowInsertionHandleAutomatically();
  void ShowSelectionHandlesAutomatically();

  void OnInsertionChanged();
  void OnSelectionChanged();

  void ActivateInsertion();
  void DeactivateInsertion();
  void ActivateSelection();
  void DeactivateSelection();
  void ResetCachedValuesIfInactive();

  const gfx::PointF& GetStartPosition() const;
  const gfx::PointF& GetEndPosition() const;
  gfx::Vector2dF GetStartLineOffset() const;
  gfx::Vector2dF GetEndLineOffset() const;
  bool GetStartVisible() const;
  bool GetEndVisible() const;
  TouchHandle::AnimationStyle GetAnimationStyle(bool was_active) const;

  TouchSelectionControllerClient* const client_;
  const base::TimeDelta tap_timeout_;
  const float tap_slop_;

  InputEventType response_pending_input_event_;

  cc::ViewportSelectionBound start_;
  cc::ViewportSelectionBound end_;
  TouchHandleOrientation start_orientation_;
  TouchHandleOrientation end_orientation_;

  scoped_ptr<TouchHandle> insertion_handle_;
  bool is_insertion_active_;
  bool activate_insertion_automatically_;

  scoped_ptr<TouchHandle> start_selection_handle_;
  scoped_ptr<TouchHandle> end_selection_handle_;
  gfx::PointF fixed_handle_position_;
  bool is_selection_active_;
  bool activate_selection_automatically_;

  bool selection_empty_;
  bool selection_editable_;

  bool temporarily_hidden_;

  DISALLOW_COPY_AND_ASSIGN(TouchSelectionController);
};

}  

#endif  
