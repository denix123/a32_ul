// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_DISCOVERY_MANAGER_MAC_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_DISCOVERY_MANAGER_MAC_H_

#include "base/macros.h"

@class IOBluetoothDevice;

namespace device {

class BluetoothDiscoveryManagerMac {
 public:
  
  class Observer {
   public:
    
    
    virtual void DeviceFound(IOBluetoothDevice* device) = 0;

    
    
    
    
    virtual void DiscoveryStopped(bool unexpected) = 0;
  };

  virtual ~BluetoothDiscoveryManagerMac();

  
  virtual bool IsDiscovering() const = 0;

  
  
  virtual bool StartDiscovery() = 0;

  
  
  virtual bool StopDiscovery() = 0;

  
  
  
  
  static BluetoothDiscoveryManagerMac* CreateClassic(Observer* observer);

 protected:
  explicit BluetoothDiscoveryManagerMac(Observer* observer);

  
  Observer* observer_;

 private:
  DISALLOW_COPY_AND_ASSIGN(BluetoothDiscoveryManagerMac);
};

}  

#endif  
