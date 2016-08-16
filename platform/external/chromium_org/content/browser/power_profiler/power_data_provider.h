// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_POWER_PROFILER_POWER_DATA_PROVIDER_H_
#define CONTENT_BROWSER_POWER_PROFILER_POWER_DATA_PROVIDER_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "content/browser/power_profiler/power_event.h"

namespace base {
class TimeDelta;
}  

namespace content {

typedef std::vector<PowerEvent> PowerEventVector;

class PowerDataProvider {
 public:
  enum AccuracyLevel {
    High,
    Moderate,
    Low
  };

  static scoped_ptr<PowerDataProvider> Create();

  PowerDataProvider() {}
  virtual ~PowerDataProvider() {}

  
  virtual PowerEventVector GetData() = 0;

  
  virtual base::TimeDelta GetSamplingRate() = 0;

  
  virtual AccuracyLevel GetAccuracyLevel() = 0;
};

}  

#endif  
