// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_OZONE_EVDEV_EVENT_FACTORY_EVDEV_H_
#define UI_EVENTS_OZONE_EVDEV_EVENT_FACTORY_EVDEV_H_

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/task_runner.h"
#include "ui/events/ozone/device/device_event_observer.h"
#include "ui/events/ozone/evdev/event_converter_evdev.h"
#include "ui/events/ozone/evdev/event_modifiers_evdev.h"
#include "ui/events/ozone/evdev/events_ozone_evdev_export.h"
#include "ui/events/platform/platform_event_source.h"
#include "ui/gfx/native_widget_types.h"

namespace gfx {
class PointF;
}  

namespace ui {

class CursorDelegateEvdev;
class DeviceManager;

class EVENTS_OZONE_EVDEV_EXPORT EventFactoryEvdev : public DeviceEventObserver,
                                                    public PlatformEventSource {
 public:
  EventFactoryEvdev(CursorDelegateEvdev* cursor,
                    DeviceManager* device_manager);
  virtual ~EventFactoryEvdev();

  void DispatchUiEvent(Event* event);

  void WarpCursorTo(gfx::AcceleratedWidget widget,
                    const gfx::PointF& location);

 private:
  
  void AttachInputDevice(const base::FilePath& file_path,
                         scoped_ptr<EventConverterEvdev> converter);

  
  void DetachInputDevice(const base::FilePath& file_path);

  
  
  
  virtual void OnDeviceEvent(const DeviceEvent& event) OVERRIDE;

  
  virtual void OnDispatcherListChanged() OVERRIDE;

  
  std::map<base::FilePath, EventConverterEvdev*> converters_;

  
  DeviceManager* device_manager_;  

  
  scoped_refptr<base::TaskRunner> ui_task_runner_;

  
  EventModifiersEvdev modifiers_;

  
  CursorDelegateEvdev* cursor_;

  
  EventDispatchCallback dispatch_callback_;

  
  base::WeakPtrFactory<EventFactoryEvdev> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EventFactoryEvdev);
};

}  

#endif  
