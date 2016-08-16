// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_FONT_LIST_H_
#define UI_GFX_FONT_LIST_H_

#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "ui/gfx/font.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class FontListImpl;

class GFX_EXPORT FontList {
 public:
  
  
  FontList();

  
  FontList(const FontList& other);

  
  
  explicit FontList(const std::string& font_description_string);

  
  FontList(const std::vector<std::string>& font_names,
           int font_style,
           int font_size);

  
  
  explicit FontList(const std::vector<Font>& fonts);

  
  explicit FontList(const Font& font);

  ~FontList();

  
  FontList& operator=(const FontList& other);

  
  
  
  
  
  
  
  
  static void SetDefaultFontDescription(const std::string& font_description);

  
  
  
  
  FontList Derive(int size_delta, int font_style) const;

  
  
  FontList DeriveWithSizeDelta(int size_delta) const;

  
  
  
  FontList DeriveWithStyle(int font_style) const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  gfx::FontList DeriveWithHeightUpperBound(int height) const;

  
  
  int GetHeight() const;

  
  
  int GetBaseline() const;

  
  
  int GetCapHeight() const;

  
  
  
  int GetExpectedTextWidth(int length) const;

  
  int GetFontStyle() const;

  
  
  
  const std::string& GetFontDescriptionString() const;

  
  int GetFontSize() const;

  
  const std::vector<Font>& GetFonts() const;

  
  const Font& GetPrimaryFont() const;

 private:
  explicit FontList(FontListImpl* impl);

  static const scoped_refptr<FontListImpl>& GetDefaultImpl();

  scoped_refptr<FontListImpl> impl_;
};

}  

#endif  
