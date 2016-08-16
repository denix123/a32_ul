// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_REMOTE_GATT_CHARACTERISTIC_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_REMOTE_GATT_CHARACTERISTIC_CHROMEOS_H_

#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "chromeos/dbus/bluetooth_gatt_characteristic_client.h"
#include "chromeos/dbus/bluetooth_gatt_descriptor_client.h"
#include "dbus/object_path.h"
#include "device/bluetooth/bluetooth_gatt_characteristic.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace device {

class BluetoothGattDescriptor;
class BluetoothGattService;

}  

namespace chromeos {

class BluetoothRemoteGattDescriptorChromeOS;
class BluetoothRemoteGattServiceChromeOS;

class BluetoothRemoteGattCharacteristicChromeOS
    : public device::BluetoothGattCharacteristic,
      public BluetoothGattCharacteristicClient::Observer,
      public BluetoothGattDescriptorClient::Observer {
 public:
  
  virtual std::string GetIdentifier() const OVERRIDE;
  virtual device::BluetoothUUID GetUUID() const OVERRIDE;
  virtual bool IsLocal() const OVERRIDE;
  virtual const std::vector<uint8>& GetValue() const OVERRIDE;
  virtual device::BluetoothGattService* GetService() const OVERRIDE;
  virtual Properties GetProperties() const OVERRIDE;
  virtual Permissions GetPermissions() const OVERRIDE;
  virtual bool IsNotifying() const OVERRIDE;
  virtual std::vector<device::BluetoothGattDescriptor*>
      GetDescriptors() const OVERRIDE;
  virtual device::BluetoothGattDescriptor* GetDescriptor(
      const std::string& identifier) const OVERRIDE;
  virtual bool AddDescriptor(
      device::BluetoothGattDescriptor* descriptor) OVERRIDE;
  virtual bool UpdateValue(const std::vector<uint8>& value) OVERRIDE;
  virtual void ReadRemoteCharacteristic(
      const ValueCallback& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void WriteRemoteCharacteristic(
      const std::vector<uint8>& new_value,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void StartNotifySession(const NotifySessionCallback& callback,
                                  const ErrorCallback& error_callback) OVERRIDE;

  
  
  
  
  void RemoveNotifySession(const base::Closure& callback);

  
  const dbus::ObjectPath& object_path() const { return object_path_; }

 private:
  friend class BluetoothRemoteGattServiceChromeOS;

  BluetoothRemoteGattCharacteristicChromeOS(
      BluetoothRemoteGattServiceChromeOS* service,
      const dbus::ObjectPath& object_path);
  virtual ~BluetoothRemoteGattCharacteristicChromeOS();

  
  virtual void GattCharacteristicValueUpdated(
      const dbus::ObjectPath& object_path,
      const std::vector<uint8>& value) OVERRIDE;

  
  virtual void GattDescriptorAdded(
      const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void GattDescriptorRemoved(
      const dbus::ObjectPath& object_path) OVERRIDE;

  
  
  void OnValueSuccess(const ValueCallback& callback,
                      const std::vector<uint8>& value);

  
  
  void OnError(const ErrorCallback& error_callback,
               const std::string& error_name,
               const std::string& error_message);

  
  
  void OnStartNotifySuccess(const NotifySessionCallback& callback);

  
  
  void OnStartNotifyError(const ErrorCallback& error_callback,
                          const std::string& error_name,
                          const std::string& error_message);

  
  
  void OnStopNotifySuccess(const base::Closure& callback);

  
  
  void OnStopNotifyError(const base::Closure& callback,
                         const std::string& error_name,
                         const std::string& error_message);

  
  void ProcessStartNotifyQueue();

  
  dbus::ObjectPath object_path_;

  
  BluetoothRemoteGattServiceChromeOS* service_;

  
  
  std::vector<uint8> cached_value_;

  
  size_t num_notify_sessions_;

  
  
  typedef std::pair<NotifySessionCallback, ErrorCallback>
      PendingStartNotifyCall;
  std::queue<PendingStartNotifyCall> pending_start_notify_calls_;

  
  bool notify_call_pending_;

  
  
  
  
  typedef std::map<dbus::ObjectPath, BluetoothRemoteGattDescriptorChromeOS*>
      DescriptorMap;
  DescriptorMap descriptors_;

  
  
  base::WeakPtrFactory<BluetoothRemoteGattCharacteristicChromeOS>
      weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothRemoteGattCharacteristicChromeOS);
};

}  

#endif  
