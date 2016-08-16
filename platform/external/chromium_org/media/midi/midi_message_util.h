// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MIDI_MIDI_MESSAGE_UTIL_H_
#define MEDIA_MIDI_MIDI_MESSAGE_UTIL_H_

#include <deque>
#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"

namespace media {

MEDIA_EXPORT size_t GetMidiMessageLength(uint8 status_byte);

const uint8 kSysExByte = 0xf0;
const uint8 kEndOfSysExByte = 0xf7;

const uint8 kSysMessageBitMask = 0xf0;
const uint8 kSysMessageBitPattern = 0xf0;
const uint8 kSysRTMessageBitMask = 0xf8;
const uint8 kSysRTMessageBitPattern = 0xf8;

}  

#endif  
