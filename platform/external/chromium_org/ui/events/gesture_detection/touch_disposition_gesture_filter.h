// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_TOUCH_DISPOSITION_GESTURE_FILTER_H_
#define UI_EVENTS_GESTURE_DETECTION_TOUCH_DISPOSITION_GESTURE_FILTER_H_

#include <queue>

#include "ui/events/event_constants.h"
#include "ui/events/gesture_detection/bitset_32.h"
#include "ui/events/gesture_detection/gesture_detection_export.h"
#include "ui/events/gesture_detection/gesture_event_data_packet.h"

namespace ui {

class GESTURE_DETECTION_EXPORT TouchDispositionGestureFilterClient {
 public:
  virtual void ForwardGestureEvent(const GestureEventData&) = 0;
};

class GESTURE_DETECTION_EXPORT TouchDispositionGestureFilter {
 public:
  explicit TouchDispositionGestureFilter(
      TouchDispositionGestureFilterClient* client);
  ~TouchDispositionGestureFilter();

  
  
  
  
  
  enum PacketResult {
    SUCCESS,              
    INVALID_PACKET_ORDER, 
                          
    INVALID_PACKET_TYPE,  
  };
  PacketResult OnGesturePacket(const GestureEventDataPacket& packet);

  
  void OnTouchEventAck(bool event_consumed);

  
  bool IsEmpty() const;

 private:
  
  
  
  typedef std::queue<GestureEventDataPacket> GestureSequence;

  
  
  class GestureHandlingState {
   public:
    GestureHandlingState();

    
    void OnTouchEventAck(bool event_consumed, bool is_touch_start_event);

    
    bool Filter(EventType type);

   private:
    
    bool start_touch_consumed_;
    
    bool current_touch_consumed_;
    
    
    BitSet32 last_gesture_of_type_dropped_;
  };

  void FilterAndSendPacket(const GestureEventDataPacket& packet);
  void SendGesture(const GestureEventData& gesture,
                   const GestureEventDataPacket& packet);
  void CancelTapIfNecessary(const GestureEventDataPacket& packet);
  void CancelFlingIfNecessary(const GestureEventDataPacket& packet);
  void EndScrollIfNecessary(const GestureEventDataPacket& packet);
  void PopGestureSequence();
  GestureSequence& Head();
  GestureSequence& Tail();

  TouchDispositionGestureFilterClient* client_;
  std::queue<GestureSequence> sequences_;

  GestureHandlingState state_;

  
  
  
  int ending_event_motion_event_id_;
  MotionEvent::ToolType ending_event_primary_tool_type_;
  bool needs_tap_ending_event_;
  bool needs_show_press_event_;
  bool needs_fling_ending_event_;
  bool needs_scroll_ending_event_;

  DISALLOW_COPY_AND_ASSIGN(TouchDispositionGestureFilter);
};

}  

#endif  
