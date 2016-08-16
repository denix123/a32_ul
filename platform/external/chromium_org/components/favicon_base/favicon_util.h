// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_BASE_FAVICON_UTIL_H_
#define COMPONENTS_FAVICON_BASE_FAVICON_UTIL_H_

#include <vector>

#include "components/favicon_base/favicon_types.h"

namespace gfx {
class Image;
}

namespace favicon_base {

std::vector<float> GetFaviconScales();

void SetFaviconColorSpace(gfx::Image* image);

gfx::Image SelectFaviconFramesFromPNGs(
    const std::vector<favicon_base::FaviconRawBitmapResult>& png_data,
    const std::vector<float>& favicon_scales,
    int favicon_size);

}  

#endif  
