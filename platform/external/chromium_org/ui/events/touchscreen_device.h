// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_TOUCHSCREEN_DEVICE_H_
#define UI_EVENTS_TOUCHSCREEN_DEVICE_H_

#include "ui/events/events_base_export.h"
#include "ui/gfx/geometry/size.h"

namespace ui {

struct EVENTS_BASE_EXPORT TouchscreenDevice {
  static const int kInvalidId;

  TouchscreenDevice(int id, const gfx::Size& size, bool is_internal);

  
  int id;

  
  gfx::Size size;

  
  bool is_internal;
};

}  

#endif  
