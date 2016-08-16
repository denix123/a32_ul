// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_GATT_NOTIFY_SESSION_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_GATT_NOTIFY_SESSION_H_

#include <string>

#include "base/callback.h"

namespace device {

class BluetoothGattNotifySession {
 public:
  
  virtual ~BluetoothGattNotifySession();

  
  virtual std::string GetCharacteristicIdentifier() const = 0;

  
  virtual bool IsActive() = 0;

  
  
  
  
  virtual void Stop(const base::Closure& callback) = 0;

 protected:
  BluetoothGattNotifySession();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattNotifySession);
};

}  

#endif  
