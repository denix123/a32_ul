// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_GATT_SERVICE_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_GATT_SERVICE_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace device {

class BluetoothDevice;
class BluetoothGattCharacteristic;
class BluetoothGattDescriptor;

class BluetoothGattService {
 public:
  
  
  
  class Delegate {
   public:
    
    typedef base::Callback<void(const std::vector<uint8>)> ValueCallback;
    typedef base::Closure ErrorCallback;

    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnCharacteristicReadRequest(
        const BluetoothGattService* service,
        const BluetoothGattCharacteristic* characteristic,
        int offset,
        const ValueCallback& callback,
        const ErrorCallback& error_callback) = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnCharacteristicWriteRequest(
        const BluetoothGattService* service,
        const BluetoothGattCharacteristic* characteristic,
        const std::vector<uint8>& value,
        int offset,
        const ValueCallback& callback,
        const ErrorCallback& error_callback) = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnDescriptorReadRequest(
        const BluetoothGattService* service,
        const BluetoothGattDescriptor* descriptor,
        int offset,
        const ValueCallback& callback,
        const ErrorCallback& error_callback) = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnDescriptorWriteRequest(
        const BluetoothGattService* service,
        const BluetoothGattDescriptor* descriptor,
        const std::vector<uint8>& value,
        int offset,
        const ValueCallback& callback,
        const ErrorCallback& error_callback) = 0;
  };

  
  typedef base::Closure ErrorCallback;

  virtual ~BluetoothGattService();

  
  
  
  
  
  
  
  
  static BluetoothGattService* Create(const BluetoothUUID& uuid,
                                      bool is_primary,
                                      Delegate* delegate);

  
  
  
  
  
  virtual std::string GetIdentifier() const = 0;

  
  virtual BluetoothUUID GetUUID() const = 0;

  
  
  virtual bool IsLocal() const = 0;

  
  
  
  
  
  virtual bool IsPrimary() const = 0;

  
  
  virtual BluetoothDevice* GetDevice() const = 0;

  
  virtual std::vector<BluetoothGattCharacteristic*>
      GetCharacteristics() const = 0;

  
  virtual std::vector<BluetoothGattService*>
      GetIncludedServices() const = 0;

  
  
  virtual BluetoothGattCharacteristic* GetCharacteristic(
      const std::string& identifier) const = 0;

  
  
  
  
  
  
  virtual bool AddCharacteristic(
      BluetoothGattCharacteristic* characteristic) = 0;
  virtual bool AddIncludedService(BluetoothGattService* service) = 0;

  
  
  
  
  
  
  
  
  
  virtual void Register(const base::Closure& callback,
                        const ErrorCallback& error_callback) = 0;
  virtual void Unregister(const base::Closure& callback,
                          const ErrorCallback& error_callback) = 0;

 protected:
  BluetoothGattService();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattService);
};

}  

#endif  
