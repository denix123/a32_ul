// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_PANGO_UTIL_H_
#define UI_GFX_PANGO_UTIL_H_

#include <cairo/cairo.h>
#include <pango/pango.h>

#include "base/i18n/rtl.h"
#include "base/logging.h"
#include "base/strings/string16.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class FontList;

class ScopedPangoFontDescription {
 public:
  explicit ScopedPangoFontDescription(PangoFontDescription* description)
      : description_(description) {
    DCHECK(description);
  }

  explicit ScopedPangoFontDescription(const std::string& str)
      : description_(pango_font_description_from_string(str.c_str())) {
    DCHECK(description_);
  }

  ~ScopedPangoFontDescription() {
    pango_font_description_free(description_);
  }

  PangoFontDescription* get() { return description_; }

 private:
  PangoFontDescription* description_;

  DISALLOW_COPY_AND_ASSIGN(ScopedPangoFontDescription);
};


void SetUpPangoLayout(
    PangoLayout* layout,
    const base::string16& text,
    const FontList& font_list,
    base::i18n::TextDirection text_direction,
    int flags);

int GetPangoFontSizeInPixels(PangoFontDescription* pango_font);

PangoFontMetrics* GetPangoFontMetrics(PangoFontDescription* desc);

}  

#endif  
