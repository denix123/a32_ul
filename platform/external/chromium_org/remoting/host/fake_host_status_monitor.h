// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_FAKE_HOST_STATUS_MONITOR_H_
#define REMOTING_HOST_FAKE_HOST_STATUS_MONITOR_H_

#include "base/memory/weak_ptr.h"
#include "remoting/host/host_status_monitor.h"

namespace remoting {

class FakeHostStatusMonitor
    : public base::SupportsWeakPtr<FakeHostStatusMonitor>,
      public HostStatusMonitor {
 public:
  virtual ~FakeHostStatusMonitor() {}

  
  virtual void AddStatusObserver(HostStatusObserver* observer) OVERRIDE {}
  virtual void RemoveStatusObserver(HostStatusObserver* observer) OVERRIDE {}
};

}  

#endif  
