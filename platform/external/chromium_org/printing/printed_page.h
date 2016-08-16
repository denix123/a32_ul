// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PRINTING_PRINTED_PAGE_H_
#define PRINTING_PRINTED_PAGE_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "printing/metafile.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"

namespace printing {

class PRINTING_EXPORT PrintedPage
    : public base::RefCountedThreadSafe<PrintedPage> {
 public:
  PrintedPage(int page_number,
              scoped_ptr<MetafilePlayer> metafile,
              const gfx::Size& page_size,
              const gfx::Rect& page_content_rect);

  
  int page_number() const { return page_number_; }
  const MetafilePlayer* metafile() const;
  const gfx::Size& page_size() const { return page_size_; }
  const gfx::Rect& page_content_rect() const { return page_content_rect_; }
#if defined(OS_WIN)
  void set_shrink_factor(double shrink_factor) {
    shrink_factor_ = shrink_factor;
  }
  double shrink_factor() const { return shrink_factor_; }
#endif  

  
  
  void GetCenteredPageContentRect(const gfx::Size& paper_size,
                                  gfx::Rect* content_rect) const;

 private:
  friend class base::RefCountedThreadSafe<PrintedPage>;

  ~PrintedPage();

  
  const int page_number_;

  
  const scoped_ptr<MetafilePlayer> metafile_;

#if defined(OS_WIN)
  
  double shrink_factor_;
#endif  

  
  
  const gfx::Size page_size_;

  
  const gfx::Rect page_content_rect_;

  DISALLOW_COPY_AND_ASSIGN(PrintedPage);
};

}  

#endif  
