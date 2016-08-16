// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_RENDERER_HOST_PEPPER_MONITOR_FINDER_MAC_H_
#define CHROME_BROWSER_RENDERER_HOST_PEPPER_MONITOR_FINDER_MAC_H_

#include <ApplicationServices/ApplicationServices.h>

#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"

namespace chrome {

class MonitorFinder : public base::RefCountedThreadSafe<MonitorFinder> {
 public:
  MonitorFinder(int process_id, int render_frame_id);

  
  int64_t GetMonitor();

  
  static bool IsMonitorBuiltIn(int64_t monitor_id);

 private:
  friend class base::RefCountedThreadSafe<MonitorFinder>;
  ~MonitorFinder();

  
  void FetchMonitorFromWidget();

  const int process_id_;
  const int render_frame_id_;

  base::Lock mutex_;  
  
  bool request_sent_;
  
  CGDirectDisplayID display_id_;

  DISALLOW_COPY_AND_ASSIGN(MonitorFinder);
};

}  

#endif  
