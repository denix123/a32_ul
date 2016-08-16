// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_CURSOR_CURSOR_UTIL_H_
#define UI_BASE_CURSOR_CURSOR_UTIL_H_

#include <vector>

#include "base/compiler_specific.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/display.h"
#include "ui/gfx/geometry/point.h"

namespace ui {

UI_BASE_EXPORT void ScaleAndRotateCursorBitmapAndHotpoint(
    float scale,
    gfx::Display::Rotation rotation,
    SkBitmap* bitmap_in_out,
    gfx::Point* hotpoint_in_out);

void GetImageCursorBitmap(int resource_id,
                          float scale,
                          gfx::Display::Rotation rotation,
                          gfx::Point* hotspot,
                          SkBitmap* bitmap);
void GetAnimatedCursorBitmaps(int resource_id,
                              float scale,
                              gfx::Display::Rotation rotation,
                              gfx::Point* hotspot,
                              std::vector<SkBitmap>* bitmaps);

}  

#endif  
