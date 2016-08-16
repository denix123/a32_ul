// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_PDF_ENGINE_H_
#define PDF_PDF_ENGINE_H_

#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

#include <string>
#include <vector>

#include "base/strings/string16.h"

#include "ppapi/c/dev/pp_cursor_type_dev.h"
#include "ppapi/c/dev/ppp_printing_dev.h"
#include "ppapi/c/ppb_input_event.h"
#include "ppapi/cpp/completion_callback.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/rect.h"
#include "ppapi/cpp/size.h"
#include "ppapi/cpp/url_loader.h"

namespace pp {
class InputEvent;
}

const uint32 kBackgroundColor = 0xFFCCCCCC;

namespace chrome_pdf {

class Stream;

#if defined(OS_MACOSX)
const uint32 kDefaultKeyModifier = PP_INPUTEVENT_MODIFIER_METAKEY;
#else  
const uint32 kDefaultKeyModifier = PP_INPUTEVENT_MODIFIER_CONTROLKEY;
#endif  

bool InitializeSDK(void* data);
void ShutdownSDK();

class PDFEngine {
 public:

  enum DocumentPermission {
    PERMISSION_COPY,
    PERMISSION_COPY_ACCESSIBLE,
    PERMISSION_PRINT_LOW_QUALITY,
    PERMISSION_PRINT_HIGH_QUALITY,
  };

  
  class Client {
   public:
    
    virtual void DocumentSizeUpdated(const pp::Size& size) = 0;

    
    virtual void Invalidate(const pp::Rect& rect) = 0;

    
    virtual void Scroll(const pp::Point& point) = 0;

    
    virtual void ScrollToX(int position) = 0;
    virtual void ScrollToY(int position) = 0;

    
    virtual void ScrollToPage(int page) = 0;

    
    virtual void NavigateTo(const std::string& url, bool open_in_new_tab) = 0;

    
    virtual void UpdateCursor(PP_CursorType_Dev cursor) = 0;

    
    virtual void UpdateTickMarks(const std::vector<pp::Rect>& tickmarks) = 0;

    
    
    
    
    virtual void NotifyNumberOfFindResultsChanged(int total,
                                                  bool final_result) = 0;

    
    virtual void NotifySelectedFindResultChanged(int current_find_index) = 0;

    
    
    virtual void GetDocumentPassword(
        pp::CompletionCallbackWithOutput<pp::Var> callback) = 0;

    
    virtual void Alert(const std::string& message) = 0;

    
    
    virtual bool Confirm(const std::string& message) = 0;

    
    
    virtual std::string Prompt(const std::string& question,
                               const std::string& default_answer) = 0;

    
    virtual std::string GetURL() = 0;

    
    virtual void Email(const std::string& to,
                       const std::string& cc,
                       const std::string& bcc,
                       const std::string& subject,
                       const std::string& body) = 0;

    
    virtual void Print() = 0;

    
    virtual void SubmitForm(const std::string& url,
                            const void* data,
                            int length) = 0;

    
    virtual std::string ShowFileSelectionDialog() = 0;

    
    virtual pp::URLLoader CreateURLLoader() = 0;

    
    
    virtual void ScheduleCallback(int id, int delay_in_ms) = 0;

    
    
    struct SearchStringResult {
      int start_index;
      int length;
    };
    virtual void SearchString(const base::char16* string,
                              const base::char16* term,
                              bool case_sensitive,
                              std::vector<SearchStringResult>* results) = 0;

    
    virtual void DocumentPaintOccurred() = 0;

    
    virtual void DocumentLoadComplete(int page_count) = 0;

    
    virtual void DocumentLoadFailed() = 0;

    virtual pp::Instance* GetPluginInstance() = 0;

    
    virtual void DocumentHasUnsupportedFeature(const std::string& feature) = 0;

    
    virtual void DocumentLoadProgress(uint32 available, uint32 doc_size) = 0;

    
    virtual void FormTextFieldFocusChange(bool in_focus) = 0;

    
    virtual bool IsPrintPreview() = 0;
  };

  
  static PDFEngine* Create(Client* client);

