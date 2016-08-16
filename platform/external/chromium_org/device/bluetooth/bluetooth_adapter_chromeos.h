// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_ADAPTER_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_ADAPTER_CHROMEOS_H_

#include <queue>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "chromeos/dbus/bluetooth_adapter_client.h"
#include "chromeos/dbus/bluetooth_agent_service_provider.h"
#include "chromeos/dbus/bluetooth_device_client.h"
#include "chromeos/dbus/bluetooth_input_client.h"
#include "dbus/object_path.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_device.h"

namespace device {
class BluetoothSocketThread;
}  

namespace chromeos {

class BluetoothChromeOSTest;
class BluetoothDeviceChromeOS;
class BluetoothPairingChromeOS;
class BluetoothRemoteGattCharacteristicChromeOS;
class BluetoothRemoteGattDescriptorChromeOS;
class BluetoothRemoteGattServiceChromeOS;

class BluetoothAdapterChromeOS
    : public device::BluetoothAdapter,
      public chromeos::BluetoothAdapterClient::Observer,
      public chromeos::BluetoothDeviceClient::Observer,
      public chromeos::BluetoothInputClient::Observer,
      public chromeos::BluetoothAgentServiceProvider::Delegate {
 public:
  static base::WeakPtr<BluetoothAdapter> CreateAdapter();

  
  virtual void AddObserver(
      device::BluetoothAdapter::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(
      device::BluetoothAdapter::Observer* observer) OVERRIDE;
  virtual std::string GetAddress() const OVERRIDE;
  virtual std::string GetName() const OVERRIDE;
  virtual void SetName(const std::string& name,
                       const base::Closure& callback,
                       const ErrorCallback& error_callback) OVERRIDE;
  virtual bool IsInitialized() const OVERRIDE;
  virtual bool IsPresent() const OVERRIDE;
  virtual bool IsPowered() const OVERRIDE;
  virtual void SetPowered(
      bool powered,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual bool IsDiscoverable() const OVERRIDE;
  virtual void SetDiscoverable(
      bool discoverable,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual bool IsDiscovering() const OVERRIDE;
  virtual void CreateRfcommService(
      const device::BluetoothUUID& uuid,
      const ServiceOptions& options,
      const CreateServiceCallback& callback,
      const CreateServiceErrorCallback& error_callback) OVERRIDE;
  virtual void CreateL2capService(
      const device::BluetoothUUID& uuid,
      const ServiceOptions& options,
      const CreateServiceCallback& callback,
      const CreateServiceErrorCallback& error_callback) OVERRIDE;

  
  
  BluetoothDeviceChromeOS* GetDeviceWithPath(
      const dbus::ObjectPath& object_path);

  
  
  void NotifyDeviceChanged(BluetoothDeviceChromeOS* device);

  
  
  void NotifyGattServiceAdded(BluetoothRemoteGattServiceChromeOS* service);
  void NotifyGattServiceRemoved(BluetoothRemoteGattServiceChromeOS* service);
  void NotifyGattServiceChanged(BluetoothRemoteGattServiceChromeOS* service);
  void NotifyGattDiscoveryComplete(BluetoothRemoteGattServiceChromeOS* service);
  void NotifyGattCharacteristicAdded(
      BluetoothRemoteGattCharacteristicChromeOS* characteristic);
  void NotifyGattCharacteristicRemoved(
      BluetoothRemoteGattCharacteristicChromeOS* characteristic);
  void NotifyGattDescriptorAdded(
      BluetoothRemoteGattDescriptorChromeOS* descriptor);
  void NotifyGattDescriptorRemoved(
      BluetoothRemoteGattDescriptorChromeOS* descriptor);
  void NotifyGattCharacteristicValueChanged(
      BluetoothRemoteGattCharacteristicChromeOS* characteristic,
      const std::vector<uint8>& value);
  void NotifyGattDescriptorValueChanged(
      BluetoothRemoteGattDescriptorChromeOS* descriptor,
      const std::vector<uint8>& value);

  
  const dbus::ObjectPath& object_path() const { return object_path_; }

 protected:
  
  virtual void RemovePairingDelegateInternal(
      device::BluetoothDevice::PairingDelegate* pairing_delegate) OVERRIDE;

 private:
  friend class BluetoothChromeOSTest;

  
  
  
  typedef std::pair<base::Closure, ErrorCallback> DiscoveryCallbackPair;
  typedef std::queue<DiscoveryCallbackPair> DiscoveryCallbackQueue;

  BluetoothAdapterChromeOS();
  virtual ~BluetoothAdapterChromeOS();

  
  virtual void AdapterAdded(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void AdapterRemoved(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void AdapterPropertyChanged(
      const dbus::ObjectPath& object_path,
      const std::string& property_name) OVERRIDE;

  
  virtual void DeviceAdded(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void DeviceRemoved(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void DevicePropertyChanged(const dbus::ObjectPath& object_path,
                                     const std::string& property_name) OVERRIDE;

  
  virtual void InputPropertyChanged(const dbus::ObjectPath& object_path,
                                    const std::string& property_name) OVERRIDE;

  
  virtual void Released() OVERRIDE;
  virtual void RequestPinCode(const dbus::ObjectPath& device_path,
                              const PinCodeCallback& callback) OVERRIDE;
  virtual void DisplayPinCode(const dbus::ObjectPath& device_path,
                              const std::string& pincode) OVERRIDE;
  virtual void RequestPasskey(const dbus::ObjectPath& device_path,
                              const PasskeyCallback& callback) OVERRIDE;
  virtual void DisplayPasskey(const dbus::ObjectPath& device_path,
                              uint32 passkey, uint16 entered) OVERRIDE;
  virtual void RequestConfirmation(const dbus::ObjectPath& device_path,
                                   uint32 passkey,
                                   const ConfirmationCallback& callback)
      OVERRIDE;
  virtual void RequestAuthorization(const dbus::ObjectPath& device_path,
                                    const ConfirmationCallback& callback)
      OVERRIDE;
  virtual void AuthorizeService(const dbus::ObjectPath& device_path,
                                const std::string& uuid,
                                const ConfirmationCallback& callback) OVERRIDE;
  virtual void Cancel() OVERRIDE;

  
  
  void OnRegisterAgent();
  void OnRegisterAgentError(const std::string& error_name,
                            const std::string& error_message);

  
  
  void OnRequestDefaultAgent();
  void OnRequestDefaultAgentError(const std::string& error_name,
                                  const std::string& error_message);

  
  
  
  
  
  BluetoothPairingChromeOS* GetPairing(const dbus::ObjectPath& object_path);

  
  
  void SetAdapter(const dbus::ObjectPath& object_path);

  
  void SetDefaultAdapterName();

  
  
  void RemoveAdapter();

  
  void PoweredChanged(bool powered);
  void DiscoverableChanged(bool discoverable);
  void DiscoveringChanged(bool discovering);
  void PresentChanged(bool present);

  
  void OnSetDiscoverable(const base::Closure& callback,
                         const ErrorCallback& error_callback,
                         bool success);

  
  void OnPropertyChangeCompleted(const base::Closure& callback,
                                 const ErrorCallback& error_callback,
                                 bool success);

  
  virtual void AddDiscoverySession(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void RemoveDiscoverySession(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;

  
  void OnStartDiscovery(const base::Closure& callback);
  void OnStartDiscoveryError(const base::Closure& callback,
                             const ErrorCallback& error_callback,
                             const std::string& error_name,
                             const std::string& error_message);

  
  void OnStopDiscovery(const base::Closure& callback);
  void OnStopDiscoveryError(const ErrorCallback& error_callback,
                            const std::string& error_name,
                            const std::string& error_message);

  
  
  
  
  void ProcessQueuedDiscoveryRequests();

  
  int num_discovery_sessions_;

  
  bool discovery_request_pending_;

  
  
  
  
  
  
  
  
  
  DiscoveryCallbackQueue discovery_request_queue_;

  
  dbus::ObjectPath object_path_;

  
  ObserverList<device::BluetoothAdapter::Observer> observers_;

  
  
  scoped_ptr<BluetoothAgentServiceProvider> agent_;

  
  scoped_refptr<base::SequencedTaskRunner> ui_task_runner_;
  scoped_refptr<device::BluetoothSocketThread> socket_thread_;

  
  
  base::WeakPtrFactory<BluetoothAdapterChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothAdapterChromeOS);
};

}  

#endif  
