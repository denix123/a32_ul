// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_ADAPTER_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_ADAPTER_H_

#include <list>
#include <map>
#include <set>
#include <string>
#include <utility>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "device/bluetooth/bluetooth_device.h"

namespace device {

class BluetoothDiscoverySession;
class BluetoothGattCharacteristic;
class BluetoothGattDescriptor;
class BluetoothGattService;
class BluetoothSocket;
class BluetoothUUID;

class BluetoothAdapter : public base::RefCounted<BluetoothAdapter> {
 public:
  
  class Observer {
   public:
    virtual ~Observer() {}

    
    
    
    virtual void AdapterPresentChanged(BluetoothAdapter* adapter,
                                       bool present) {}

    
    
    
    virtual void AdapterPoweredChanged(BluetoothAdapter* adapter,
                                       bool powered) {}

    
    
    
    virtual void AdapterDiscoverableChanged(BluetoothAdapter* adapter,
                                           bool discoverable) {}

    
    
    
    virtual void AdapterDiscoveringChanged(BluetoothAdapter* adapter,
                                           bool discovering) {}

    
    
    
    virtual void DeviceAdded(BluetoothAdapter* adapter,
                             BluetoothDevice* device) {}

    
    
    
    virtual void DeviceChanged(BluetoothAdapter* adapter,
                               BluetoothDevice* device) {}

    
    
    
    
    virtual void DeviceRemoved(BluetoothAdapter* adapter,
                               BluetoothDevice* device) {}

    
    
    
    virtual void GattServiceAdded(BluetoothAdapter* adapter,
                                  BluetoothDevice* device,
                                  BluetoothGattService* service) {}

    
    
    
    virtual void GattServiceRemoved(BluetoothAdapter* adapter,
                                    BluetoothDevice* device,
                                    BluetoothGattService* service) {}

    
    
    
    
    virtual void GattDiscoveryCompleteForService(
        BluetoothAdapter* adapter,
        BluetoothGattService* service) {}

    
    
    
    
    
    virtual void GattServiceChanged(BluetoothAdapter* adapter,
                                    BluetoothGattService* service) {}

    
    
    
    
    
    
    
    
    
    
    virtual void GattCharacteristicAdded(
        BluetoothAdapter* adapter,
        BluetoothGattCharacteristic* characteristic) {}

    
    
    virtual void GattCharacteristicRemoved(
        BluetoothAdapter* adapter,
        BluetoothGattCharacteristic* characteristic) {}

    
    
    
    
    virtual void GattDescriptorAdded(BluetoothAdapter* adapter,
                                     BluetoothGattDescriptor* descriptor) {}

    
    
    virtual void GattDescriptorRemoved(BluetoothAdapter* adapter,
                                       BluetoothGattDescriptor* descriptor) {}

    
    
    
    virtual void GattCharacteristicValueChanged(
        BluetoothAdapter* adapter,
        BluetoothGattCharacteristic* characteristic,
        const std::vector<uint8>& value) {}

    
    virtual void GattDescriptorValueChanged(BluetoothAdapter* adapter,
                                            BluetoothGattDescriptor* descriptor,
                                            const std::vector<uint8>& value) {}
  };

  
  struct ServiceOptions {
    ServiceOptions();
    ~ServiceOptions();

    scoped_ptr<int> channel;
    scoped_ptr<int> psm;
    scoped_ptr<std::string> name;
  };

  
  
  typedef base::Closure ErrorCallback;

  
  
  typedef base::Callback<void()> InitCallback;

  
  
  
  
  
  
  static base::WeakPtr<BluetoothAdapter> CreateAdapter(
      const InitCallback& init_callback);

  
  base::WeakPtr<BluetoothAdapter> GetWeakPtrForTesting();

  
  
  
  virtual void AddObserver(BluetoothAdapter::Observer* observer) = 0;
  virtual void RemoveObserver(
      BluetoothAdapter::Observer* observer) = 0;

  
  
  virtual std::string GetAddress() const = 0;

  
  virtual std::string GetName() const = 0;

  
  
