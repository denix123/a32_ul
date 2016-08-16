// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_OZONE_EVDEV_LIBGESTURES_GLUE_EVENT_READER_LIBEVDEV_CROS_H_
#define UI_EVENTS_OZONE_EVDEV_LIBGESTURES_GLUE_EVENT_READER_LIBEVDEV_CROS_H_

#include <libevdev/libevdev.h>

#include "base/files/file_path.h"
#include "base/message_loop/message_loop.h"
#include "ui/events/ozone/evdev/event_converter_evdev.h"

namespace ui {

class EventReaderLibevdevCros : public EventConverterEvdev {
 public:
  class Delegate {
   public:
    virtual ~Delegate();

    
    virtual void OnLibEvdevCrosOpen(Evdev* evdev, EventStateRec* evstate) = 0;

    
    virtual void OnLibEvdevCrosEvent(Evdev* evdev,
                                     EventStateRec* state,
                                     const timeval& time) = 0;
  };

  EventReaderLibevdevCros(int fd,
                          const base::FilePath& path,
                          scoped_ptr<Delegate> delegate);
  ~EventReaderLibevdevCros();

  
  virtual void OnFileCanReadWithoutBlocking(int fd) OVERRIDE;

 private:
  static void OnSynReport(void* data,
                          EventStateRec* evstate,
                          struct timeval* tv);
  static void OnLogMessage(void*, int level, const char*, ...);

  
  Evdev evdev_;

  
  EventStateRec evstate_;

  
  base::FilePath path_;

  
  scoped_ptr<Delegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(EventReaderLibevdevCros);
};

}  

#endif  
