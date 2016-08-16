// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MIDI_USB_MIDI_INPUT_STREAM_H_
#define MEDIA_MIDI_USB_MIDI_INPUT_STREAM_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/midi/usb_midi_jack.h"

namespace media {

class UsbMidiDevice;

class MEDIA_EXPORT UsbMidiInputStream {
 public:
  class MEDIA_EXPORT Delegate {
   public:
    virtual ~Delegate() {}
    
    
    virtual void OnReceivedData(size_t jack_index,
                                const uint8* data,
                                size_t size,
                                base::TimeTicks time) = 0;
  };

  
  struct JackUniqueKey {
    JackUniqueKey(UsbMidiDevice* device, int endpoint_number, int cable_number);
    bool operator==(const JackUniqueKey& that) const;
    bool operator<(const JackUniqueKey& that) const;

    UsbMidiDevice* device;
    int endpoint_number;
    int cable_number;
  };

  UsbMidiInputStream(const std::vector<UsbMidiJack>& jacks,
                     Delegate* delegate);
  ~UsbMidiInputStream();

  
  
  
  
  void OnReceivedData(UsbMidiDevice* device,
                      int endpoint_number,
                      const uint8* data,
                      size_t size,
                      base::TimeTicks time);

  std::vector<JackUniqueKey> RegisteredJackKeysForTesting() const;

 private:
  static const size_t kPacketSize = 4;
  
  
  void ProcessOnePacket(UsbMidiDevice* device,
                        int endpoint_number,
                        const uint8* packet,
                        base::TimeTicks time);

  
  std::map<JackUniqueKey, size_t> jack_dictionary_;

  
  Delegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(UsbMidiInputStream);
};

}  

#endif  
