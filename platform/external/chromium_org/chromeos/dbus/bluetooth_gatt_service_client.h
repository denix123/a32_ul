// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_BLUETOOTH_GATT_SERVICE_CLIENT_H_
#define CHROMEOS_DBUS_BLUETOOTH_GATT_SERVICE_CLIENT_H_

#include <string>
#include <vector>

#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client.h"
#include "dbus/object_path.h"
#include "dbus/property.h"

namespace chromeos {

class CHROMEOS_EXPORT BluetoothGattServiceClient : public DBusClient {
 public:
  
  struct Properties : public dbus::PropertySet {
    
    dbus::Property<std::string> uuid;

    
    dbus::Property<dbus::ObjectPath> device;

    
    dbus::Property<bool> primary;

    
    
    dbus::Property<std::vector<dbus::ObjectPath> > characteristics;

    
    
    dbus::Property<std::vector<dbus::ObjectPath> > includes;

    Properties(dbus::ObjectProxy* object_proxy,
               const std::string& interface_name,
               const PropertyChangedCallback& callback);
    virtual ~Properties();
  };

  
  class Observer {
   public:
    virtual ~Observer() {}

    
    
    virtual void GattServiceAdded(const dbus::ObjectPath& object_path) {}

    
    
    virtual void GattServiceRemoved(const dbus::ObjectPath& object_path) {}

    
    
    virtual void GattServicePropertyChanged(const dbus::ObjectPath& object_path,
                                            const std::string& property_name) {}
  };

  virtual ~BluetoothGattServiceClient();

  
  
  
  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;

  
  virtual std::vector<dbus::ObjectPath> GetServices() = 0;

  
  
  virtual Properties* GetProperties(const dbus::ObjectPath& object_path) = 0;

  
  static BluetoothGattServiceClient* Create();

 protected:
  BluetoothGattServiceClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothGattServiceClient);
};

}  

#endif  
