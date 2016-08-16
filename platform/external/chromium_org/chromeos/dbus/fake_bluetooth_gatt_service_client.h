// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_SERVICE_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_SERVICE_CLIENT_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/bluetooth_gatt_service_client.h"
#include "dbus/object_path.h"
#include "dbus/property.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeBluetoothGattServiceClient
    : public BluetoothGattServiceClient {
 public:
  struct Properties : public BluetoothGattServiceClient::Properties {
    explicit Properties(const PropertyChangedCallback& callback);
    virtual ~Properties();

    
    virtual void Get(dbus::PropertyBase* property,
                     dbus::PropertySet::GetCallback callback) OVERRIDE;
    virtual void GetAll() OVERRIDE;
    virtual void Set(dbus::PropertyBase* property,
                     dbus::PropertySet::SetCallback callback) OVERRIDE;
  };

  FakeBluetoothGattServiceClient();
  virtual ~FakeBluetoothGattServiceClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;

  
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetServices() OVERRIDE;
  virtual Properties* GetProperties(const dbus::ObjectPath& object_path)
      OVERRIDE;

  
  
  
  void ExposeHeartRateService(const dbus::ObjectPath& device_path);
  void HideHeartRateService();

  
  bool IsHeartRateVisible() const;

  
  
  dbus::ObjectPath GetHeartRateServicePath() const;

  
  
  
  
  
  static const char kHeartRateServicePathComponent[];
  static const char kHeartRateServiceUUID[];

 private:
  
  void OnPropertyChanged(const dbus::ObjectPath& object_path,
                         const std::string& property_name);

  
  void NotifyServiceAdded(const dbus::ObjectPath& object_path);
  void NotifyServiceRemoved(const dbus::ObjectPath& object_path);

  
  
  
  
  void ExposeHeartRateCharacteristics();

  
  
  scoped_ptr<Properties> heart_rate_service_properties_;
  std::string heart_rate_service_path_;

  
  ObserverList<Observer> observers_;

  
  
  
  
  base::WeakPtrFactory<FakeBluetoothGattServiceClient> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(FakeBluetoothGattServiceClient);
};

}  

#endif  
