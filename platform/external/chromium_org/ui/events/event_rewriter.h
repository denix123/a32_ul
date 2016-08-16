// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_EVENT_REWRITER_H_
#define UI_EVENTS_EVENT_REWRITER_H_

#include "base/memory/scoped_ptr.h"
#include "ui/events/events_export.h"

namespace ui {

class Event;

enum EventRewriteStatus {
  // Nothing was done; no rewritten event returned. Pass the original
  
  
  EVENT_REWRITE_CONTINUE,

  // The event has been rewritten. Send the rewritten event to the
  
  
  EVENT_REWRITE_REWRITTEN,

  
  
  EVENT_REWRITE_DISCARD,

  // The event has been rewritten. As for EVENT_REWRITE_REWRITTEN,
  // send the rewritten event to the EventProcessor instead of the
  
  
  
  
  EVENT_REWRITE_DISPATCH_ANOTHER,
};

// EventRewriter provides a mechanism for Events to be rewritten
class EVENTS_EXPORT EventRewriter {
 public:
  virtual ~EventRewriter() {}

  
  
  // dispatch another event once the rewritten event is dispatched, it should
  
  
  virtual EventRewriteStatus RewriteEvent(
      const Event& event,
      scoped_ptr<Event>* rewritten_event) = 0;

  
  
  
  // Should only return either EVENT_REWRITE_REWRITTEN or
  
  
  virtual EventRewriteStatus NextDispatchEvent(
      const Event& last_event,
      scoped_ptr<Event>* new_event) = 0;
};

}  

#endif  
