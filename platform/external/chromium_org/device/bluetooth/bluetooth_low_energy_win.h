// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_LOW_ENERGY_WIN_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_LOW_ENERGY_WIN_H_

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/win/scoped_handle.h"
#include "device/bluetooth/bluetooth_low_energy_defs_win.h"

namespace device {
namespace win {

class DeviceRegistryPropertyValue {
 public:
  
  
  
  
  
  static scoped_ptr<DeviceRegistryPropertyValue> Create(
      DWORD property_type,
      scoped_ptr<uint8_t[]> value,
      size_t value_size);
  ~DeviceRegistryPropertyValue();

  
  DWORD property_type() const { return property_type_; }

  std::string AsString() const;
  DWORD AsDWORD() const;

 private:
  DeviceRegistryPropertyValue(DWORD property_type,
                              scoped_ptr<uint8_t[]> value,
                              size_t value_size);

  DWORD property_type_;
  scoped_ptr<uint8_t[]> value_;
  size_t value_size_;

  DISALLOW_COPY_AND_ASSIGN(DeviceRegistryPropertyValue);
};

class DevicePropertyValue {
 public:
  
  
  
  
  DevicePropertyValue(DEVPROPTYPE property_type,
                      scoped_ptr<uint8_t[]> value,
                      size_t value_size);

  DEVPROPTYPE property_type() const { return property_type_; }

  uint32_t AsUint32() const;

 private:
  DEVPROPTYPE property_type_;
  scoped_ptr<uint8_t[]> value_;
  size_t value_size_;

  DISALLOW_COPY_AND_ASSIGN(DevicePropertyValue);
};

bool IsBluetoothLowEnergySupported();

struct BluetoothLowEnergyServiceInfo {
  BluetoothLowEnergyServiceInfo();
  ~BluetoothLowEnergyServiceInfo();

  BTH_LE_UUID uuid;
};

struct BluetoothLowEnergyDeviceInfo {
  BluetoothLowEnergyDeviceInfo();
  ~BluetoothLowEnergyDeviceInfo();

  base::FilePath path;
  std::string id;
  std::string friendly_name;
  BLUETOOTH_ADDRESS address;
  bool visible;
  bool authenticated;
  bool connected;
};

bool EnumerateKnownBluetoothLowEnergyDevices(
    ScopedVector<BluetoothLowEnergyDeviceInfo>* devices,
    std::string* error);

bool EnumerateKnownBluetoothLowEnergyServices(
    const base::FilePath& device_path,
    ScopedVector<BluetoothLowEnergyServiceInfo>* services,
    std::string* error);

bool ExtractBluetoothAddressFromDeviceInstanceIdForTesting(
    const std::string& instance_id,
    BLUETOOTH_ADDRESS* btha,
    std::string* error);

}  
}  

#endif  
