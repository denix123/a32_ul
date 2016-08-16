// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_X_KEYSYM_TO_UNICODE_H_
#define UI_EVENTS_X_KEYSYM_TO_UNICODE_H_

#include <cstdint>

namespace ui {

uint16_t GetUnicodeCharacterFromXKeySym(unsigned long keysym);

}  

#endif  
