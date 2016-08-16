// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_IMAGE_UTIL_H_
#define EXTENSIONS_BROWSER_IMAGE_UTIL_H_

#include <string>

typedef unsigned int SkColor;

namespace extensions {
namespace image_util {

bool ParseCSSColorString(const std::string& color_string, SkColor* result);

}  
}  

#endif  
