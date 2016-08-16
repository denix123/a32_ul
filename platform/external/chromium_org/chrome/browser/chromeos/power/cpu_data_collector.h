// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POWER_CPU_DATA_COLLECTOR_H_
#define CHROME_BROWSER_CHROMEOS_POWER_CPU_DATA_COLLECTOR_H_

#include <deque>
#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"

namespace chromeos {

class CpuDataCollector {
 public:
  struct StateOccupancySample {
    StateOccupancySample();
    ~StateOccupancySample();

    
    base::Time time;

    
    bool cpu_online;

    
    
    
    
    
    std::vector<int64> time_in_state;
  };

  typedef std::deque<StateOccupancySample> StateOccupancySampleDeque;

  const std::vector<std::string>& cpu_idle_state_names() const {
    return cpu_idle_state_names_;
  }

  const std::vector<StateOccupancySampleDeque>& cpu_idle_state_data() const {
    return cpu_idle_state_data_;
  }

  const std::vector<std::string>& cpu_freq_state_names() const {
    return cpu_freq_state_names_;
  }

  const std::vector<StateOccupancySampleDeque>& cpu_freq_state_data() const {
    return cpu_freq_state_data_;
  }

  CpuDataCollector();
  ~CpuDataCollector();

  
  
  void Start();

 private:
  
  
  void PostSampleCpuState();

  
  
  
  
  void SaveCpuStateSamplesOnUIThread(
      const int* cpu_count,
      const std::vector<std::string>* cpu_idle_state_names,
      const std::vector<StateOccupancySample>* idle_samples,
      const std::vector<std::string>* cpu_freq_state_names,
      const std::vector<StateOccupancySample>* freq_samples);

  base::RepeatingTimer<CpuDataCollector> timer_;

  
  std::vector<std::string> cpu_idle_state_names_;

  
  
  std::vector<StateOccupancySampleDeque> cpu_idle_state_data_;

  
  std::vector<std::string> cpu_freq_state_names_;

  
  
  std::vector<StateOccupancySampleDeque> cpu_freq_state_data_;

  
  // hence should be read/written to only from the blocking pool.
  int cpu_count_;

  base::WeakPtrFactory<CpuDataCollector> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(CpuDataCollector);
};

}  

#endif  
