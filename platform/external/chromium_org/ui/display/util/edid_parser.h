// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_UTIL_EDID_PARSER_H_
#define UI_DISPLAY_UTIL_EDID_PARSER_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "ui/display/util/display_util_export.h"


namespace ui {

DISPLAY_UTIL_EXPORT bool GetDisplayIdFromEDID(const std::vector<uint8_t>& edid,
                                              uint8_t index,
                                              int64_t* display_id_out);

DISPLAY_UTIL_EXPORT bool ParseOutputDeviceData(
    const std::vector<uint8_t>& edid,
    uint16_t* manufacturer_id,
    std::string* human_readable_name);

DISPLAY_UTIL_EXPORT bool ParseOutputOverscanFlag(
    const std::vector<uint8_t>& edid,
    bool* flag);

}  

#endif 
