// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_GATT_SERVICE_SERVICE_PROVIDER_H_
#define CHROMEOS_DBUS_BLUETOOTH_GATT_SERVICE_SERVICE_PROVIDER_H_

#include <string>
#include <vector>

#include "chromeos/chromeos_export.h"
#include "dbus/bus.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothGattServiceServiceProvider {
 public:
  virtual ~BluetoothGattServiceServiceProvider();

  
  
  
  
  
  
  static BluetoothGattServiceServiceProvider* Create(
      dbus::Bus* bus,
      const dbus::ObjectPath& object_path,
      const std::string& uuid,
      const std::vector<dbus::ObjectPath>& includes);

 protected:
  BluetoothGattServiceServiceProvider();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattServiceServiceProvider);
};

}  

#endif  
