// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PERFORMANCE_MONITOR_PERFORMANCE_MONITOR_H_
#define CHROME_BROWSER_PERFORMANCE_MONITOR_PERFORMANCE_MONITOR_H_

#include <map>

#include "base/process/process_handle.h"
#include "base/timer/timer.h"
#include "chrome/browser/performance_monitor/process_metrics_history.h"

template <typename Type>
struct DefaultSingletonTraits;

namespace performance_monitor {

class PerformanceMonitor {
 public:
  typedef std::map<base::ProcessHandle, ProcessMetricsHistory> MetricsMap;

  
  
  static PerformanceMonitor* GetInstance();

  
  void StartGatherCycle();

 private:
  friend struct DefaultSingletonTraits<PerformanceMonitor>;

  PerformanceMonitor();
  virtual ~PerformanceMonitor();

  
  void DoTimedCollections();

  
  
  
  void MarkProcessAsAlive(const base::ProcessHandle& handle,
                          int process_type,
                          int current_update_sequence);

  
  
  void GatherMetricsMapOnUIThread();
  void GatherMetricsMapOnIOThread(int current_update_sequence);

  
  MetricsMap metrics_map_;

  
  base::RepeatingTimer<PerformanceMonitor> repeating_timer_;

  DISALLOW_COPY_AND_ASSIGN(PerformanceMonitor);
};

}  

#endif  
