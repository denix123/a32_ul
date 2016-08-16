// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_DESCRIPTOR_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_DESCRIPTOR_CLIENT_H_

#include <map>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/bluetooth_gatt_descriptor_client.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeBluetoothGattDescriptorClient
    : public BluetoothGattDescriptorClient {
 public:
  struct Properties : public BluetoothGattDescriptorClient::Properties {
    explicit Properties(const PropertyChangedCallback& callback);
    virtual ~Properties();

    
    virtual void Get(dbus::PropertyBase* property,
                     dbus::PropertySet::GetCallback callback) OVERRIDE;
    virtual void GetAll() OVERRIDE;
    virtual void Set(dbus::PropertyBase* property,
                     dbus::PropertySet::SetCallback callback) OVERRIDE;
  };

  FakeBluetoothGattDescriptorClient();
  virtual ~FakeBluetoothGattDescriptorClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;

  
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetDescriptors() OVERRIDE;
  virtual Properties* GetProperties(const dbus::ObjectPath& object_path)
      OVERRIDE;
  virtual void ReadValue(const dbus::ObjectPath& object_path,
                         const ValueCallback& callback,
                         const ErrorCallback& error_callback) OVERRIDE;
  virtual void WriteValue(const dbus::ObjectPath& object_path,
                          const std::vector<uint8>& value,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) OVERRIDE;

  
  
  
  
  
  
  dbus::ObjectPath ExposeDescriptor(const dbus::ObjectPath& characteristic_path,
                                    const std::string& uuid);
  void HideDescriptor(const dbus::ObjectPath& descriptor_path);

  
  static const char kClientCharacteristicConfigurationPathComponent[];
  static const char kClientCharacteristicConfigurationUUID[];

 private:
  
  void OnPropertyChanged(const dbus::ObjectPath& object_path,
                         const std::string& property_name);

  
  void NotifyDescriptorAdded(const dbus::ObjectPath& object_path);
  void NotifyDescriptorRemoved(const dbus::ObjectPath& object_path);

  
  struct DescriptorData {
    DescriptorData();
    ~DescriptorData();

    scoped_ptr<Properties> properties;
    std::vector<uint8> value;
  };
  typedef std::map<dbus::ObjectPath, DescriptorData*> PropertiesMap;
  PropertiesMap properties_;

  
  ObserverList<Observer> observers_;

  
  
  
  
  base::WeakPtrFactory<FakeBluetoothGattDescriptorClient>
      weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(FakeBluetoothGattDescriptorClient);
};

}  

#endif  
