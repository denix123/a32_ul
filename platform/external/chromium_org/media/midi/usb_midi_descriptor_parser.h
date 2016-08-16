// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MIDI_USB_MIDI_DESCRIPTOR_PARSER_H_
#define MEDIA_MIDI_USB_MIDI_DESCRIPTOR_PARSER_H_

#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"
#include "media/midi/usb_midi_jack.h"

namespace media {

class UsbMidiDevice;

class MEDIA_EXPORT UsbMidiDescriptorParser {
 public:
  UsbMidiDescriptorParser();
  ~UsbMidiDescriptorParser();

  
  
  
  bool Parse(UsbMidiDevice* device,
             const uint8* data,
             size_t size,
             std::vector<UsbMidiJack>* jacks);

 private:
  bool ParseInternal(UsbMidiDevice* device,
                     const uint8* data,
                     size_t size,
                     std::vector<UsbMidiJack>* jacks);
  bool ParseInterface(const uint8* data, size_t size);
  bool ParseCSInterface(UsbMidiDevice* device, const uint8* data, size_t size);
  bool ParseEndpoint(const uint8* data, size_t size);
  bool ParseCSEndpoint(const uint8* data,
                       size_t size,
                       std::vector<UsbMidiJack>* jacks);
  void Clear();

  bool is_parsing_usb_midi_interface_;
  uint8 current_endpoint_address_;
  uint8 current_cable_number_;

  std::vector<UsbMidiJack> incomplete_jacks_;

  DISALLOW_COPY_AND_ASSIGN(UsbMidiDescriptorParser);
};


}  

#endif  
