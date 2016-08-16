// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DEVICE_UMA_H_
#define CHROME_BROWSER_CHROMEOS_DEVICE_UMA_H_

#include "base/basictypes.h"
#include "ui/events/platform/platform_event_observer.h"

template <typename T> struct DefaultSingletonTraits;

namespace chromeos {

class DeviceUMA : public ui::PlatformEventObserver {
 public:
  
  
  static DeviceUMA* GetInstance();

  void Stop();

 private:
  friend struct DefaultSingletonTraits<DeviceUMA>;

  DeviceUMA();
  virtual ~DeviceUMA();

  
  virtual void WillProcessEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual void DidProcessEvent(const ui::PlatformEvent& event) OVERRIDE;

  
  void CheckTouchpadEvent(XEvent* event);

  
  void CheckIncomingEvent(XEvent* event);

  bool stopped_;

  DISALLOW_COPY_AND_ASSIGN(DeviceUMA);
};

}  

#endif  
