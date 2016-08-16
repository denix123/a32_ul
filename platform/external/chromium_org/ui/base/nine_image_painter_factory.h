// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_NINE_IMAGE_PAINTER_FACTORY_H_
#define UI_BASE_NINE_IMAGE_PAINTER_FACTORY_H_

#include "base/memory/scoped_ptr.h"
#include "ui/base/ui_base_export.h"

#define IMAGE_GRID(x) { x ## _TOP_LEFT,    x ## _TOP,    x ## _TOP_RIGHT, \
                        x ## _LEFT,        x ## _CENTER, x ## _RIGHT, \
                        x ## _BOTTOM_LEFT, x ## _BOTTOM, x ## _BOTTOM_RIGHT, }

#define EMPTY_IMAGE 0

#define IMAGE_GRID_NO_CENTER(x) { x ## _TOP_LEFT, x ## _TOP, x ## _TOP_RIGHT, \
      x ## _LEFT, EMPTY_IMAGE, x ## _RIGHT, \
      x ## _BOTTOM_LEFT, x ## _BOTTOM, x ## _BOTTOM_RIGHT, }


namespace gfx {
class NineImagePainter;
}

namespace ui {

UI_BASE_EXPORT scoped_ptr<gfx::NineImagePainter> CreateNineImagePainter(
    const int image_ids[]);

}  

#endif  
