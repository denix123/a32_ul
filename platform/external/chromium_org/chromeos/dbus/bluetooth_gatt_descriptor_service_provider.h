// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_GATT_DESCRIPTOR_SERVICE_PROVIDER_H_
#define CHROMEOS_DBUS_BLUETOOTH_GATT_DESCRIPTOR_SERVICE_PROVIDER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "dbus/bus.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothGattDescriptorServiceProvider {
 public:
  
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    typedef base::Callback<void(const std::vector<uint8>&)> ValueCallback;

    
    typedef base::Closure ErrorCallback;

    
    
    
    
    
    
    
    virtual void GetDescriptorValue(const ValueCallback& callback,
                                    const ErrorCallback& error_callback) = 0;

    
    
    // that the value was successfully written. Invoke |error_callback| to
    
    
    
    
    
    
    
    
    virtual void SetDescriptorValue(const std::vector<uint8>& value,
                                    const base::Closure& callback,
                                    const ErrorCallback& error_callback) = 0;
  };

  virtual ~BluetoothGattDescriptorServiceProvider();

  
  
  virtual void SendValueChanged(const std::vector<uint8>& value) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  static BluetoothGattDescriptorServiceProvider* Create(
      dbus::Bus* bus,
      const dbus::ObjectPath& object_path,
      Delegate* delegate,
      const std::string& uuid,
      const std::vector<std::string>& permissions,
      const dbus::ObjectPath& characteristic_path);

 protected:
  BluetoothGattDescriptorServiceProvider();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattDescriptorServiceProvider);
};

}  

#endif  
