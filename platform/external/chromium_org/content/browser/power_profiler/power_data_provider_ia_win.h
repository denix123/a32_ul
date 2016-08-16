// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_POWER_PROFILER_POWER_DATA_PROVIDER_IA_WIN_H_
#define CONTENT_BROWSER_POWER_PROFILER_POWER_DATA_PROVIDER_IA_WIN_H_

#include "content/browser/power_profiler/power_data_provider.h"
#include "third_party/power_gadget/PowerGadgetLib.h"

namespace content {

class PowerDataProviderIA : public PowerDataProvider {
 public:
  PowerDataProviderIA();

  virtual ~PowerDataProviderIA();

  bool Initialize();
  virtual PowerEventVector GetData() OVERRIDE;
  virtual base::TimeDelta GetSamplingRate() OVERRIDE;
  virtual AccuracyLevel GetAccuracyLevel() OVERRIDE { return High; }

 private:
  CIntelPowerGadgetLib energy_lib_;

  int sockets_number_;
  int power_msr_ids_[PowerEvent::ID_COUNT];
  bool is_open_;
  DISALLOW_COPY_AND_ASSIGN(PowerDataProviderIA);
};

}  

#endif  