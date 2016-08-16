// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_DESCRIPTOR_SERVICE_PROVIDER_H_
#define CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_DESCRIPTOR_SERVICE_PROVIDER_H_

#include <string>
#include <vector>

#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/bluetooth_gatt_descriptor_service_provider.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeBluetoothGattDescriptorServiceProvider
    : public BluetoothGattDescriptorServiceProvider {
 public:
  FakeBluetoothGattDescriptorServiceProvider(
      const dbus::ObjectPath& object_path,
      Delegate* delegate,
      const std::string& uuid,
      const std::vector<std::string>& permissions,
      const dbus::ObjectPath& characteristic_path);
  virtual ~FakeBluetoothGattDescriptorServiceProvider();

  
  virtual void SendValueChanged(const std::vector<uint8>& value) OVERRIDE;

  
  
  
  void GetValue(const Delegate::ValueCallback& callback,
                const Delegate::ErrorCallback& error_callback);
  void SetValue(const std::vector<uint8>& value,
                const base::Closure& callback,
                const Delegate::ErrorCallback& error_callback);

  const dbus::ObjectPath& object_path() const { return object_path_; }
  const std::string& uuid() const { return uuid_; }
  const dbus::ObjectPath& characteristic_path() const {
      return characteristic_path_;
  }

 private:
  
  dbus::ObjectPath object_path_;

  
  std::string uuid_;

  
  dbus::ObjectPath characteristic_path_;

  
  Delegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(FakeBluetoothGattDescriptorServiceProvider);
};

}  

#endif  
