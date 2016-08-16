// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVICE_MONITOR_MAC_H_
#define CONTENT_BROWSER_DEVICE_MONITOR_MAC_H_

#include "base/basictypes.h"
#include "base/system_monitor/system_monitor.h"
#include "base/threading/thread_checker.h"

namespace {
class DeviceMonitorMacImpl;
}

namespace content {

class DeviceMonitorMac {
 public:
  DeviceMonitorMac();
  ~DeviceMonitorMac();

  
  
  
  
  void StartMonitoring(
    const scoped_refptr<base::SingleThreadTaskRunner>& device_task_runner);

  
  
  
  
  void NotifyDeviceChanged(base::SystemMonitor::DeviceType type);

 private:
  scoped_ptr<DeviceMonitorMacImpl> device_monitor_impl_;

  
  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(DeviceMonitorMac);
};

}  

#endif  
