// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EVENTS_SYSTEM_KEY_EVENT_LISTENER_H_
#define CHROME_BROWSER_CHROMEOS_EVENTS_SYSTEM_KEY_EVENT_LISTENER_H_

#include "base/memory/singleton.h"
#include "ui/events/platform/platform_event_observer.h"

typedef union _XEvent XEvent;

namespace chromeos {

class SystemKeyEventListener : public ui::PlatformEventObserver {
 public:
  static void Initialize();
  static void Shutdown();
  
  static SystemKeyEventListener* GetInstance();

  void Stop();

 private:
  
  
  friend struct DefaultSingletonTraits<SystemKeyEventListener>;
  friend class SystemKeyEventListenerTest;

  SystemKeyEventListener();
  virtual ~SystemKeyEventListener();

  
  virtual void WillProcessEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual void DidProcessEvent(const ui::PlatformEvent& event) OVERRIDE;

  void ProcessedXEvent(XEvent* xevent);

  bool stopped_;

  
  int xkb_event_base_;

  DISALLOW_COPY_AND_ASSIGN(SystemKeyEventListener);
};

}  

#endif  
