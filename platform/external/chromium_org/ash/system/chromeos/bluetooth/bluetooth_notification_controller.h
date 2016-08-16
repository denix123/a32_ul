// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_BLUETOOTH_BLUETOOTH_NOTIFICATION_CONTROLLER_H_
#define ASH_SYSTEM_CHROMEOS_BLUETOOTH_BLUETOOTH_NOTIFICATION_CONTROLLER_H_

#include <set>

#include "ash/ash_export.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_device.h"

namespace ash {

class ASH_EXPORT BluetoothNotificationController
    : public device::BluetoothAdapter::Observer,
      public device::BluetoothDevice::PairingDelegate {
 public:
  BluetoothNotificationController();
  virtual ~BluetoothNotificationController();

  
  virtual void AdapterDiscoverableChanged(device::BluetoothAdapter* adapter,
                                          bool discoverable) OVERRIDE;
  virtual void DeviceAdded(device::BluetoothAdapter* adapter,
                           device::BluetoothDevice* device) OVERRIDE;
  virtual void DeviceChanged(device::BluetoothAdapter* adapter,
                             device::BluetoothDevice* device) OVERRIDE;
  virtual void DeviceRemoved(device::BluetoothAdapter* adapter,
                             device::BluetoothDevice* device) OVERRIDE;

  
  virtual void RequestPinCode(device::BluetoothDevice* device) OVERRIDE;
  virtual void RequestPasskey(device::BluetoothDevice* device) OVERRIDE;
  virtual void DisplayPinCode(device::BluetoothDevice* device,
                              const std::string& pincode) OVERRIDE;
  virtual void DisplayPasskey(device::BluetoothDevice* device,
                              uint32 passkey) OVERRIDE;
  virtual void KeysEntered(device::BluetoothDevice* device,
                           uint32 entered) OVERRIDE;
  virtual void ConfirmPasskey(device::BluetoothDevice* device,
                              uint32 passkey) OVERRIDE;
  virtual void AuthorizePairing(device::BluetoothDevice* device) OVERRIDE;

 private:
  
  
  void OnGetAdapter(scoped_refptr<device::BluetoothAdapter> adapter);

  
  
  void NotifyAdapterDiscoverable();

  
  
  
  
  
  void NotifyPairing(device::BluetoothDevice* device,
                     const base::string16& message,
                     bool with_buttons);

  
  void NotifyPairedDevice(device::BluetoothDevice* device);

  
  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  
  
  std::set<std::string> paired_devices_;

  
  
  base::WeakPtrFactory<BluetoothNotificationController> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothNotificationController);
};

}  

#endif  
