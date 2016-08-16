// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LOW_ENERGY_EVENT_ROUTER_H_
#define EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LOW_ENERGY_EVENT_ROUTER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/notification_observer.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_device.h"
#include "device/bluetooth/bluetooth_gatt_service.h"
#include "extensions/common/api/bluetooth_low_energy.h"

namespace base {

class ListValue;

}  

namespace content {

class BrowserContext;

}  

namespace device {

class BluetoothGattNotifySession;

}  

namespace extensions {

class BluetoothLowEnergyConnection;
class BluetoothLowEnergyNotifySession;
class Extension;

class BluetoothLowEnergyEventRouter
    : public device::BluetoothAdapter::Observer {
 public:
  explicit BluetoothLowEnergyEventRouter(content::BrowserContext* context);
  virtual ~BluetoothLowEnergyEventRouter();

  
  enum Status {
    kStatusSuccess = 0,
    kStatusErrorPermissionDenied,
    kStatusErrorNotFound,
    kStatusErrorAlreadyConnected,
    kStatusErrorAlreadyNotifying,
    kStatusErrorNotConnected,
    kStatusErrorNotNotifying,
    kStatusErrorInProgress,
    kStatusErrorFailed
  };

  
  typedef base::Callback<void(Status)> ErrorCallback;

  
  
  bool IsBluetoothSupported() const;

  
  
  
  
  
  bool InitializeAdapterAndInvokeCallback(const base::Closure& callback);

  
  bool HasAdapter() const;

  
  
  
  
  
  
  void Connect(bool persistent,
               const Extension* extension,
               const std::string& device_address,
               const base::Closure& callback,
               const ErrorCallback& error_callback);

  
  
  
  
  
  void Disconnect(const Extension* extension,
                  const std::string& device_address,
                  const base::Closure& callback,
                  const ErrorCallback& error_callback);

  
  
  
  
  
  
  
  typedef std::vector<linked_ptr<core_api::bluetooth_low_energy::Service> >
      ServiceList;
  bool GetServices(const std::string& device_address,
                   ServiceList* out_services) const;

  
  
  Status GetService(const std::string& instance_id,
                    core_api::bluetooth_low_energy::Service* out_service) const;

  
  
  
  
  
  Status GetIncludedServices(const std::string& instance_id,
                             ServiceList* out_services) const;

  
  
  
  
  
  
  
  
  typedef std::vector<
      linked_ptr<core_api::bluetooth_low_energy::Characteristic> >
      CharacteristicList;
  Status GetCharacteristics(const Extension* extension,
                            const std::string& instance_id,
                            CharacteristicList* out_characteristics) const;

  
  
  
  Status GetCharacteristic(
      const Extension* extension,
      const std::string& instance_id,
      core_api::bluetooth_low_energy::Characteristic* out_characteristic) const;

  
  
  
  
  
  
  
  typedef std::vector<linked_ptr<core_api::bluetooth_low_energy::Descriptor> >
      DescriptorList;
  Status GetDescriptors(const Extension* extension,
                        const std::string& instance_id,
                        DescriptorList* out_descriptors) const;

  
  
  
  Status GetDescriptor(
      const Extension* extension,
      const std::string& instance_id,
      core_api::bluetooth_low_energy::Descriptor* out_descriptor) const;

  
  
  
  void ReadCharacteristicValue(const Extension* extension,
                               const std::string& instance_id,
                               const base::Closure& callback,
                               const ErrorCallback& error_callback);

  
  
  
  void WriteCharacteristicValue(const Extension* extension,
                                const std::string& instance_id,
                                const std::vector<uint8>& value,
                                const base::Closure& callback,
                                const ErrorCallback& error_callback);

  
  
  
  
  void StartCharacteristicNotifications(bool persistent,
                                        const Extension* extension,
                                        const std::string& instance_id,
                                        const base::Closure& callback,
                                        const ErrorCallback& error_callback);

  
  
  
  void StopCharacteristicNotifications(const Extension* extension,
                                       const std::string& instance_id,
                                       const base::Closure& callback,
                                       const ErrorCallback& error_callback);

  
  
  
  void ReadDescriptorValue(const Extension* extension,
                           const std::string& instance_id,
                           const base::Closure& callback,
                           const ErrorCallback& error_callback);

  
  
  
  void WriteDescriptorValue(const Extension* extension,
                            const std::string& instance_id,
                            const std::vector<uint8>& value,
                            const base::Closure& callback,
                            const ErrorCallback& error_callback);

  
  void SetAdapterForTesting(device::BluetoothAdapter* adapter);

  
  virtual void GattServiceAdded(device::BluetoothAdapter* adapter,
                                device::BluetoothDevice* device,
                                device::BluetoothGattService* service) OVERRIDE;
  virtual void GattServiceRemoved(
      device::BluetoothAdapter* adapter,
      device::BluetoothDevice* device,
      device::BluetoothGattService* service) OVERRIDE;
  virtual void GattDiscoveryCompleteForService(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattService* service) OVERRIDE;
  virtual void GattServiceChanged(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattService* service) OVERRIDE;
  virtual void GattCharacteristicAdded(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattCharacteristic* characteristic) OVERRIDE;
  virtual void GattCharacteristicRemoved(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattCharacteristic* characteristic) OVERRIDE;
  virtual void GattDescriptorAdded(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattDescriptor* descriptor) OVERRIDE;
  virtual void GattDescriptorRemoved(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattDescriptor* descriptor) OVERRIDE;
  virtual void GattCharacteristicValueChanged(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattCharacteristic* characteristic,
      const std::vector<uint8>& value) OVERRIDE;
  virtual void GattDescriptorValueChanged(
      device::BluetoothAdapter* adapter,
      device::BluetoothGattDescriptor* descriptor,
      const std::vector<uint8>& value) OVERRIDE;

 private:
  
  void OnGetAdapter(const base::Closure& callback,
                    scoped_refptr<device::BluetoothAdapter> adapter);

  
  
  void InitializeIdentifierMappings();

  
  
  
  
  
  
  void DispatchEventToExtensionsWithPermission(
      const std::string& event_name,
      const device::BluetoothUUID& uuid,
      const std::string& characteristic_id,
      scoped_ptr<base::ListValue> args);

  
  
  device::BluetoothGattService* FindServiceById(
      const std::string& instance_id) const;

  
  
  device::BluetoothGattCharacteristic* FindCharacteristicById(
      const std::string& instance_id) const;

  
  
  device::BluetoothGattDescriptor* FindDescriptorById(
      const std::string& instance_id) const;

  
  
  void OnValueSuccess(const base::Closure& callback,
                      const std::vector<uint8>& value);

  
  void OnCreateGattConnection(
      bool persistent,
      const std::string& extension_id,
      const std::string& device_address,
      const base::Closure& callback,
      scoped_ptr<device::BluetoothGattConnection> connection);

  
  void OnDisconnect(const std::string& extension_id,
                    const std::string& device_address,
                    const base::Closure& callback);

  
  
  void OnError(const ErrorCallback& error_callback);

  
  void OnConnectError(const std::string& extension_id,
                      const std::string& device_address,
                      const ErrorCallback& error_callback,
                      device::BluetoothDevice::ConnectErrorCode error_code);

  
  
  void OnStartNotifySession(
      bool persistent,
      const std::string& extension_id,
      const std::string& characteristic_id,
      const base::Closure& callback,
      scoped_ptr<device::BluetoothGattNotifySession> session);

  
  
  void OnStartNotifySessionError(const std::string& extension_id,
                                 const std::string& characteristic_id,
                                 const ErrorCallback& error_callback);

  
  void OnStopNotifySession(const std::string& extension_id,
                           const std::string& characteristic_id,
                           const base::Closure& callback);

  
  
  
  BluetoothLowEnergyConnection* FindConnection(
      const std::string& extension_id,
      const std::string& device_address);

  
  
  
  bool RemoveConnection(const std::string& extension_id,
                        const std::string& device_address);

  
  
  
  BluetoothLowEnergyNotifySession* FindNotifySession(
      const std::string& extension_id,
      const std::string& characteristic_id);

  
  
  
  
  bool RemoveNotifySession(const std::string& extension_id,
                           const std::string& characteristic_id);

  
  
  
  
  
  
  
  
  
  
  
  
  typedef std::map<std::string, std::string> InstanceIdMap;
  InstanceIdMap service_id_to_device_address_;
  InstanceIdMap chrc_id_to_service_id_;
  InstanceIdMap desc_id_to_chrc_id_;

  
  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  
  
  std::set<std::string> connecting_devices_;
  std::set<std::string> disconnecting_devices_;

  
  
  std::set<std::string> pending_session_calls_;

  
  content::BrowserContext* browser_context_;

  
  
  base::WeakPtrFactory<BluetoothLowEnergyEventRouter> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothLowEnergyEventRouter);
};

}  

#endif  
