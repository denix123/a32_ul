// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PROXIMITY_AUTH_BLUETOOTH_UTIL_H
#define COMPONENTS_PROXIMITY_AUTH_BLUETOOTH_UTIL_H

#include <string>

#include "base/callback_forward.h"
#include "device/bluetooth/bluetooth_device.h"

namespace device {
class BluetoothUUID;
}

namespace proximity_auth {
namespace bluetooth_util {

typedef base::Callback<void(const std::string& error_message)> ErrorCallback;

void SeekDeviceByAddress(const std::string& device_address,
                         const base::Closure& callback,
                         const ErrorCallback& error_callback,
                         base::TaskRunner* task_runner);

void ConnectToServiceInsecurely(
    device::BluetoothDevice* device,
    const device::BluetoothUUID& uuid,
    const device::BluetoothDevice::ConnectToServiceCallback& callback,
    const device::BluetoothDevice::ConnectToServiceErrorCallback&
        error_callback);

}  
}  

#endif  
