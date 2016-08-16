// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_GATT_NOTIFY_SESSION_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_GATT_NOTIFY_SESSION_CHROMEOS_H_

#include <string>

#include "base/callback.h"
#include "chromeos/dbus/bluetooth_gatt_characteristic_client.h"
#include "device/bluetooth/bluetooth_gatt_notify_session.h"

namespace device {

class BluetoothAdapter;

}  

namespace chromeos {

class BluetoothRemoteGattCharacteristicChromeOS;

class BluetoothGattNotifySessionChromeOS
    : public device::BluetoothGattNotifySession,
      public BluetoothGattCharacteristicClient::Observer {
 public:
  virtual ~BluetoothGattNotifySessionChromeOS();

  
  virtual std::string GetCharacteristicIdentifier() const OVERRIDE;
  virtual bool IsActive() OVERRIDE;
  virtual void Stop(const base::Closure& callback) OVERRIDE;

 private:
  friend class BluetoothRemoteGattCharacteristicChromeOS;

  explicit BluetoothGattNotifySessionChromeOS(
      scoped_refptr<device::BluetoothAdapter> adapter,
      const std::string& device_address,
      const std::string& service_identifier,
      const std::string& characteristic_identifier,
      const dbus::ObjectPath& characteristic_path);

  
  virtual void GattCharacteristicRemoved(
      const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void GattCharacteristicPropertyChanged(
      const dbus::ObjectPath& object_path,
      const std::string& property_name) OVERRIDE;

  
  bool active_;

  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  
  std::string device_address_;

  
  std::string service_id_;

  
  std::string characteristic_id_;

  
  
  dbus::ObjectPath object_path_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothGattNotifySessionChromeOS);
};

}  

#endif  
