// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_COCOA_APPKIT_UTILS_H
#define UI_BASE_COCOA_APPKIT_UTILS_H

#import <Cocoa/Cocoa.h>

#include "ui/base/ui_base_export.h"

namespace ui {

struct NinePartImageIds {
  int top_left;
  int top;
  int top_right;
  int left;
  int center;
  int right;
  int bottom_left;
  int bottom;
  int bottom_right;
};

#define IMAGE_GRID(x) { x ## _TOP_LEFT,    x ## _TOP,    x ## _TOP_RIGHT, \
                        x ## _LEFT,        x ## _CENTER, x ## _RIGHT, \
                        x ## _BOTTOM_LEFT, x ## _BOTTOM, x ## _BOTTOM_RIGHT, }

UI_BASE_EXPORT void DrawNinePartImage(NSRect frame,
                                      const NinePartImageIds& image_ids,
                                      NSCompositingOperation operation,
                                      CGFloat alpha,
                                      BOOL flipped);

}  

#endif  
