// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MIDI_USB_MIDI_DEVICE_H_
#define MEDIA_MIDI_USB_MIDI_DEVICE_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"
#include "media/base/media_export.h"

namespace media {

class UsbMidiDevice;

class MEDIA_EXPORT UsbMidiDeviceDelegate {
 public:
  virtual ~UsbMidiDeviceDelegate() {}

  
  virtual void ReceiveUsbMidiData(UsbMidiDevice* device,
                                  int endpoint_number,
                                  const uint8* data,
                                  size_t size,
                                  base::TimeTicks time) = 0;
};

class MEDIA_EXPORT UsbMidiDevice {
 public:
  typedef ScopedVector<UsbMidiDevice> Devices;

  
  
  
  class Factory {
   public:
    typedef base::Callback<void(bool result, Devices* devices)> Callback;
    virtual ~Factory() {}
    
    
    
    
    
    
    
    
    virtual void EnumerateDevices(UsbMidiDeviceDelegate* delegate,
                                  Callback callback) = 0;
  };

  virtual ~UsbMidiDevice() {}

  
  virtual std::vector<uint8> GetDescriptor() = 0;

  
  virtual void Send(int endpoint_number, const std::vector<uint8>& data) = 0;
};

}  

#endif  
