// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_FONT_FALLBACK_H_
#define UI_GFX_FONT_FALLBACK_H_

#include <string>
#include <vector>

namespace gfx {

std::vector<std::string> GetFallbackFontFamilies(
    const std::string& font_family);

}  

#endif  
