// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_DEVICE_CHROMEOS_H
#define DEVICE_BLUETOOTH_BLUETOOTH_DEVICE_CHROMEOS_H

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "chromeos/dbus/bluetooth_device_client.h"
#include "chromeos/dbus/bluetooth_gatt_service_client.h"
#include "dbus/object_path.h"
#include "device/bluetooth/bluetooth_device.h"

namespace device {
class BluetoothSocketThread;
}  

namespace chromeos {

class BluetoothAdapterChromeOS;
class BluetoothPairingChromeOS;

class BluetoothDeviceChromeOS
    : public device::BluetoothDevice,
      public BluetoothGattServiceClient::Observer {
 public:
  
  virtual uint32 GetBluetoothClass() const OVERRIDE;
  virtual std::string GetAddress() const OVERRIDE;
  virtual VendorIDSource GetVendorIDSource() const OVERRIDE;
  virtual uint16 GetVendorID() const OVERRIDE;
  virtual uint16 GetProductID() const OVERRIDE;
  virtual uint16 GetDeviceID() const OVERRIDE;
  virtual int GetRSSI() const OVERRIDE;
  virtual int GetCurrentHostTransmitPower() const OVERRIDE;
  virtual int GetMaximumHostTransmitPower() const OVERRIDE;
  virtual bool IsPaired() const OVERRIDE;
  virtual bool IsConnected() const OVERRIDE;
  virtual bool IsConnectable() const OVERRIDE;
  virtual bool IsConnecting() const OVERRIDE;
  virtual UUIDList GetUUIDs() const OVERRIDE;
  virtual bool ExpectingPinCode() const OVERRIDE;
  virtual bool ExpectingPasskey() const OVERRIDE;
  virtual bool ExpectingConfirmation() const OVERRIDE;
  virtual void Connect(
      device::BluetoothDevice::PairingDelegate* pairing_delegate,
      const base::Closure& callback,
      const ConnectErrorCallback& error_callback) OVERRIDE;
  virtual void SetPinCode(const std::string& pincode) OVERRIDE;
  virtual void SetPasskey(uint32 passkey) OVERRIDE;
  virtual void ConfirmPairing() OVERRIDE;
  virtual void RejectPairing() OVERRIDE;
  virtual void CancelPairing() OVERRIDE;
  virtual void Disconnect(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void Forget(const ErrorCallback& error_callback) OVERRIDE;
  virtual void ConnectToService(
      const device::BluetoothUUID& uuid,
      const ConnectToServiceCallback& callback,
      const ConnectToServiceErrorCallback& error_callback) OVERRIDE;
  virtual void CreateGattConnection(
      const GattConnectionCallback& callback,
      const ConnectErrorCallback& error_callback) OVERRIDE;
  virtual void StartConnectionMonitor(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;

  
  
  
  
  
  
  
  
  void ConnectToServiceInsecurely(
    const device::BluetoothUUID& uuid,
    const ConnectToServiceCallback& callback,
    const ConnectToServiceErrorCallback& error_callback);

  
  
  
  BluetoothPairingChromeOS* BeginPairing(
      BluetoothDevice::PairingDelegate* pairing_delegate);

  
  
  void EndPairing();

  
  BluetoothPairingChromeOS* GetPairing() const;

  
  const dbus::ObjectPath& object_path() const { return object_path_; }

 protected:
   
  virtual std::string GetDeviceName() const OVERRIDE;

 private:
  friend class BluetoothAdapterChromeOS;

  BluetoothDeviceChromeOS(
      BluetoothAdapterChromeOS* adapter,
      const dbus::ObjectPath& object_path,
      scoped_refptr<base::SequencedTaskRunner> ui_task_runner,
      scoped_refptr<device::BluetoothSocketThread> socket_thread);
  virtual ~BluetoothDeviceChromeOS();

  
  virtual void GattServiceAdded(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void GattServiceRemoved(const dbus::ObjectPath& object_path) OVERRIDE;

  
  
  void ConnectInternal(bool after_pairing,
                       const base::Closure& callback,
                       const ConnectErrorCallback& error_callback);
  void OnConnect(bool after_pairing,
                 const base::Closure& callback);
  void OnCreateGattConnection(const GattConnectionCallback& callback);
  void OnConnectError(bool after_pairing,
                      const ConnectErrorCallback& error_callback,
                      const std::string& error_name,
                      const std::string& error_message);

  
  void OnPair(const base::Closure& callback,
              const ConnectErrorCallback& error_callback);
  void OnPairError(const ConnectErrorCallback& error_callback,
                   const std::string& error_name,
                   const std::string& error_message);

  
  
  
  void OnCancelPairingError(const std::string& error_name,
                            const std::string& error_message);

  
  
  
  
  void SetTrusted();
  void OnSetTrusted(bool success);

  
  
  void OnDisconnect(const base::Closure& callback);
  void OnDisconnectError(const ErrorCallback& error_callback,
                         const std::string& error_name,
                         const std::string& error_message);

  
  
  
  void OnForgetError(const ErrorCallback& error_callback,
                     const std::string& error_name,
                     const std::string& error_message);

  
  
  void OnStartConnectionMonitor(const base::Closure& callback);
  void OnStartConnectionMonitorError(const ErrorCallback& error_callback,
                                     const std::string& error_name,
                                     const std::string& error_message);

  
  BluetoothAdapterChromeOS* adapter_;

  
  dbus::ObjectPath object_path_;

  
  int num_connecting_calls_;

  
  
  bool connection_monitor_started_;

  
  scoped_refptr<base::SequencedTaskRunner> ui_task_runner_;
  scoped_refptr<device::BluetoothSocketThread> socket_thread_;

  
  
  
  scoped_ptr<BluetoothPairingChromeOS> pairing_;

  
  
  base::WeakPtrFactory<BluetoothDeviceChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothDeviceChromeOS);
};

}  

#endif  
