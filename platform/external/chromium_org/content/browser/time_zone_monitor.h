// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_TIME_ZONE_MONITOR_H_
#define CONTENT_BROWSER_TIME_ZONE_MONITOR_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace content {


class TimeZoneMonitor {
 public:
  
  
  static scoped_ptr<TimeZoneMonitor> Create();

  virtual ~TimeZoneMonitor();

 protected:
  TimeZoneMonitor();

  
  
  void NotifyRenderers();

 private:
  DISALLOW_COPY_AND_ASSIGN(TimeZoneMonitor);
};

}  

#endif  
