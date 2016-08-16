// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MIDI_USB_MIDI_JACK_H_
#define MEDIA_MIDI_USB_MIDI_JACK_H_

#include "base/basictypes.h"
#include "media/base/media_export.h"

namespace media {

class UsbMidiDevice;

struct MEDIA_EXPORT UsbMidiJack {
  
  
  
  enum Direction {
    DIRECTION_IN,
    DIRECTION_OUT,
  };
  UsbMidiJack(UsbMidiDevice* device,
              uint8 jack_id,
              uint8 cable_number,
              uint8 endpoint_address)
      : device(device),
        jack_id(jack_id),
        cable_number(cable_number),
        endpoint_address(endpoint_address) {}
  
  UsbMidiDevice* device;
  
  uint8 jack_id;
  
  uint8 cable_number;
  
  uint8 endpoint_address;

  Direction direction() const {
    return (endpoint_address & 0x80) ? DIRECTION_IN : DIRECTION_OUT;
  }
  uint8 endpoint_number() const {
    return (endpoint_address & 0xf);
  }
};

}  

#endif  
