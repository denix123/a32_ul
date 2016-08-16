// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_PDFIUM_PDFIUM_RANGE_H_
#define PDF_PDFIUM_PDFIUM_RANGE_H_

#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "pdf/pdfium/pdfium_page.h"
#include "ppapi/cpp/rect.h"

namespace chrome_pdf {

class PDFiumRange {
 public:
  PDFiumRange(PDFiumPage* page, int char_index, int char_count);
  ~PDFiumRange();

  
  
  void SetCharCount(int char_count);

  int page_index() const { return page_->index(); }
  int char_index() const { return char_index_; }
  int char_count() const { return char_count_; }

  
  std::vector<pp::Rect> GetScreenRects(const pp::Point& offset,
                                       double zoom,
                                       int rotation);

  
  base::string16 GetText();

 private:
  PDFiumPage* page_;
  
  int char_index_;
  
  int char_count_;

  
  std::vector<pp::Rect> cached_screen_rects_;
  pp::Point cached_screen_rects_offset_;
  double cached_screen_rects_zoom_;
};

}  

#endif  
