// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_REMOTE_GATT_DESCRIPTOR_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_REMOTE_GATT_DESCRIPTOR_CHROMEOS_H_

#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "dbus/object_path.h"
#include "device/bluetooth/bluetooth_gatt_descriptor.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace device {

class BluetoothGattCharacteristic;

}  

namespace chromeos {

class BluetoothRemoteGattCharacteristicChromeOS;

class BluetoothRemoteGattDescriptorChromeOS
    : public device::BluetoothGattDescriptor {
 public:
  
  virtual std::string GetIdentifier() const OVERRIDE;
  virtual device::BluetoothUUID GetUUID() const OVERRIDE;
  virtual bool IsLocal() const OVERRIDE;
  virtual const std::vector<uint8>& GetValue() const OVERRIDE;
  virtual device::BluetoothGattCharacteristic*
      GetCharacteristic() const OVERRIDE;
  virtual device::BluetoothGattCharacteristic::Permissions
      GetPermissions() const OVERRIDE;
  virtual void ReadRemoteDescriptor(
      const ValueCallback& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void WriteRemoteDescriptor(
      const std::vector<uint8>& new_value,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;

  
  const dbus::ObjectPath& object_path() const { return object_path_; }

 private:
  friend class BluetoothRemoteGattCharacteristicChromeOS;

  BluetoothRemoteGattDescriptorChromeOS(
      BluetoothRemoteGattCharacteristicChromeOS* characteristic,
      const dbus::ObjectPath& object_path);
  virtual ~BluetoothRemoteGattDescriptorChromeOS();

  
  
  void OnValueSuccess(const ValueCallback& callback,
                      const std::vector<uint8>& value);

  
  
  void OnError(const ErrorCallback& error_callback,
               const std::string& error_name,
               const std::string& error_message);

  
  dbus::ObjectPath object_path_;

  
  BluetoothRemoteGattCharacteristicChromeOS* characteristic_;

  
  std::vector<uint8> cached_value_;

  
  
  base::WeakPtrFactory<BluetoothRemoteGattDescriptorChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothRemoteGattDescriptorChromeOS);
};

}  

#endif  
