// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_PDFIUM_PDFIUM_PAGE_H_
#define PDF_PDFIUM_PDFIUM_PAGE_H_

#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "ppapi/cpp/rect.h"
#include "third_party/pdfium/fpdfsdk/include/fpdfdoc.h"
#include "third_party/pdfium/fpdfsdk/include/fpdfformfill.h"
#include "third_party/pdfium/fpdfsdk/include/fpdftext.h"

namespace base {
class Value;
}

namespace chrome_pdf {

class PDFiumEngine;

class PDFiumPage {
 public:
  PDFiumPage(PDFiumEngine* engine,
             int i,
             const pp::Rect& r,
             bool available);
  ~PDFiumPage();
  
  void Unload();
  
  FPDF_PAGE GetPage();
  
  FPDF_PAGE GetPrintPage();
  
  void ClosePrintPage();

  
  FPDF_TEXTPAGE GetTextPage();

  
  base::Value* GetAccessibleContentAsValue(int rotation);

  enum Area {
    NONSELECTABLE_AREA,
    TEXT_AREA,
    WEBLINK_AREA,  
    DOCLINK_AREA,  
  };

  struct LinkTarget {
    
    
    std::string url;  
    int page;         
  };

  
  
  
  
  Area GetCharIndex(const pp::Point& point, int rotation, int* char_index,
                    LinkTarget* target);

  
  base::char16 GetCharAtIndex(int index);

  
  int GetCharCount();

  
  pp::Rect PageToScreen(const pp::Point& offset,
                        double zoom,
                        double left,
                        double top,
                        double right,
                        double bottom,
                        int rotation);

  int index() const { return index_; }
  pp::Rect rect() const { return rect_; }
  void set_rect(const pp::Rect& r) { rect_ = r; }
  bool available() const { return available_; }
  void set_available(bool available) { available_ = available; }
  void set_calculated_links(bool calculated_links) {
     calculated_links_ = calculated_links;
  }

 private:
  
  
  int GetLink(int char_index, LinkTarget* target);
  
  
  std::vector<int> GetLinks(pp::Rect text_area,
                            std::vector<LinkTarget>* targets);
  
  void CalculateLinks();
  
  
  Area GetLinkTarget(FPDF_LINK link, LinkTarget* target);
  
  Area GetDestinationTarget(FPDF_DEST destination, LinkTarget* target);
  
  base::Value* GetTextBoxAsValue(double page_height, double left, double top,
                                 double right, double bottom, int rotation);
  
  base::Value* CreateTextNode(std::string text);
  base::Value* CreateURLNode(std::string text, std::string url);

  struct Link {
    Link();
    ~Link();

    std::string url;
    
    std::vector<pp::Rect> rects;
  };

  PDFiumEngine* engine_;
  FPDF_PAGE page_;
  FPDF_TEXTPAGE text_page_;
  int index_;
  pp::Rect rect_;
  bool calculated_links_;
  std::vector<Link> links_;
  bool available_;
};

}  

#endif  
