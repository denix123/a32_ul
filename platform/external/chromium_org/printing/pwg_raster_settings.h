// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PRINTING_BITMAP_TRANSFORM_SETTINGS_H_
#define PRINTING_BITMAP_TRANSFORM_SETTINGS_H_

#include "base/tuple.h"
#include "ipc/ipc_param_traits.h"
#include "printing/printing_export.h"
#include "ui/gfx/rect.h"

namespace printing {

enum PwgRasterTransformType {
  TRANSFORM_NORMAL,
  TRANSFORM_ROTATE_180,
  TRANSFORM_FLIP_HORIZONTAL,
  TRANSFORM_FLIP_VERTICAL
};

struct PwgRasterSettings {
  
  PwgRasterTransformType odd_page_transform;
  
  bool rotate_all_pages;
  
  bool reverse_page_order;
};

}  

#endif  
