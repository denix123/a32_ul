// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_MANAGER_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_MANAGER_CLIENT_H_

#include <map>
#include <string>
#include <utility>

#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/bluetooth_gatt_manager_client.h"
#include "dbus/object_path.h"

namespace chromeos {

class FakeBluetoothGattCharacteristicServiceProvider;
class FakeBluetoothGattDescriptorServiceProvider;
class FakeBluetoothGattServiceServiceProvider;

class CHROMEOS_EXPORT FakeBluetoothGattManagerClient
    : public BluetoothGattManagerClient {
 public:
  FakeBluetoothGattManagerClient();
  virtual ~FakeBluetoothGattManagerClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;

  
  virtual void RegisterService(const dbus::ObjectPath& service_path,
                               const Options& options,
                               const base::Closure& callback,
                               const ErrorCallback& error_callback) OVERRIDE;
  virtual void UnregisterService(const dbus::ObjectPath& service_path,
                                 const base::Closure& callback,
                                 const ErrorCallback& error_callback) OVERRIDE;

  
  
  
  void RegisterServiceServiceProvider(
      FakeBluetoothGattServiceServiceProvider* provider);
  void RegisterCharacteristicServiceProvider(
      FakeBluetoothGattCharacteristicServiceProvider* provider);
  void RegisterDescriptorServiceProvider(
      FakeBluetoothGattDescriptorServiceProvider* provider);

  void UnregisterServiceServiceProvider(
      FakeBluetoothGattServiceServiceProvider* provider);
  void UnregisterCharacteristicServiceProvider(
      FakeBluetoothGattCharacteristicServiceProvider* provider);
  void UnregisterDescriptorServiceProvider(
      FakeBluetoothGattDescriptorServiceProvider* provider);

  
  
  FakeBluetoothGattServiceServiceProvider*
      GetServiceServiceProvider(const dbus::ObjectPath& object_path) const;
  FakeBluetoothGattCharacteristicServiceProvider*
      GetCharacteristicServiceProvider(
          const dbus::ObjectPath& object_path) const;
  FakeBluetoothGattDescriptorServiceProvider*
      GetDescriptorServiceProvider(const dbus::ObjectPath& object_path) const;

  
  
  bool IsServiceRegistered(const dbus::ObjectPath& object_path) const;

 private:
  
  
  
  typedef std::map<
      dbus::ObjectPath, FakeBluetoothGattCharacteristicServiceProvider*>
      CharacteristicMap;
  typedef std::map<
      dbus::ObjectPath, FakeBluetoothGattDescriptorServiceProvider*>
      DescriptorMap;

  
  
  
  typedef std::pair<bool, FakeBluetoothGattServiceServiceProvider*>
      ServiceProvider;
  typedef std::map<dbus::ObjectPath, ServiceProvider> ServiceMap;

  ServiceMap service_map_;
  CharacteristicMap characteristic_map_;
  DescriptorMap descriptor_map_;

  DISALLOW_COPY_AND_ASSIGN(FakeBluetoothGattManagerClient);
};

}  

#endif  
