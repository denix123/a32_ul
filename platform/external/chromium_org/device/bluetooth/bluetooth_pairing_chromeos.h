// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_PAIRING_CHROMEOS_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_PAIRING_CHROMEOS_H_

#include "chromeos/dbus/bluetooth_agent_service_provider.h"
#include "device/bluetooth/bluetooth_device.h"

namespace chromeos {

class BluetoothDeviceChromeOS;

class BluetoothPairingChromeOS {
 public:
  BluetoothPairingChromeOS(
      BluetoothDeviceChromeOS* device,
      device::BluetoothDevice::PairingDelegate* pairing_delegate);
  ~BluetoothPairingChromeOS();

  
  
  bool ExpectingPasskey() const;

  
  
  bool ExpectingConfirmation() const;

  
  
  
  
  void RequestPinCode(
      const BluetoothAgentServiceProvider::Delegate::PinCodeCallback& callback);

  
  
  bool ExpectingPinCode() const;

  
  
  
  
  void SetPinCode(const std::string& pincode);

  
  
  void DisplayPinCode(const std::string& pincode);

  
  
  
  
  void RequestPasskey(
      const BluetoothAgentServiceProvider::Delegate::PasskeyCallback& callback);

  
  
  
  
  
  void SetPasskey(uint32 passkey);

  
  
  void DisplayPasskey(uint32 passkey);

  
  
  
  void KeysEntered(uint16 entered);

  
  
  
  
  void RequestConfirmation(
      uint32 passkey,
      const BluetoothAgentServiceProvider::Delegate::ConfirmationCallback&
          callback);

  
  
  
  
  void RequestAuthorization(
      const BluetoothAgentServiceProvider::Delegate::ConfirmationCallback&
          callback);

  
  
  void ConfirmPairing();

  
  
  bool RejectPairing();

  
  
  bool CancelPairing();

  
  device::BluetoothDevice::PairingDelegate* GetPairingDelegate() const;

 private:
  
  
  void ResetCallbacks();

  
  
  bool RunPairingCallbacks(
      BluetoothAgentServiceProvider::Delegate::Status status);

  
  BluetoothDeviceChromeOS* device_;

  
  
  device::BluetoothDevice::PairingDelegate* pairing_delegate_;

  
  
  
  bool pairing_delegate_used_;

  
  
  
  
  BluetoothAgentServiceProvider::Delegate::PinCodeCallback pincode_callback_;
  BluetoothAgentServiceProvider::Delegate::PasskeyCallback passkey_callback_;
  BluetoothAgentServiceProvider::Delegate::ConfirmationCallback
      confirmation_callback_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothPairingChromeOS);
};

}  

#endif  
