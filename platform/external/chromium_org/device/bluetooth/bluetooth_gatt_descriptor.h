// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_GATT_DESCRIPTOR_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_GATT_DESCRIPTOR_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "device/bluetooth/bluetooth_gatt_characteristic.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace device {

class BluetoothGattDescriptor {
 public:
  
  
  
  
  
  

  
  
  
  
  
  
  
  
  static const BluetoothUUID& CharacteristicExtendedPropertiesUuid();

  
  
  
  // per characteristic. This descriptor can be written to if the "Writable
  
  
  static const BluetoothUUID& CharacteristicUserDescriptionUuid();

  
  
  
  // the server and the value can be read and written by that client only. As
  
  
  
  
  
  
  
  
  static const BluetoothUUID& ClientCharacteristicConfigurationUuid();

  
  
  
  
  
  
  
  
  
  
  
  static const BluetoothUUID& ServerCharacteristicConfigurationUuid();

  
  
  
  
  
  
  
  
  static const BluetoothUUID& CharacteristicPresentationFormatUuid();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static const BluetoothUUID& CharacteristicAggregateFormatUuid();

  
  typedef base::Closure ErrorCallback;

  
  
  typedef base::Callback<void(const std::vector<uint8>&)> ValueCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static BluetoothGattDescriptor* Create(
      const BluetoothUUID& uuid,
      const std::vector<uint8>& value,
      BluetoothGattCharacteristic::Permissions permissions);

  
  
  
  
  
  virtual std::string GetIdentifier() const = 0;

  
  virtual BluetoothUUID GetUUID() const = 0;

  
  
  virtual bool IsLocal() const = 0;

  
  
  
  
  virtual const std::vector<uint8>& GetValue() const = 0;

  
  
  virtual BluetoothGattCharacteristic* GetCharacteristic() const = 0;

  
  virtual BluetoothGattCharacteristic::Permissions GetPermissions() const = 0;

  
  
  
  virtual void ReadRemoteDescriptor(const ValueCallback& callback,
                                    const ErrorCallback& error_callback) = 0;

  
  
  
  
  
  virtual void WriteRemoteDescriptor(
      const std::vector<uint8>& new_value,
      const base::Closure& callback,
      const ErrorCallback& error_callback) = 0;

 protected:
  BluetoothGattDescriptor();
  virtual ~BluetoothGattDescriptor();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattDescriptor);
};

}  

#endif  
