// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_CHANNEL_MAC_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_CHANNEL_MAC_H_

#import <IOKit/IOReturn.h>

#include <string>

#include "base/macros.h"

@class IOBluetoothDevice;

namespace device {

class BluetoothSocketMac;

class BluetoothChannelMac {
 public:
  BluetoothChannelMac();
  virtual ~BluetoothChannelMac();

  
  
  
  virtual void SetSocket(BluetoothSocketMac* socket);

  
  
  std::string GetDeviceAddress();

  
  virtual IOBluetoothDevice* GetDevice() = 0;

  
  virtual uint16_t GetOutgoingMTU() = 0;

  
  
  
  
  
  
  
  
  
  virtual IOReturn WriteAsync(void* data, uint16_t length, void* refcon) = 0;

 protected:
  BluetoothSocketMac* socket() { return socket_; }

 private:
  
  BluetoothSocketMac* socket_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothChannelMac);
};

}  

#endif  
