// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_GEOMETRY_SIZE_CONVERSIONS_H_
#define UI_GFX_GEOMETRY_SIZE_CONVERSIONS_H_

#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/size_f.h"

namespace gfx {

GFX_EXPORT Size ToFlooredSize(const SizeF& size);

GFX_EXPORT Size ToCeiledSize(const SizeF& size);

GFX_EXPORT Size ToRoundedSize(const SizeF& size);

}  

#endif  
