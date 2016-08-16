// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_TEXT_ELIDER_H_
#define UI_GFX_TEXT_ELIDER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "ui/gfx/gfx_export.h"
#include "ui/gfx/text_constants.h"

class GURL;

namespace base {
class FilePath;
}

namespace gfx {
class FontList;

GFX_EXPORT extern const char kEllipsis[];
GFX_EXPORT extern const base::char16 kEllipsisUTF16[];
GFX_EXPORT extern const base::char16 kForwardSlash;

class StringSlicer {
 public:
  StringSlicer(const base::string16& text,
               const base::string16& ellipsis,
               bool elide_in_middle,
               bool elide_at_beginning);

  
  
  
  
  
  base::string16 CutString(size_t length, bool insert_ellipsis);

 private:
  
  size_t FindValidBoundaryBefore(size_t index) const;
  size_t FindValidBoundaryAfter(size_t index) const;

  
  const base::string16& text_;

  
  const base::string16& ellipsis_;

  
  bool elide_in_middle_;

  
  bool elide_at_beginning_;

  DISALLOW_COPY_AND_ASSIGN(StringSlicer);
};

GFX_EXPORT base::string16 ElideText(const base::string16& text,
                                    const gfx::FontList& font_list,
                                    float available_pixel_width,
                                    ElideBehavior elide_behavior);

GFX_EXPORT base::string16 ElideFilename(const base::FilePath& filename,
                                        const gfx::FontList& font_list,
                                        float available_pixel_width);


GFX_EXPORT bool ElideString(const base::string16& input, int max_len,
                            base::string16* output);

GFX_EXPORT bool ElideRectangleString(const base::string16& input,
                                     size_t max_rows,
                                     size_t max_cols,
                                     bool strict,
                                     base::string16* output);

enum WordWrapBehavior {
  
  
  IGNORE_LONG_WORDS,

  
  
  TRUNCATE_LONG_WORDS,

  
  
  ELIDE_LONG_WORDS,

  
  
  WRAP_LONG_WORDS,
};

enum ReformattingResultFlags {
  INSUFFICIENT_SPACE_HORIZONTAL = 1 << 0,
  INSUFFICIENT_SPACE_VERTICAL = 1 << 1,
};

GFX_EXPORT int ElideRectangleText(const base::string16& text,
                                  const gfx::FontList& font_list,
                                  float available_pixel_width,
                                  int available_pixel_height,
                                  WordWrapBehavior wrap_behavior,
                                  std::vector<base::string16>* lines);

GFX_EXPORT base::string16 TruncateString(const base::string16& string,
                                         size_t length,
                                         BreakType break_type);

}  

#endif  
