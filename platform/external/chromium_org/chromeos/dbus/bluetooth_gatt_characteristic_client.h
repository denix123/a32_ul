// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_GATT_CHARACTERISTIC_CLIENT_H_
#define CHROMEOS_DBUS_BLUETOOTH_GATT_CHARACTERISTIC_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client.h"
#include "dbus/object_path.h"
#include "dbus/property.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothGattCharacteristicClient : public DBusClient {
 public:
  
  struct Properties : public dbus::PropertySet {
    
    dbus::Property<std::string> uuid;

    
    
    dbus::Property<dbus::ObjectPath> service;

    
    
    dbus::Property<bool> notifying;

    
    
    
    dbus::Property<std::vector<std::string> > flags;

    
    
    dbus::Property<std::vector<dbus::ObjectPath> > descriptors;

    Properties(dbus::ObjectProxy* object_proxy,
               const std::string& interface_name,
               const PropertyChangedCallback& callback);
    virtual ~Properties();
  };

  
  class Observer {
   public:
    virtual ~Observer() {}

    
    
    virtual void GattCharacteristicAdded(const dbus::ObjectPath& object_path) {}

    
    
    virtual void GattCharacteristicRemoved(
        const dbus::ObjectPath& object_path) {}

    
    
    virtual void GattCharacteristicPropertyChanged(
        const dbus::ObjectPath& object_path,
        const std::string& property_name) {}

    
    
    
    virtual void GattCharacteristicValueUpdated(
        const dbus::ObjectPath& object_path,
        const std::vector<uint8>& value) {}
  };

  
  typedef base::Callback<void(const std::string& error_name,
                              const std::string& error_message)> ErrorCallback;
  typedef base::Callback<void(const std::vector<uint8>& value)> ValueCallback;

  virtual ~BluetoothGattCharacteristicClient();

  
  
  
  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;

  
  virtual std::vector<dbus::ObjectPath> GetCharacteristics() = 0;

  
  
  virtual Properties* GetProperties(const dbus::ObjectPath& object_path) = 0;

  
  
  
  virtual void ReadValue(const dbus::ObjectPath& object_path,
                         const ValueCallback& callback,
                         const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void WriteValue(const dbus::ObjectPath& object_path,
                          const std::vector<uint8>& value,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void StartNotify(const dbus::ObjectPath& object_path,
                           const base::Closure& callback,
                           const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void StopNotify(const dbus::ObjectPath& object_path,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) = 0;

  
  static BluetoothGattCharacteristicClient* Create();

  
  static const char kNoResponseError[];
  static const char kUnknownCharacteristicError[];

 protected:
  BluetoothGattCharacteristicClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattCharacteristicClient);
};

}  

#endif  
