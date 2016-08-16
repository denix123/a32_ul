// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_OZONE_EVDEV_TOUCH_EVENT_CONVERTER_EVDEV_H_
#define UI_EVENTS_OZONE_EVDEV_TOUCH_EVENT_CONVERTER_EVDEV_H_

#include <bitset>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/message_loop/message_pump_libevent.h"
#include "ui/events/event_constants.h"
#include "ui/events/ozone/evdev/event_converter_evdev.h"
#include "ui/events/ozone/evdev/event_device_info.h"
#include "ui/events/ozone/evdev/events_ozone_evdev_export.h"

namespace ui {

class TouchEvent;

class EVENTS_OZONE_EVDEV_EXPORT TouchEventConverterEvdev
    : public EventConverterEvdev {
 public:
  enum {
    MAX_FINGERS = 11
  };
  TouchEventConverterEvdev(int fd,
                           base::FilePath path,
                           const EventDeviceInfo& info,
                           const EventDispatchCallback& dispatch);
  virtual ~TouchEventConverterEvdev();

 private:
  friend class MockTouchEventConverterEvdev;

  
  void Init(const EventDeviceInfo& info);

  
  virtual void OnFileCanReadWithoutBlocking(int fd) OVERRIDE;

  virtual bool Reinitialize();

  void ProcessInputEvent(const input_event& input);
  void ProcessAbs(const input_event& input);
  void ProcessSyn(const input_event& input);

  void ReportEvents(base::TimeDelta delta);

  
  EventDispatchCallback callback_;

  
  bool syn_dropped_;

  
  bool is_type_a_;

  
  int pressure_min_;
  int pressure_max_;  

  
  float x_min_tuxels_;
  float x_num_tuxels_;

  
  float y_min_tuxels_;
  float y_num_tuxels_;

  
  float x_min_pixels_;
  float x_num_pixels_;

  
  float y_min_pixels_;
  float y_num_pixels_;

  
  int current_slot_;

  
  
  std::bitset<MAX_FINGERS> altered_slots_;

  struct InProgressEvents {
    float x_;
    float y_;
    int id_;  
    int finger_;  

    EventType type_;
    float radius_x_;
    float radius_y_;
    float pressure_;
  };

  
  InProgressEvents events_[MAX_FINGERS];

  DISALLOW_COPY_AND_ASSIGN(TouchEventConverterEvdev);
};

}  

#endif  
