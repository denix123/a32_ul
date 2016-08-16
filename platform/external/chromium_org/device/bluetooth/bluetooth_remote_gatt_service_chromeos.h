// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_REMOTE_GATT_SERVICE_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_REMOTE_GATT_SERVICE_CHROMEOS_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chromeos/dbus/bluetooth_gatt_characteristic_client.h"
#include "chromeos/dbus/bluetooth_gatt_service_client.h"
#include "dbus/object_path.h"
#include "device/bluetooth/bluetooth_gatt_service.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace device {

class BluetoothAdapter;
class BluetoothGattCharacteristic;

}  

namespace chromeos {

class BluetoothAdapterChromeOS;
class BluetoothDeviceChromeOS;
class BluetoothRemoteGattCharacteristicChromeOS;
class BluetoothRemoteGattDescriptorChromeOS;

class BluetoothRemoteGattServiceChromeOS
    : public device::BluetoothGattService,
      public BluetoothGattServiceClient::Observer,
      public BluetoothGattCharacteristicClient::Observer {
 public:
  
  virtual std::string GetIdentifier() const OVERRIDE;
  virtual device::BluetoothUUID GetUUID() const OVERRIDE;
  virtual bool IsLocal() const OVERRIDE;
  virtual bool IsPrimary() const OVERRIDE;
  virtual device::BluetoothDevice* GetDevice() const OVERRIDE;
  virtual std::vector<device::BluetoothGattCharacteristic*>
      GetCharacteristics() const OVERRIDE;
  virtual std::vector<device::BluetoothGattService*>
      GetIncludedServices() const OVERRIDE;
  virtual device::BluetoothGattCharacteristic* GetCharacteristic(
      const std::string& identifier) const OVERRIDE;
  virtual bool AddCharacteristic(
      device::BluetoothGattCharacteristic* characteristic) OVERRIDE;
  virtual bool AddIncludedService(
      device::BluetoothGattService* service) OVERRIDE;
  virtual void Register(const base::Closure& callback,
                        const ErrorCallback& error_callback) OVERRIDE;
  virtual void Unregister(const base::Closure& callback,
                          const ErrorCallback& error_callback) OVERRIDE;

  
  const dbus::ObjectPath& object_path() const { return object_path_; }

  
  BluetoothAdapterChromeOS* GetAdapter() const;

  
  
  
  void NotifyServiceChanged();

  
  
  
  
  void NotifyCharacteristicValueChanged(
      BluetoothRemoteGattCharacteristicChromeOS* characteristic,
      const std::vector<uint8>& value);

  
  
  
  
  
  
  void NotifyDescriptorAddedOrRemoved(
      BluetoothRemoteGattCharacteristicChromeOS* characteristic,
      BluetoothRemoteGattDescriptorChromeOS* descriptor,
      bool added);

  
  
  
  void NotifyDescriptorValueChanged(
      BluetoothRemoteGattCharacteristicChromeOS* characteristic,
      BluetoothRemoteGattDescriptorChromeOS* descriptor,
      const std::vector<uint8>& value);

 private:
  friend class BluetoothDeviceChromeOS;

  BluetoothRemoteGattServiceChromeOS(BluetoothAdapterChromeOS* adapter,
                                     BluetoothDeviceChromeOS* device,
                                     const dbus::ObjectPath& object_path);
  virtual ~BluetoothRemoteGattServiceChromeOS();

  
  virtual void GattServicePropertyChanged(
      const dbus::ObjectPath& object_path,
      const std::string& property_name) OVERRIDE;

  
  virtual void GattCharacteristicAdded(
      const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void GattCharacteristicRemoved(
      const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void GattCharacteristicPropertyChanged(
      const dbus::ObjectPath& object_path,
      const std::string& property_name) OVERRIDE;

  
  dbus::ObjectPath object_path_;

  
  
  BluetoothAdapterChromeOS* adapter_;

  
  
  BluetoothDeviceChromeOS* device_;

  
  
  
  
  typedef std::map<dbus::ObjectPath, BluetoothRemoteGattCharacteristicChromeOS*>
      CharacteristicMap;
  CharacteristicMap characteristics_;

  
  
  bool discovery_complete_;

  
  
  base::WeakPtrFactory<BluetoothRemoteGattServiceChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothRemoteGattServiceChromeOS);
};

}  

#endif  
