// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POWER_POWER_DATA_COLLECTOR_H_
#define CHROME_BROWSER_CHROMEOS_POWER_POWER_DATA_COLLECTOR_H_

#include <deque>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/time/time.h"
#include "chrome/browser/chromeos/power/cpu_data_collector.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/power_manager_client.h"

namespace power_manager {
class PowerSupplyProperties;
}

namespace chromeos {

class CHROMEOS_EXPORT PowerDataCollector : public PowerManagerClient::Observer {
 public:
  struct PowerSupplySample {
    PowerSupplySample();

    
    
    
    base::Time time;

    
    bool external_power;

    
    double battery_percent;

    
    
    double battery_discharge_rate;
  };

  struct SystemResumedSample {
    SystemResumedSample();

    
    base::Time time;

    
    base::TimeDelta sleep_duration;
  };

  const std::deque<PowerSupplySample>& power_supply_data() const {
    return power_supply_data_;
  }

  const std::deque<SystemResumedSample>& system_resumed_data() const {
    return system_resumed_data_;
  }

  const CpuDataCollector& cpu_data_collector() const {
    return cpu_data_collector_;
  }

  
  static void Initialize();

  
  static void InitializeForTesting();

  
  
  static void Shutdown();

  
  static PowerDataCollector* Get();

  
  virtual void PowerChanged(
      const power_manager::PowerSupplyProperties& prop) OVERRIDE;
  virtual void SuspendDone(const base::TimeDelta& sleep_duration) OVERRIDE;

  
  
  static const int kSampleTimeLimitSec;

 private:
  explicit PowerDataCollector(const bool start_cpu_data_collector);

  virtual ~PowerDataCollector();

  std::deque<PowerSupplySample> power_supply_data_;
  std::deque<SystemResumedSample> system_resumed_data_;
  CpuDataCollector cpu_data_collector_;

  DISALLOW_COPY_AND_ASSIGN(PowerDataCollector);
};

template <typename SampleType>
void AddSample(std::deque<SampleType>* sample_queue, const SampleType& sample) {
  while (!sample_queue->empty()) {
    const SampleType& first = sample_queue->front();
    if (sample.time - first.time >
        base::TimeDelta::FromSeconds(PowerDataCollector::kSampleTimeLimitSec)) {
      sample_queue->pop_front();
    } else {
      break;
    }
  }
  sample_queue->push_back(sample);
}

}  

#endif  
