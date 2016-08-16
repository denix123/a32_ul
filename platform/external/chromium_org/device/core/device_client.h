// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_CORE_DEVICE_CLIENT_H_
#define DEVICE_CORE_DEVICE_CLIENT_H_

#include "base/macros.h"

namespace device {

class HidService;
class UsbService;

class DeviceClient {
 public:
  
  DeviceClient();

  
  ~DeviceClient();

  
  static DeviceClient* Get();

  
  virtual UsbService* GetUsbService();

  
  virtual HidService* GetHidService();

 private:
  DISALLOW_COPY_AND_ASSIGN(DeviceClient);
};

}  

#endif  
