// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POWER_PROCESS_POWER_COLLECTOR_H_
#define CHROME_BROWSER_POWER_PROCESS_POWER_COLLECTOR_H_

#include <map>

#include "base/memory/linked_ptr.h"
#include "base/process/process_handle.h"
#include "base/process/process_metrics.h"
#include "base/timer/timer.h"
#include "components/power/origin_power_map_factory.h"
#include "url/gurl.h"

#if defined(OS_CHROMEOS)
#include "chromeos/dbus/power_manager_client.h"
#endif

class Profile;

namespace content {
class RenderProcessHost;
}

#if defined(OS_CHROMEOS)
namespace power_manager {
class PowerSupplyProperties;
}
#endif

class ProcessPowerCollector
#if defined(OS_CHROMEOS)
    : public chromeos::PowerManagerClient::Observer
#endif
      {
 public:
  class PerProcessData {
   public:
    PerProcessData(scoped_ptr<base::ProcessMetrics> metrics,
                   const GURL& origin,
                   Profile* profile);
    PerProcessData();
    ~PerProcessData();

    base::ProcessMetrics* metrics() const { return metrics_.get(); }
    Profile* profile() const { return profile_; }
    GURL last_origin() const { return last_origin_; }
    int last_cpu_percent() const { return last_cpu_percent_; }
    bool seen_this_cycle() const { return seen_this_cycle_; }
    void set_last_cpu_percent(double new_cpu) { last_cpu_percent_ = new_cpu; }
    void set_seen_this_cycle(bool seen) { seen_this_cycle_ = seen; }

   private:
    
    scoped_ptr<base::ProcessMetrics> metrics_;

    
    
    Profile* profile_;

    
    GURL last_origin_;

    
    
    double last_cpu_percent_;

    
    
    bool seen_this_cycle_;

    DISALLOW_COPY_AND_ASSIGN(PerProcessData);
  };

  
  typedef std::map<base::ProcessHandle, linked_ptr<PerProcessData> >
      ProcessMetricsMap;
  
  typedef base::Callback<double(base::ProcessHandle)> CpuUsageCallback;

  
  
  ProcessPowerCollector();
  
  virtual ~ProcessPowerCollector();

  void set_cpu_usage_callback_for_testing(const CpuUsageCallback& callback) {
    cpu_usage_callback_ = callback;
  }

  ProcessMetricsMap* metrics_map_for_testing() { return &metrics_map_; }

#if defined(OS_CHROMEOS)
  
  virtual void PowerChanged(
      const power_manager::PowerSupplyProperties& prop) OVERRIDE;
#endif

  
  void Initialize();

  
  double UpdatePowerConsumptionForTesting();

 private:
  
  void StartTimer();

  
  
  
  double UpdatePowerConsumption();

  
  void HandleUpdateTimeout();

  
  
  double SynchronizeProcesses();

  
  
  
  void RecordCpuUsageByOrigin(double total_cpu_percent);

  
  
  void UpdateProcessInMap(const content::RenderProcessHost* render_process,
                          const GURL& origin);

  ProcessMetricsMap metrics_map_;
  base::RepeatingTimer<ProcessPowerCollector> timer_;

  
  CpuUsageCallback cpu_usage_callback_;

  
  double scale_factor_;

  DISALLOW_COPY_AND_ASSIGN(ProcessPowerCollector);
};

#endif  
