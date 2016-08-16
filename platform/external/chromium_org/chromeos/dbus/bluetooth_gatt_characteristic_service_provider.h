// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_GATT_CHARACTERISTIC_SERVICE_PROVIDER_H_
#define CHROMEOS_DBUS_BLUETOOTH_GATT_CHARACTERISTIC_SERVICE_PROVIDER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "dbus/bus.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothGattCharacteristicServiceProvider {
 public:
  
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    typedef base::Callback<void(const std::vector<uint8>&)> ValueCallback;

    
    typedef base::Closure ErrorCallback;

    
    
    
    
    
    
    
    virtual void GetCharacteristicValue(
        const ValueCallback& callback,
        const ErrorCallback& error_callback) = 0;

    
    
    // that the value was successfully written. Invoke |error_callback| to
    
    
    
    
    
    
    
    
    virtual void SetCharacteristicValue(
        const std::vector<uint8>& value,
        const base::Closure& callback,
        const ErrorCallback& error_callback) = 0;
  };

  virtual ~BluetoothGattCharacteristicServiceProvider();

  
  
  virtual void SendValueChanged(const std::vector<uint8>& value) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static BluetoothGattCharacteristicServiceProvider* Create(
      dbus::Bus* bus,
      const dbus::ObjectPath& object_path,
      Delegate* delegate,
      const std::string& uuid,
      const std::vector<std::string>& flags,
      const std::vector<std::string>& permissions,
      const dbus::ObjectPath& service_path);

 protected:
  BluetoothGattCharacteristicServiceProvider();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattCharacteristicServiceProvider);
};

}  

#endif  
