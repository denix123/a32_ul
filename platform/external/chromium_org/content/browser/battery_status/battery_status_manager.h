// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BATTERY_STATUS_BATTERY_STATUS_MANAGER_H_
#define CHROME_BROWSER_BATTERY_STATUS_BATTERY_STATUS_MANAGER_H_

#include "base/memory/scoped_ptr.h"
#include "build/build_config.h"
#include "content/browser/battery_status/battery_status_service.h"

namespace content {

class CONTENT_EXPORT BatteryStatusManager {
 public:
  
  
  static scoped_ptr<BatteryStatusManager> Create(
      const BatteryStatusService::BatteryUpdateCallback& callback);

  virtual ~BatteryStatusManager() {}

  
  
  
  virtual bool StartListeningBatteryChange() = 0;

  
  
  virtual void StopListeningBatteryChange() = 0;
};

}  

#endif  
