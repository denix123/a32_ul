// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EVENTS_EVENT_REWRITER_CONTROLLER_H_
#define CHROME_BROWSER_CHROMEOS_EVENTS_EVENT_REWRITER_CONTROLLER_H_

#include <list>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "ui/aura/env_observer.h"
#include "ui/events/event_rewriter.h"

namespace ui {
class EventSource;
}  

namespace chromeos {

class EventRewriterController : public aura::EnvObserver {
 public:
  EventRewriterController();
  virtual ~EventRewriterController();

  
  void AddEventRewriter(scoped_ptr<ui::EventRewriter> rewriter);

  
  
  void Init();

  
  virtual void OnWindowInitialized(aura::Window* window) OVERRIDE {}
  virtual void OnHostInitialized(aura::WindowTreeHost* host) OVERRIDE;

 private:
  typedef std::list<ui::EventSource*> EventSourceList;
  typedef ScopedVector<ui::EventRewriter> EventRewriters;

  void AddToEventSource(ui::EventSource* source);

  
  EventRewriters rewriters_;

  
  
  bool initialized_;

  DISALLOW_COPY_AND_ASSIGN(EventRewriterController);
};

}  

#endif  
