// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_DEVICE_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_DEVICE_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/strings/string16.h"
#include "device/bluetooth/bluetooth_uuid.h"
#include "net/base/net_log.h"

namespace device {

class BluetoothGattConnection;
class BluetoothGattService;
class BluetoothSocket;
class BluetoothUUID;

class BluetoothDevice {
 public:
  
  
  
  enum VendorIDSource {
    VENDOR_ID_UNKNOWN,
    VENDOR_ID_BLUETOOTH,
    VENDOR_ID_USB
  };

  
  
  
  enum DeviceType {
    DEVICE_UNKNOWN,
    DEVICE_COMPUTER,
    DEVICE_PHONE,
    DEVICE_MODEM,
    DEVICE_AUDIO,
    DEVICE_CAR_AUDIO,
    DEVICE_VIDEO,
    DEVICE_PERIPHERAL,
    DEVICE_JOYSTICK,
    DEVICE_GAMEPAD,
    DEVICE_KEYBOARD,
    DEVICE_MOUSE,
    DEVICE_TABLET,
    DEVICE_KEYBOARD_MOUSE_COMBO
  };

  
  static const int kUnknownPower = 127;

  
  
  enum ConnectErrorCode {
    ERROR_UNKNOWN,
    ERROR_INPROGRESS,
    ERROR_FAILED,
    ERROR_AUTH_FAILED,
    ERROR_AUTH_CANCELED,
    ERROR_AUTH_REJECTED,
    ERROR_AUTH_TIMEOUT,
    ERROR_UNSUPPORTED_DEVICE
  };

  
  class PairingDelegate {
   public:
    virtual ~PairingDelegate() {}

    
    
    
    
    
    
    
    
    virtual void RequestPinCode(BluetoothDevice* device) = 0;

    
    
    
    
    
    
    
    
    
    virtual void RequestPasskey(BluetoothDevice* device) = 0;

    
    
    
    
    
    
    
    virtual void DisplayPinCode(BluetoothDevice* device,
                                const std::string& pincode) = 0;

    
    
    
    
    
    
    
    
    virtual void DisplayPasskey(BluetoothDevice* device,
                                uint32 passkey) = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    virtual void KeysEntered(BluetoothDevice* device,
                             uint32 entered) = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    virtual void ConfirmPasskey(BluetoothDevice* device,
                                uint32 passkey) = 0;

    
    
    
    
    
    
    
    virtual void AuthorizePairing(BluetoothDevice* device) = 0;
  };

  virtual ~BluetoothDevice();

  
  
  virtual uint32 GetBluetoothClass() const = 0;

  
  
  virtual std::string GetAddress() const = 0;

  
  
  virtual VendorIDSource GetVendorIDSource() const = 0;

  
  virtual uint16 GetVendorID() const = 0;

  
  virtual uint16 GetProductID() const = 0;

  
  
  virtual uint16 GetDeviceID() const = 0;

  
  
  
  virtual base::string16 GetName() const;

  
  
  
  
  DeviceType GetDeviceType() const;

  
  
  
  
  
  
  
  virtual int GetRSSI() const = 0;

  
  
  
  
  
  
  
  
  
  
  virtual int GetCurrentHostTransmitPower() const = 0;
  virtual int GetMaximumHostTransmitPower() const = 0;

  
  
  bool IsPairable() const;

  
  virtual bool IsPaired() const = 0;

  
  
  
  
  
  
  virtual bool IsConnected() const = 0;

  
  
  virtual bool IsConnectable() const = 0;

  
  
  
  virtual bool IsConnecting() const = 0;

  
  
  bool IsTrustable() const;

  
  
  
  
  typedef std::vector<BluetoothUUID> UUIDList;
  virtual UUIDList GetUUIDs() const = 0;

  
  
  typedef base::Callback<void()> ErrorCallback;

  
  
  
  typedef base::Callback<void(enum ConnectErrorCode)> ConnectErrorCallback;

  
  
  virtual bool ExpectingPinCode() const = 0;

  
  
  virtual bool ExpectingPasskey() const = 0;

  
  
  virtual bool ExpectingConfirmation() const = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Connect(PairingDelegate* pairing_delegate,
                       const base::Closure& callback,
                       const ConnectErrorCallback& error_callback) = 0;

  
  
  
  
  virtual void SetPinCode(const std::string& pincode) = 0;

  
  
  
  
  
  virtual void SetPasskey(uint32 passkey) = 0;

  
  
  virtual void ConfirmPairing() = 0;

  
  virtual void RejectPairing() = 0;

  
  
  virtual void CancelPairing() = 0;

  
  
  
  
  
  virtual void Disconnect(const base::Closure& callback,
                          const ErrorCallback& error_callback) = 0;

  
  
  
  
  
  
  
  virtual void Forget(const ErrorCallback& error_callback) = 0;

  
  
  
  
  
  
  
  typedef base::Callback<void(scoped_refptr<BluetoothSocket>)>
      ConnectToServiceCallback;
  typedef base::Callback<void(const std::string& message)>
      ConnectToServiceErrorCallback;
  virtual void ConnectToService(
      const BluetoothUUID& uuid,
      const ConnectToServiceCallback& callback,
      const ConnectToServiceErrorCallback& error_callback) = 0;

  
  
  
  
  
  
  
  
  
  typedef base::Callback<void(scoped_ptr<BluetoothGattConnection>)>
      GattConnectionCallback;
  virtual void CreateGattConnection(
      const GattConnectionCallback& callback,
      const ConnectErrorCallback& error_callback) = 0;

  
  
  
  virtual void StartConnectionMonitor(const base::Closure& callback,
                                      const ErrorCallback& error_callback) = 0;

  
  virtual std::vector<BluetoothGattService*> GetGattServices() const;

  
  
  virtual BluetoothGattService* GetGattService(
      const std::string& identifier) const;

  
  
  
  static std::string CanonicalizeAddress(const std::string& address);

 protected:
  BluetoothDevice();

  
  virtual std::string GetDeviceName() const = 0;

  
  
  typedef std::map<std::string, BluetoothGattService*> GattServiceMap;
  GattServiceMap gatt_services_;

 private:
  
  
  base::string16 GetAddressWithLocalizedDeviceTypeName() const;
};

}  

#endif  
