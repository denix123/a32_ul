// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_PLATFORM_PLATFORM_EVENT_SOURCE_H_
#define UI_EVENTS_PLATFORM_PLATFORM_EVENT_SOURCE_H_

#include <map>
#include <vector>

#include "base/auto_reset.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "ui/events/events_export.h"
#include "ui/events/platform/platform_event_types.h"

namespace ui {

class Event;
class PlatformEventDispatcher;
class PlatformEventObserver;
class ScopedEventDispatcher;

class EVENTS_EXPORT PlatformEventSource {
 public:
  virtual ~PlatformEventSource();

  static PlatformEventSource* GetInstance();

  
  
  
  void AddPlatformEventDispatcher(PlatformEventDispatcher* dispatcher);

  
  
  
  void RemovePlatformEventDispatcher(PlatformEventDispatcher* dispatcher);

  
  
  
  
  
  
  
  
  scoped_ptr<ScopedEventDispatcher> OverrideDispatcher(
      PlatformEventDispatcher* dispatcher);

  void AddPlatformEventObserver(PlatformEventObserver* observer);
  void RemovePlatformEventObserver(PlatformEventObserver* observer);

  static scoped_ptr<PlatformEventSource> CreateDefault();

 protected:
  PlatformEventSource();

  
  
  
  
  
  virtual uint32_t DispatchEvent(PlatformEvent platform_event);

 private:
  friend class ScopedEventDispatcher;
  static PlatformEventSource* instance_;

  
  
  
  virtual void StopCurrentEventStream();

  
  
  virtual void OnDispatcherListChanged();

  void OnOverriddenDispatcherRestored();

  
  
  
  typedef ObserverList<PlatformEventDispatcher> PlatformEventDispatcherList;
  PlatformEventDispatcherList dispatchers_;
  PlatformEventDispatcher* overridden_dispatcher_;

  
  
  bool overridden_dispatcher_restored_;

  ObserverList<PlatformEventObserver> observers_;

  DISALLOW_COPY_AND_ASSIGN(PlatformEventSource);
};

}  

#endif  
