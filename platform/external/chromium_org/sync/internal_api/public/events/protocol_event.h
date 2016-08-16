// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_EVENTS_PROTOCOL_EVENT_H
#define SYNC_INTERNAL_API_PUBLIC_EVENTS_PROTOCOL_EVENT_H

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/values.h"
#include "sync/base/sync_export.h"

namespace syncer {

class SYNC_EXPORT ProtocolEvent {
 public:
  ProtocolEvent();
  virtual ~ProtocolEvent();

  
  virtual base::Time GetTimestamp() const = 0;

  
  virtual std::string GetType() const = 0;

  
  
  virtual std::string GetDetails() const = 0;

  
  
  virtual scoped_ptr<base::DictionaryValue> GetProtoMessage() const = 0;

  
  virtual scoped_ptr<ProtocolEvent> Clone() const = 0;

  
  
  static scoped_ptr<base::DictionaryValue> ToValue(
      const ProtocolEvent& event);
};

}  

#endif  
