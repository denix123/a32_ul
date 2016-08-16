// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_PLATFORM_X11_X11_EVENT_SOURCE_H_
#define UI_EVENTS_PLATFORM_X11_X11_EVENT_SOURCE_H_

#include "base/memory/scoped_ptr.h"
#include "ui/events/events_export.h"
#include "ui/events/platform/platform_event_source.h"
#include "ui/gfx/x/x11_types.h"

typedef struct _GPollFD GPollFD;
typedef struct _GSource GSource;
typedef union _XEvent XEvent;
typedef unsigned long XID;

namespace ui {

class HotplugEventHandlerX11;

class EVENTS_EXPORT X11EventSource : public PlatformEventSource {
 public:
  explicit X11EventSource(XDisplay* display);
  virtual ~X11EventSource();

  static X11EventSource* GetInstance();

  
  
  void DispatchXEvents();

  
  
  
  
  
  
  
  
  
  void BlockUntilWindowMapped(XID window);

 protected:
  XDisplay* display() { return display_; }

 private:
  
  virtual uint32_t DispatchEvent(XEvent* xevent) OVERRIDE;
  virtual void StopCurrentEventStream() OVERRIDE;

  
  XDisplay* display_;

  
  
  bool continue_stream_;

  scoped_ptr<HotplugEventHandlerX11> hotplug_event_handler_;

  DISALLOW_COPY_AND_ASSIGN(X11EventSource);
};

}  

#endif  
