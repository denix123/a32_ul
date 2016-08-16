// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_SERVICE_RECORD_WIN_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_SERVICE_RECORD_WIN_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "device/bluetooth/bluetooth_init_win.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace device {

class BluetoothServiceRecordWin {
 public:
  BluetoothServiceRecordWin(const std::string& device_address,
                            const std::string& name,
                            const std::vector<uint8>& sdp_bytes,
                            const BluetoothUUID& gatt_uuid);

  bool IsEqual(const BluetoothServiceRecordWin& other);

  
  BTH_ADDR device_bth_addr() const { return device_bth_addr_; }

  
  const std::string& device_address() const { return device_address_; }

  
  const std::string& name() const { return name_; }

  
  
  const BluetoothUUID& uuid() const { return uuid_; }

  
  bool SupportsRfcomm() const { return supports_rfcomm_; }

  
  
  uint8 rfcomm_channel() const { return rfcomm_channel_; }

 private:
  BTH_ADDR device_bth_addr_;
  std::string device_address_;
  std::string name_;
  BluetoothUUID uuid_;

  bool supports_rfcomm_;
  uint8 rfcomm_channel_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothServiceRecordWin);
};

}  

#endif  
