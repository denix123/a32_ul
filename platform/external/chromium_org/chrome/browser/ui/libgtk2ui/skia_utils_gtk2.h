// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_SKIA_UTILS_GTK2_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_SKIA_UTILS_GTK2_H_

#include "third_party/skia/include/core/SkColor.h"

typedef struct _GdkColor GdkColor;
typedef struct _GdkPixbuf GdkPixbuf;

class SkBitmap;

#define GDK_COLOR_RGB(r, g, b) {0, r * ::libgtk2ui::kSkiaToGDKMultiplier,  \
        g * ::libgtk2ui::kSkiaToGDKMultiplier,                          \
        b * ::libgtk2ui::kSkiaToGDKMultiplier}

namespace libgtk2ui {

const int kSkiaToGDKMultiplier = 257;

SkColor GdkColorToSkColor(GdkColor color);

GdkColor SkColorToGdkColor(SkColor color);

const SkBitmap GdkPixbufToImageSkia(GdkPixbuf* pixbuf);

GdkPixbuf* GdkPixbufFromSkBitmap(const SkBitmap& bitmap);

}  

#endif  
