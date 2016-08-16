// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_UTIL_X11_EDID_PARSER_X11_H_
#define UI_DISPLAY_UTIL_X11_EDID_PARSER_X11_H_

#include <stdint.h>

#include <string>

#include "ui/display/types/display_constants.h"
#include "ui/display/util/display_util_export.h"

typedef unsigned long XID;
typedef XID RROutput;


namespace ui {

DISPLAY_UTIL_EXPORT bool GetDisplayId(XID output,
                                      uint8_t index,
                                      int64_t* display_id_out);

DISPLAY_UTIL_EXPORT std::string GetDisplayName(RROutput output);

DISPLAY_UTIL_EXPORT bool GetOutputOverscanFlag(RROutput output, bool* flag);

}  

#endif  
