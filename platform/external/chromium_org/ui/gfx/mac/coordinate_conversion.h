// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_MAC_COORDINATE_CONVERSION_H_
#define UI_GFX_MAC_COORDINATE_CONVERSION_H_

#import <Foundation/Foundation.h>

#include "ui/gfx/gfx_export.h"

namespace gfx {

class Rect;

GFX_EXPORT NSRect ScreenRectToNSRect(const gfx::Rect& rect);

GFX_EXPORT gfx::Rect ScreenRectFromNSRect(const NSRect& point);

}  

#endif  
