// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_AX_TEXT_UTILS_H_
#define UI_ACCESSIBILITY_AX_TEXT_UTILS_H_

#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "ui/accessibility/ax_export.h"

namespace ui {

enum TextBoundaryType {
  CHAR_BOUNDARY,
  WORD_BOUNDARY,
  LINE_BOUNDARY,
  SENTENCE_BOUNDARY,
  PARAGRAPH_BOUNDARY,
  ALL_BOUNDARY
};

enum TextBoundaryDirection {
  
  FORWARDS_DIRECTION,
  
  BACKWARDS_DIRECTION
};

size_t AX_EXPORT
    FindAccessibleTextBoundary(const base::string16& text,
                               const std::vector<int>& line_breaks,
                               TextBoundaryType boundary,
                               size_t start_offset,
                               TextBoundaryDirection direction);

}  

#endif  
