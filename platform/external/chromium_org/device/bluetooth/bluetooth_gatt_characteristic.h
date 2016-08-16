// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_GATT_CHARACTERISTIC_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_GATT_CHARACTERISTIC_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace device {

class BluetoothGattDescriptor;
class BluetoothGattService;
class BluetoothGattNotifySession;

class BluetoothGattCharacteristic {
 public:
  
  
  
  
  
  
  
  
  
  enum Property {
    kPropertyNone = 0,
    kPropertyBroadcast = 1 << 0,
    kPropertyRead = 1 << 1,
    kPropertyWriteWithoutResponse = 1 << 2,
    kPropertyWrite = 1 << 3,
    kPropertyNotify = 1 << 4,
    kPropertyIndicate = 1 << 5,
    kPropertyAuthenticatedSignedWrites = 1 << 6,
    kPropertyExtendedProperties = 1 << 7,
    kPropertyReliableWrite = 1 << 8,
    kPropertyWritableAuxiliaries = 1 << 9
  };
  typedef uint32 Properties;

  
  
  
  
  
  
  
  
  
  
  
  enum Permission {
    kPermissionNone = 0,
    kPermissionRead = 1 << 0,
    kPermissionWrite = 1 << 1,
    kPermissionReadEncrypted = 1 << 2,
    kPermissionWriteEncrypted = 1 << 3
  };
  typedef uint32 Permissions;

  
  typedef base::Closure ErrorCallback;

  
  
  typedef base::Callback<void(const std::vector<uint8>&)> ValueCallback;

  
  
  typedef base::Callback<void(scoped_ptr<BluetoothGattNotifySession>)>
      NotifySessionCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static BluetoothGattCharacteristic* Create(const BluetoothUUID& uuid,
                                             const std::vector<uint8>& value,
                                             Properties properties,
                                             Permissions permissions);

  
  
  
  
  
  virtual std::string GetIdentifier() const = 0;

  
  virtual BluetoothUUID GetUUID() const = 0;

  
  
  virtual bool IsLocal() const = 0;

  
  
  
  virtual const std::vector<uint8>& GetValue() const = 0;

  
  virtual BluetoothGattService* GetService() const = 0;

  
  virtual Properties GetProperties() const = 0;

  
  virtual Permissions GetPermissions() const = 0;

  
  
  virtual bool IsNotifying() const = 0;

  
  
  virtual std::vector<BluetoothGattDescriptor*>
      GetDescriptors() const = 0;

  
  
  virtual BluetoothGattDescriptor* GetDescriptor(
      const std::string& identifier) const = 0;

  
  
  
  
  
  virtual bool AddDescriptor(BluetoothGattDescriptor* descriptor) = 0;

  
  
  
  
  
  
  
  
  
  
  virtual bool UpdateValue(const std::vector<uint8>& value) = 0;

  
  
  
  
  virtual void StartNotifySession(const NotifySessionCallback& callback,
                                  const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void ReadRemoteCharacteristic(
      const ValueCallback& callback,
      const ErrorCallback& error_callback) = 0;

  
  
  
  
  
  virtual void WriteRemoteCharacteristic(
      const std::vector<uint8>& new_value,
      const base::Closure& callback,
      const ErrorCallback& error_callback) = 0;

 protected:
  BluetoothGattCharacteristic();
  virtual ~BluetoothGattCharacteristic();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattCharacteristic);
};

}  

#endif  
