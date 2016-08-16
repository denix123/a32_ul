// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_GATT_CONNECTION_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_GATT_CONNECTION_H_

#include <string>

#include "base/callback.h"

namespace device {

class BluetoothGattConnection {
 public:
  
  
  
  
  
  virtual ~BluetoothGattConnection();

  
  
  virtual std::string GetDeviceAddress() const = 0;

  
  virtual bool IsConnected() = 0;

  
  
  
  virtual void Disconnect(const base::Closure& callback) = 0;

 protected:
  BluetoothGattConnection();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattConnection);
};

}  

#endif  
