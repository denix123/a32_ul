// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_RFCOMM_CHANNEL_MAC_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_RFCOMM_CHANNEL_MAC_H_

#import <IOBluetooth/IOBluetooth.h>
#import <IOKit/IOReturn.h>

#include "base/mac/scoped_nsobject.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "device/bluetooth/bluetooth_channel_mac.h"

@class BluetoothRfcommChannelDelegate;

namespace device {

class BluetoothRfcommChannelMac : public BluetoothChannelMac {
 public:
  
  
  
  BluetoothRfcommChannelMac(BluetoothSocketMac* socket,
                            IOBluetoothRFCOMMChannel* channel);
  virtual ~BluetoothRfcommChannelMac();

  
  
  
  
  static scoped_ptr<BluetoothRfcommChannelMac> OpenAsync(
      BluetoothSocketMac* socket,
      IOBluetoothDevice* device,
      BluetoothRFCOMMChannelID channel_id,
      IOReturn* status);

  
  virtual void SetSocket(BluetoothSocketMac* socket) OVERRIDE;
  virtual IOBluetoothDevice* GetDevice() OVERRIDE;
  virtual uint16_t GetOutgoingMTU() OVERRIDE;
  virtual IOReturn WriteAsync(void* data,
                              uint16_t length,
                              void* refcon) OVERRIDE;

  void OnChannelOpenComplete(IOBluetoothRFCOMMChannel* channel,
                             IOReturn status);
  void OnChannelClosed(IOBluetoothRFCOMMChannel* channel);
  void OnChannelDataReceived(IOBluetoothRFCOMMChannel* channel,
                             void* data,
                             size_t length);
  void OnChannelWriteComplete(IOBluetoothRFCOMMChannel* channel,
                              void* refcon,
                              IOReturn status);

 private:
  
  base::scoped_nsobject<IOBluetoothRFCOMMChannel> channel_;

  
  base::scoped_nsobject<BluetoothRfcommChannelDelegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothRfcommChannelMac);
};

}  

#endif  
