// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_CURSOR_FACTORY_OZONE_H_
#define UI_OZONE_PUBLIC_CURSOR_FACTORY_OZONE_H_

#include <vector>

#include "ui/gfx/native_widget_types.h"
#include "ui/ozone/ozone_base_export.h"

namespace gfx {
class Point;
}

namespace ui {

typedef void* PlatformCursor;

class OZONE_BASE_EXPORT CursorFactoryOzone {
 public:
  CursorFactoryOzone();
  virtual ~CursorFactoryOzone();

  
  static CursorFactoryOzone* GetInstance();

  
  
  
  virtual PlatformCursor GetDefaultCursor(int type);

  
  
  
  virtual PlatformCursor CreateImageCursor(const SkBitmap& bitmap,
                                           const gfx::Point& hotspot);

  
  
  
  
  virtual PlatformCursor CreateAnimatedCursor(
      const std::vector<SkBitmap>& bitmaps,
      const gfx::Point& hotspot,
      int frame_delay_ms);

  
  virtual void RefImageCursor(PlatformCursor cursor);

  
  virtual void UnrefImageCursor(PlatformCursor cursor);

 private:
  static CursorFactoryOzone* impl_;  
};

}  

#endif  
