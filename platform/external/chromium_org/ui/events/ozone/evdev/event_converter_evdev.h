// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_OZONE_EVDEV_EVENT_CONVERTER_EVDEV_H_
#define UI_EVENTS_OZONE_EVDEV_EVENT_CONVERTER_EVDEV_H_

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/message_loop/message_loop.h"
#include "ui/events/ozone/evdev/events_ozone_evdev_export.h"

namespace ui {

class Event;

typedef base::Callback<void(Event*)> EventDispatchCallback;

class EVENTS_OZONE_EVDEV_EXPORT EventConverterEvdev
    : public base::MessagePumpLibevent::Watcher {
 public:
  EventConverterEvdev(int fd, const base::FilePath& path);
  virtual ~EventConverterEvdev();

  
  void Start();

  
  void Stop();

 protected:
  
  virtual void OnFileCanWriteWithoutBlocking(int fd) OVERRIDE;

  
  int fd_;

  
  base::FilePath path_;

  
  base::MessagePumpLibevent::FileDescriptorWatcher controller_;

 private:
  DISALLOW_COPY_AND_ASSIGN(EventConverterEvdev);
};

}  

#endif  
