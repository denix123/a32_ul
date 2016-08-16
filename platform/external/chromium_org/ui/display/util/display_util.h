// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_UTIL_DISPLAY_UTIL_H_
#define UI_DISPLAY_UTIL_DISPLAY_UTIL_H_

#include "ui/display/util/display_util_export.h"
#include "ui/gfx/geometry/size.h"

namespace ui {

DISPLAY_UTIL_EXPORT bool IsDisplaySizeBlackListed(
    const gfx::Size& physical_size);

DISPLAY_UTIL_EXPORT float GetScaleFactor(
    const gfx::Size& physical_size_in_mm,
    const gfx::Size& screen_size_in_pixels);

}  

#endif  