  virtual ~PDFEngine() {}
  
  
  virtual bool New(const char* url) = 0;
  virtual bool New(const char* url,
                   const char* headers) = 0;
  virtual void PageOffsetUpdated(const pp::Point& page_offset) = 0;
  virtual void PluginSizeUpdated(const pp::Size& size) = 0;
  virtual void ScrolledToXPosition(int position) = 0;
  virtual void ScrolledToYPosition(int position) = 0;
  
  
  virtual void PrePaint() = 0;
  virtual void Paint(const pp::Rect& rect,
                     pp::ImageData* image_data,
                     std::vector<pp::Rect>* ready,
                     std::vector<pp::Rect>* pending) = 0;
  virtual void PostPaint() = 0;
  virtual bool HandleDocumentLoad(const pp::URLLoader& loader) = 0;
  virtual bool HandleEvent(const pp::InputEvent& event) = 0;
  virtual uint32_t QuerySupportedPrintOutputFormats() = 0;
  virtual void PrintBegin() = 0;
  virtual pp::Resource PrintPages(
      const PP_PrintPageNumberRange_Dev* page_ranges,
      uint32_t page_range_count,
      const PP_PrintSettings_Dev& print_settings) = 0;
  virtual void PrintEnd() = 0;
  virtual void StartFind(const char* text, bool case_sensitive) = 0;
  virtual bool SelectFindResult(bool forward) = 0;
  virtual void StopFind() = 0;
  virtual void ZoomUpdated(double new_zoom_level) = 0;
  virtual void RotateClockwise() = 0;
  virtual void RotateCounterclockwise() = 0;
  virtual std::string GetSelectedText() = 0;
  virtual std::string GetLinkAtPosition(const pp::Point& point) = 0;
  virtual bool IsSelecting() = 0;
  
  virtual bool HasPermission(DocumentPermission permission) const = 0;
  virtual void SelectAll() = 0;
  
  virtual int GetNumberOfPages() = 0;
  
  virtual int GetNamedDestinationPage(const std::string& destination) = 0;
  
  virtual int GetFirstVisiblePage() = 0;
  
  virtual int GetMostVisiblePage() = 0;
  
  virtual pp::Rect GetPageRect(int index) = 0;
  
  virtual pp::Rect GetPageContentsRect(int index) = 0;
  
  
  virtual int GetVerticalScrollbarYPosition() = 0;
  
  virtual void PaintThumbnail(pp::ImageData* image_data, int index) = 0;
  
  virtual void SetGrayscale(bool grayscale) = 0;
  
  virtual void OnCallback(int id) = 0;
  
  virtual std::string GetPageAsJSON(int index) = 0;
  
  
  virtual bool GetPrintScaling() = 0;

  
  
  virtual void AppendBlankPages(int num_pages) = 0;
  
  
  virtual void AppendPage(PDFEngine* engine, int index) = 0;

  
  
  
  virtual pp::Point GetScrollPosition() = 0;
  virtual void SetScrollPosition(const pp::Point& position) = 0;

  virtual bool IsProgressiveLoad() = 0;
};

class PDFEngineExports {
 public:
  struct RenderingSettings {
   RenderingSettings(int dpi_x,
                     int dpi_y,
                     const pp::Rect& bounds,
                     bool fit_to_bounds,
                     bool stretch_to_bounds,
                     bool keep_aspect_ratio,
                     bool center_in_bounds,
                     bool autorotate)
      : dpi_x(dpi_x), dpi_y(dpi_y), bounds(bounds),
        fit_to_bounds(fit_to_bounds), stretch_to_bounds(stretch_to_bounds),
        keep_aspect_ratio(keep_aspect_ratio),
        center_in_bounds(center_in_bounds), autorotate(autorotate) {
    }
    int dpi_x;
    int dpi_y;
    pp::Rect bounds;
    bool fit_to_bounds;
    bool stretch_to_bounds;
    bool keep_aspect_ratio;
    bool center_in_bounds;
    bool autorotate;
  };

  PDFEngineExports() {}
  virtual ~PDFEngineExports() {}
  static PDFEngineExports* Create();
#if defined(OS_WIN)
  
  virtual bool RenderPDFPageToDC(const void* pdf_buffer,
                                 int buffer_size,
                                 int page_number,
                                 const RenderingSettings& settings,
                                 HDC dc) = 0;
#endif  
  
  virtual bool RenderPDFPageToBitmap(const void* pdf_buffer,
                                     int pdf_buffer_size,
                                     int page_number,
                                     const RenderingSettings& settings,
                                     void* bitmap_buffer) = 0;

  virtual bool GetPDFDocInfo(const void* pdf_buffer,
                             int buffer_size,
                             int* page_count,
                             double* max_page_width) = 0;

  
  virtual bool GetPDFPageSizeByIndex(const void* pdf_buffer,
                                     int pdf_buffer_size, int page_number,
                                     double* width, double* height) = 0;
};

}  

#endif  
