// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_OVERLAY_TRANSFORM_H_
#define UI_GFX_OVERLAY_TRANSFORM_H_

namespace gfx {

enum OverlayTransform {
  OVERLAY_TRANSFORM_INVALID,
  OVERLAY_TRANSFORM_NONE,
  OVERLAY_TRANSFORM_FLIP_HORIZONTAL,
  OVERLAY_TRANSFORM_FLIP_VERTICAL,
  OVERLAY_TRANSFORM_ROTATE_90,
  OVERLAY_TRANSFORM_ROTATE_180,
  OVERLAY_TRANSFORM_ROTATE_270,
};

}  

#endif  
