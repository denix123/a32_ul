// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_GATT_CONNECTION_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_GATT_CONNECTION_CHROMEOS_H_

#include <string>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "chromeos/dbus/bluetooth_device_client.h"
#include "dbus/object_path.h"
#include "device/bluetooth/bluetooth_gatt_connection.h"

namespace device {

class BluetoothAdapter;

}  

namespace chromeos {

class BluetoothGattConnectionChromeOS
    : public device::BluetoothGattConnection,
      public BluetoothDeviceClient::Observer {
 public:
  explicit BluetoothGattConnectionChromeOS(
      scoped_refptr<device::BluetoothAdapter> adapter,
      const std::string& device_address,
      const dbus::ObjectPath& object_path);
  virtual ~BluetoothGattConnectionChromeOS();

  
  virtual std::string GetDeviceAddress() const OVERRIDE;
  virtual bool IsConnected() OVERRIDE;
  virtual void Disconnect(const base::Closure& callback) OVERRIDE;

 private:

  
  virtual void DeviceRemoved(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void DevicePropertyChanged(const dbus::ObjectPath& object_path,
                                     const std::string& property_name) OVERRIDE;

  
  bool connected_;

  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  
  std::string device_address_;

  
  
  dbus::ObjectPath object_path_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothGattConnectionChromeOS);
};

}  

#endif  
