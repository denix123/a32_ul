// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_CHARACTERISTIC_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_BLUETOOTH_GATT_CHARACTERISTIC_CLIENT_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/bluetooth_gatt_characteristic_client.h"
#include "dbus/object_path.h"
#include "dbus/property.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeBluetoothGattCharacteristicClient
    : public BluetoothGattCharacteristicClient {
 public:
  struct Properties : public BluetoothGattCharacteristicClient::Properties {
    explicit Properties(const PropertyChangedCallback& callback);
    virtual ~Properties();

    
    virtual void Get(dbus::PropertyBase* property,
                     dbus::PropertySet::GetCallback callback) OVERRIDE;
    virtual void GetAll() OVERRIDE;
    virtual void Set(dbus::PropertyBase* property,
                     dbus::PropertySet::SetCallback callback) OVERRIDE;
  };

  FakeBluetoothGattCharacteristicClient();
  virtual ~FakeBluetoothGattCharacteristicClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;

  
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetCharacteristics() OVERRIDE;
  virtual Properties* GetProperties(const dbus::ObjectPath& object_path)
      OVERRIDE;
  virtual void ReadValue(const dbus::ObjectPath& object_path,
                         const ValueCallback& callback,
                         const ErrorCallback& error_callback) OVERRIDE;
  virtual void WriteValue(const dbus::ObjectPath& object_path,
                          const std::vector<uint8>& value,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) OVERRIDE;
  virtual void StartNotify(const dbus::ObjectPath& object_path,
                           const base::Closure& callback,
                           const ErrorCallback& error_callback) OVERRIDE;
  virtual void StopNotify(const dbus::ObjectPath& object_path,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) OVERRIDE;

  
  
  
  void ExposeHeartRateCharacteristics(const dbus::ObjectPath& service_path);
  void HideHeartRateCharacteristics();

  
  
  bool IsHeartRateVisible() const;

  
  
  dbus::ObjectPath GetHeartRateMeasurementPath() const;
  dbus::ObjectPath GetBodySensorLocationPath() const;
  dbus::ObjectPath GetHeartRateControlPointPath() const;

  
  
  static const char kHeartRateMeasurementPathComponent[];
  static const char kHeartRateMeasurementUUID[];
  static const char kBodySensorLocationPathComponent[];
  static const char kBodySensorLocationUUID[];
  static const char kHeartRateControlPointPathComponent[];
  static const char kHeartRateControlPointUUID[];

 private:
  
  void OnPropertyChanged(const dbus::ObjectPath& object_path,
                         const std::string& property_name);

  
  void NotifyCharacteristicAdded(const dbus::ObjectPath& object_path);
  void NotifyCharacteristicRemoved(const dbus::ObjectPath& object_path);

  
  
  void ScheduleHeartRateMeasurementValueChange();

  
  
  
  std::vector<uint8> GetHeartRateMeasurementValue();

  
  
  bool heart_rate_visible_;

  
  uint16 calories_burned_;

  
  
  
  scoped_ptr<Properties> heart_rate_measurement_properties_;
  scoped_ptr<Properties> body_sensor_location_properties_;
  scoped_ptr<Properties> heart_rate_control_point_properties_;

  
  
  std::string heart_rate_measurement_path_;
  std::string heart_rate_measurement_ccc_desc_path_;
  std::string body_sensor_location_path_;
  std::string heart_rate_control_point_path_;

  
  ObserverList<Observer> observers_;

  
  
  
  
  base::WeakPtrFactory<FakeBluetoothGattCharacteristicClient>
      weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(FakeBluetoothGattCharacteristicClient);
};

}  

#endif  
