// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_FONT_LIST_IMPL_H_
#define UI_GFX_FONT_LIST_IMPL_H_

#include <string>
#include <vector>

#include "base/memory/ref_counted.h"

namespace gfx {

class Font;

class FontListImpl : public base::RefCounted<FontListImpl> {
 public:
  
  
  explicit FontListImpl(const std::string& font_description_string);

  
  FontListImpl(const std::vector<std::string>& font_names,
               int font_style,
               int font_size);

  
  
  explicit FontListImpl(const std::vector<Font>& fonts);

  
  explicit FontListImpl(const Font& font);

  
  
  
  
  FontListImpl* Derive(int size_delta, int font_style) const;

  
  
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
  friend class base::RefCounted<FontListImpl>;

  ~FontListImpl();

  
  
  void CacheCommonFontHeightAndBaseline() const;

  
  void CacheFontStyleAndSize() const;

  
  
  
  mutable std::vector<Font> fonts_;

  
  
  
  
  
  
  mutable std::string font_description_string_;

  
  mutable int common_height_;
  mutable int common_baseline_;

  
  mutable int font_style_;
  mutable int font_size_;
};

}  

#endif  
