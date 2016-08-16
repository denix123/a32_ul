// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_BASE_SELECT_FAVICON_FRAMES_H_
#define COMPONENTS_FAVICON_BASE_SELECT_FAVICON_FRAMES_H_

#include <vector>

#include "base/basictypes.h"

class SkBitmap;

namespace gfx {
class ImageSkia;
class Size;
}

extern const float kSelectFaviconFramesInvalidScore;

gfx::ImageSkia CreateFaviconImageSkia(
    const std::vector<SkBitmap>& bitmaps,
    const std::vector<gfx::Size>& original_sizes,
    int desired_size_in_dip,
    float* score);

void SelectFaviconFrameIndices(const std::vector<gfx::Size>& frame_pixel_sizes,
                               const std::vector<int>& desired_sizes,
                               std::vector<size_t>* best_indices,
                               float* score);

#endif  
