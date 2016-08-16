// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_GATT_DESCRIPTOR_CLIENT_H_
#define CHROMEOS_DBUS_BLUETOOTH_GATT_DESCRIPTOR_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client.h"
#include "dbus/object_path.h"
#include "dbus/property.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothGattDescriptorClient : public DBusClient {
 public:
  
  struct Properties : public dbus::PropertySet {
    
    dbus::Property<std::string> uuid;

    
    
    dbus::Property<dbus::ObjectPath> characteristic;

    Properties(dbus::ObjectProxy* object_proxy,
               const std::string& interface_name,
               const PropertyChangedCallback& callback);
    virtual ~Properties();
  };

  
  
  class Observer {
   public:
    virtual ~Observer() {}

    
    
    virtual void GattDescriptorAdded(const dbus::ObjectPath& object_path) {}

    
    
    virtual void GattDescriptorRemoved(const dbus::ObjectPath& object_path) {}

    
    
    virtual void GattDescriptorPropertyChanged(
        const dbus::ObjectPath& object_path,
        const std::string& property_name) {}
  };

  
  typedef base::Callback<void(const std::string& error_name,
                              const std::string& error_message)> ErrorCallback;
  typedef base::Callback<void(const std::vector<uint8>& value)> ValueCallback;

  virtual ~BluetoothGattDescriptorClient();

  
  
  
  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;

  
  virtual std::vector<dbus::ObjectPath> GetDescriptors() = 0;

  
  
  virtual Properties* GetProperties(const dbus::ObjectPath& object_path) = 0;

  
  
  
  virtual void ReadValue(const dbus::ObjectPath& object_path,
                         const ValueCallback& callback,
                         const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void WriteValue(const dbus::ObjectPath& object_path,
                          const std::vector<uint8>& value,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) = 0;

  
  static BluetoothGattDescriptorClient* Create();

  
  static const char kNoResponseError[];
  static const char kUnknownDescriptorError[];

 protected:
  BluetoothGattDescriptorClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattDescriptorClient);
};

}  

#endif  
