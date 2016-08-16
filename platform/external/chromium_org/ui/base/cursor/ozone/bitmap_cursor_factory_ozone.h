// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_CURSOR_OZONE_BITMAP_CURSOR_FACTORY_OZONE_H_
#define UI_BASE_CURSOR_OZONE_BITMAP_CURSOR_FACTORY_OZONE_H_

#include <map>

#include "base/memory/ref_counted.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/base/cursor/cursor.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/geometry/point.h"
#include "ui/ozone/public/cursor_factory_ozone.h"

namespace ui {

class UI_BASE_EXPORT BitmapCursorOzone
    : public base::RefCounted<BitmapCursorOzone> {
 public:
  BitmapCursorOzone(const SkBitmap& bitmap, const gfx::Point& hotspot);
  BitmapCursorOzone(const std::vector<SkBitmap>& bitmaps,
                    const gfx::Point& hotspot,
                    int frame_delay_ms);

  const gfx::Point& hotspot();
  const SkBitmap& bitmap();

  
  const std::vector<SkBitmap>& bitmaps();
  int frame_delay_ms();

 private:
  friend class base::RefCounted<BitmapCursorOzone>;
  ~BitmapCursorOzone();

  std::vector<SkBitmap> bitmaps_;
  gfx::Point hotspot_;
  int frame_delay_ms_;

  DISALLOW_COPY_AND_ASSIGN(BitmapCursorOzone);
};

class UI_BASE_EXPORT BitmapCursorFactoryOzone : public CursorFactoryOzone {
 public:
  BitmapCursorFactoryOzone();
  virtual ~BitmapCursorFactoryOzone();

  
  static scoped_refptr<BitmapCursorOzone> GetBitmapCursor(
      PlatformCursor platform_cursor);

  
  virtual PlatformCursor GetDefaultCursor(int type) OVERRIDE;
  virtual PlatformCursor CreateImageCursor(const SkBitmap& bitmap,
                                           const gfx::Point& hotspot) OVERRIDE;
  virtual PlatformCursor CreateAnimatedCursor(
      const std::vector<SkBitmap>& bitmaps,
      const gfx::Point& hotspot,
      int frame_delay_ms) OVERRIDE;
  virtual void RefImageCursor(PlatformCursor cursor) OVERRIDE;
  virtual void UnrefImageCursor(PlatformCursor cursor) OVERRIDE;

 private:
  
  scoped_refptr<BitmapCursorOzone> GetDefaultCursorInternal(int type);

  
  typedef std::map<int, scoped_refptr<BitmapCursorOzone> > DefaultCursorMap;
  DefaultCursorMap default_cursors_;

  DISALLOW_COPY_AND_ASSIGN(BitmapCursorFactoryOzone);
};

}  

#endif  