  virtual void SetName(const std::string& name,
                       const base::Closure& callback,
                       const ErrorCallback& error_callback) = 0;

  
  virtual bool IsInitialized() const = 0;

  
  
  
  virtual bool IsPresent() const = 0;

  
  virtual bool IsPowered() const = 0;

  
  
  
  virtual void SetPowered(bool powered,
                          const base::Closure& callback,
                          const ErrorCallback& error_callback) = 0;

  
  virtual bool IsDiscoverable() const = 0;

  
  
  
  
  virtual void SetDiscoverable(bool discoverable,
                               const base::Closure& callback,
                               const ErrorCallback& error_callback) = 0;

  
  virtual bool IsDiscovering() const = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  typedef base::Callback<void(scoped_ptr<BluetoothDiscoverySession>)>
      DiscoverySessionCallback;
  virtual void StartDiscoverySession(const DiscoverySessionCallback& callback,
                                     const ErrorCallback& error_callback);

  
  
  
  typedef std::vector<BluetoothDevice*> DeviceList;
  virtual DeviceList GetDevices();
  typedef std::vector<const BluetoothDevice*> ConstDeviceList;
  virtual ConstDeviceList GetDevices() const;

  
  
  virtual BluetoothDevice* GetDevice(const std::string& address);
  virtual const BluetoothDevice* GetDevice(const std::string& address) const;

  
  
  enum PairingDelegatePriority {
    PAIRING_DELEGATE_PRIORITY_LOW,
    PAIRING_DELEGATE_PRIORITY_HIGH
  };

  
  
  
  
  
  
  
  virtual void AddPairingDelegate(
      BluetoothDevice::PairingDelegate* pairing_delegate,
      PairingDelegatePriority priority);

  
  virtual void RemovePairingDelegate(
      BluetoothDevice::PairingDelegate* pairing_delegate);

  
  
  
  virtual BluetoothDevice::PairingDelegate* DefaultPairingDelegate();

  
  
  
  
  
  
  
  typedef base::Callback<void(scoped_refptr<BluetoothSocket>)>
      CreateServiceCallback;
  typedef base::Callback<void(const std::string& message)>
      CreateServiceErrorCallback;
  virtual void CreateRfcommService(
      const BluetoothUUID& uuid,
      const ServiceOptions& options,
      const CreateServiceCallback& callback,
      const CreateServiceErrorCallback& error_callback) = 0;

  
  
  
  
  
  
  
  virtual void CreateL2capService(
      const BluetoothUUID& uuid,
      const ServiceOptions& options,
      const CreateServiceCallback& callback,
      const CreateServiceErrorCallback& error_callback) = 0;

 protected:
  friend class base::RefCounted<BluetoothAdapter>;
  friend class BluetoothDiscoverySession;
  BluetoothAdapter();
  virtual ~BluetoothAdapter();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void AddDiscoverySession(const base::Closure& callback,
                                   const ErrorCallback& error_callback) = 0;
  virtual void RemoveDiscoverySession(const base::Closure& callback,
                                      const ErrorCallback& error_callback) = 0;

  
  
  
  virtual void RemovePairingDelegateInternal(
      BluetoothDevice::PairingDelegate* pairing_delegate) = 0;

  
  void OnStartDiscoverySession(const DiscoverySessionCallback& callback);

  
  
  
  void MarkDiscoverySessionsAsInactive();

  
  
  
  void DiscoverySessionBecameInactive(
      BluetoothDiscoverySession* discovery_session);

  
  
  
  
  typedef std::map<const std::string, BluetoothDevice*> DevicesMap;
  DevicesMap devices_;

  
  typedef std::pair<BluetoothDevice::PairingDelegate*,
                    PairingDelegatePriority> PairingDelegatePair;
  std::list<PairingDelegatePair> pairing_delegates_;

 private:
  
  
  
  
  
  
  std::set<BluetoothDiscoverySession*> discovery_sessions_;

  
  
  base::WeakPtrFactory<BluetoothAdapter> weak_ptr_factory_;
};

}  

#endif  
