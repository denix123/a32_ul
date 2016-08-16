// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_EMULATOR_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_EMULATOR_H_

#include "content/browser/renderer_host/input/touch_emulator_client.h"
#include "content/common/cursors/webcursor.h"
#include "content/common/input/input_event_ack_state.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "ui/events/gesture_detection/filtered_gesture_provider.h"
#include "ui/gfx/size_f.h"

namespace content {

class CONTENT_EXPORT TouchEmulator : public ui::GestureProviderClient {
 public:
  explicit TouchEmulator(TouchEmulatorClient* client);
  virtual ~TouchEmulator();

  void Enable();
  void Disable();

  
  
  bool enabled() const { return enabled_; }

  
  
  
  bool HandleMouseEvent(const blink::WebMouseEvent& event);
  bool HandleMouseWheelEvent(const blink::WebMouseWheelEvent& event);
  bool HandleKeyboardEvent(const blink::WebKeyboardEvent& event);
  bool HandleTouchEvent(const blink::WebTouchEvent& event);

  
  
  bool HandleTouchEventAck(const blink::WebTouchEvent& event,
                           InputEventAckState ack_result);

  
  void CancelTouch();

 private:
  
  virtual void OnGestureEvent(const ui::GestureEventData& gesture) OVERRIDE;

  
  gfx::SizeF InitCursorFromResource(
      WebCursor* cursor, float scale, int resource_id);
  void ResetState();
  void UpdateCursor();
  bool UpdateShiftPressed(bool shift_pressed);

  
  bool InPinchGestureMode() const;

  bool FillTouchEventAndPoint(const blink::WebMouseEvent& mouse_event);
  void FillPinchEvent(const blink::WebInputEvent& event);

  
  void PinchBegin(const blink::WebGestureEvent& event);
  void PinchUpdate(const blink::WebGestureEvent& event);
  void PinchEnd(const blink::WebGestureEvent& event);
  void ScrollEnd(const blink::WebGestureEvent& event);

  void ForwardTouchEventToClient();

  TouchEmulatorClient* const client_;
  ui::FilteredGestureProvider gesture_provider_;

  
  
  bool enabled_;

  
  
  WebCursor pointer_cursor_;
  WebCursor touch_cursor_;
  WebCursor pinch_cursor_;
  gfx::SizeF cursor_size_;

  
  
  bool last_mouse_event_was_move_;
  double last_mouse_move_timestamp_;

  bool mouse_pressed_;
  bool shift_pressed_;

  blink::WebTouchEvent touch_event_;
  int emulated_stream_active_sequence_count_;
  int native_stream_active_sequence_count_;

  
  
  bool suppress_next_fling_cancel_;

  blink::WebGestureEvent pinch_event_;
  
  gfx::Point pinch_anchor_;
  
  float pinch_scale_;
  bool pinch_gesture_active_;

  DISALLOW_COPY_AND_ASSIGN(TouchEmulator);
};

}  

#endif  
