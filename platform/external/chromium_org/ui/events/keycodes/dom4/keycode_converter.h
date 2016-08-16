// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_KEYCODES_DOM4_KEYCODE_CONVERTER_H_
#define UI_EVENTS_KEYCODES_DOM4_KEYCODE_CONVERTER_H_

#include <stdint.h>
#include "base/basictypes.h"


namespace ui {

typedef struct {
  
  
  
  uint32_t usb_keycode;

  
  
  
  
  uint16_t native_keycode;

  
  
  const char* code;
} KeycodeMapEntry;

class KeycodeConverter {
 public:
  
  static uint16_t InvalidNativeKeycode();

  
  
  static const char* InvalidKeyboardEventCode();

  
  
  static const char* NativeKeycodeToCode(uint16_t native_keycode);

  
  static uint16_t CodeToNativeKeycode(const char* code);

  
  
  

  
  static uint16_t InvalidUsbKeycode();

  
  static uint16_t UsbKeycodeToNativeKeycode(uint32_t usb_keycode);

  
  static uint32_t NativeKeycodeToUsbKeycode(uint16_t native_keycode);

  
  
  static const char* UsbKeycodeToCode(uint32_t usb_keycode);

  
  static uint32_t CodeToUsbKeycode(const char* code);

  
  static size_t NumKeycodeMapEntriesForTest();
  static const KeycodeMapEntry* GetKeycodeMapForTest();

 private:
  DISALLOW_COPY_AND_ASSIGN(KeycodeConverter);
};

}  

#endif  
