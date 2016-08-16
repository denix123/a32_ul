// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_FONT_RENDER_PARAMS_H_
#define UI_GFX_FONT_RENDER_PARAMS_H_

#include <string>
#include <vector>

#include "ui/gfx/gfx_export.h"

namespace gfx {

struct GFX_EXPORT FontRenderParams {
  FontRenderParams();
  ~FontRenderParams();

  
  enum Hinting {
    HINTING_NONE = 0,
    HINTING_SLIGHT,
    HINTING_MEDIUM,
    HINTING_FULL,
  };

  
  enum SubpixelRendering {
    SUBPIXEL_RENDERING_NONE = 0,
    SUBPIXEL_RENDERING_RGB,
    SUBPIXEL_RENDERING_BGR,
    SUBPIXEL_RENDERING_VRGB,
    SUBPIXEL_RENDERING_VBGR,
  };

  
  
  bool antialiasing;

  
  
  
  
  bool subpixel_positioning;

  
  
  bool autohinter;

  
  bool use_bitmaps;

  
  Hinting hinting;

  
  
  SubpixelRendering subpixel_rendering;
};

struct GFX_EXPORT FontRenderParamsQuery {
  explicit FontRenderParamsQuery(bool for_web_contents);
  ~FontRenderParamsQuery();

  bool is_empty() const {
    return families.empty() && pixel_size <= 0 && point_size <= 0 && style < 0;
  }

  
  
  
  bool for_web_contents;

  
  std::vector<std::string> families;

  
  int pixel_size;
  int point_size;

  
  int style;
};

GFX_EXPORT FontRenderParams GetFontRenderParams(
    const FontRenderParamsQuery& query,
    std::string* family_out);

GFX_EXPORT void ClearFontRenderParamsCacheForTest();

#if defined(OS_CHROMEOS)
GFX_EXPORT void SetFontRenderParamsDeviceScaleFactor(
    float device_scale_factor);
#endif

}  

#endif  
