// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WINDOW_WINDOW_SHAPE_H_
#define UI_VIEWS_WINDOW_WINDOW_SHAPE_H_

#include "ui/views/views_export.h"

namespace gfx {
class Size;
class Path;
}

namespace views {

VIEWS_EXPORT void GetDefaultWindowMask(const gfx::Size& size,
                                       gfx::Path* window_mask);

} 

#endif  