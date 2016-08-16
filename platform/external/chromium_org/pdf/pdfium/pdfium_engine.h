// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_PDFIUM_PDFIUM_ENGINE_H_
#define PDF_PDFIUM_PDFIUM_ENGINE_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "pdf/document_loader.h"
#include "pdf/pdf_engine.h"
#include "pdf/pdfium/pdfium_page.h"
#include "pdf/pdfium/pdfium_range.h"
#include "ppapi/cpp/completion_callback.h"
#include "ppapi/cpp/dev/buffer_dev.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/point.h"
#include "third_party/pdfium/fpdfsdk/include/fpdf_dataavail.h"
#include "third_party/pdfium/fpdfsdk/include/fpdf_progressive.h"
#include "third_party/pdfium/fpdfsdk/include/fpdfformfill.h"
#include "third_party/pdfium/fpdfsdk/include/fpdfview.h"

namespace pp {
class KeyboardInputEvent;
class MouseInputEvent;
}

namespace chrome_pdf {

class ShadowMatrix;

class PDFiumEngine : public PDFEngine,
                     public DocumentLoader::Client,
                     public FPDF_FORMFILLINFO,
                     public IPDF_JSPLATFORM,
                     public IFSDK_PAUSE {
 public:
  explicit PDFiumEngine(PDFEngine::Client* client);
  virtual ~PDFiumEngine();

  
  virtual bool New(const char* url);
  virtual bool New(const char* url,
                   const char* headers);
  virtual void PageOffsetUpdated(const pp::Point& page_offset);
  virtual void PluginSizeUpdated(const pp::Size& size);
  virtual void ScrolledToXPosition(int position);
  virtual void ScrolledToYPosition(int position);
  virtual void PrePaint();
  virtual void Paint(const pp::Rect& rect,
                     pp::ImageData* image_data,
                     std::vector<pp::Rect>* ready,
                     std::vector<pp::Rect>* pending);
  virtual void PostPaint();
  virtual bool HandleDocumentLoad(const pp::URLLoader& loader);
  virtual bool HandleEvent(const pp::InputEvent& event);
  virtual uint32_t QuerySupportedPrintOutputFormats();
  virtual void PrintBegin();
  virtual pp::Resource PrintPages(
      const PP_PrintPageNumberRange_Dev* page_ranges,
      uint32_t page_range_count,
      const PP_PrintSettings_Dev& print_settings);
  virtual void PrintEnd();
  virtual void StartFind(const char* text, bool case_sensitive);
  virtual bool SelectFindResult(bool forward);
  virtual void StopFind();
  virtual void ZoomUpdated(double new_zoom_level);
  virtual void RotateClockwise();
  virtual void RotateCounterclockwise();
  virtual std::string GetSelectedText();
  virtual std::string GetLinkAtPosition(const pp::Point& point);
  virtual bool IsSelecting();
  virtual bool HasPermission(DocumentPermission permission) const;
  virtual void SelectAll();
  virtual int GetNumberOfPages();
  virtual int GetNamedDestinationPage(const std::string& destination);
  virtual int GetFirstVisiblePage();
  virtual int GetMostVisiblePage();
  virtual pp::Rect GetPageRect(int index);
  virtual pp::Rect GetPageContentsRect(int index);
  virtual int GetVerticalScrollbarYPosition() { return position_.y(); }
  virtual void PaintThumbnail(pp::ImageData* image_data, int index);
  virtual void SetGrayscale(bool grayscale);
  virtual void OnCallback(int id);
  virtual std::string GetPageAsJSON(int index);
  virtual bool GetPrintScaling();
  virtual void AppendBlankPages(int num_pages);
  virtual void AppendPage(PDFEngine* engine, int index);
  virtual pp::Point GetScrollPosition();
  virtual void SetScrollPosition(const pp::Point& position);
  virtual bool IsProgressiveLoad();

  
  virtual pp::Instance* GetPluginInstance();
  virtual pp::URLLoader CreateURLLoader();
  virtual void OnPartialDocumentLoaded();
  virtual void OnPendingRequestComplete();
  virtual void OnNewDataAvailable();
  virtual void OnDocumentComplete();

  void UnsupportedFeature(int type);

  std::string current_find_text() const { return current_find_text_; }

  FPDF_DOCUMENT doc() { return doc_; }
  FPDF_FORMHANDLE form() { return form_; }

 private:
  
  
  
  
  class SelectionChangeInvalidator {
   public:
    explicit SelectionChangeInvalidator(PDFiumEngine* engine);
    ~SelectionChangeInvalidator();
   private:
    
    
    void GetVisibleSelectionsScreenRects(std::vector<pp::Rect>* rects);

    PDFiumEngine* engine_;
    
    std::vector<pp::Rect> old_selections_;
    
    pp::Point previous_origin_;
  };

  
  class MouseDownState {
   public:
    MouseDownState(const PDFiumPage::Area& area,
                   const PDFiumPage::LinkTarget& target);
    ~MouseDownState();

    void Set(const PDFiumPage::Area& area,
             const PDFiumPage::LinkTarget& target);
    void Reset();
    bool Matches(const PDFiumPage::Area& area,
                 const PDFiumPage::LinkTarget& target) const;

   private:
    PDFiumPage::Area area_;
    PDFiumPage::LinkTarget target_;

    DISALLOW_COPY_AND_ASSIGN(MouseDownState);
  };

  friend class SelectionChangeInvalidator;

  struct FileAvail : public FX_FILEAVAIL {
    DocumentLoader* loader;
  };

  struct DownloadHints : public FX_DOWNLOADHINTS {
    DocumentLoader* loader;
  };

  
  static int GetBlock(void* param, unsigned long position,
                      unsigned char* buffer, unsigned long size);

  
  static bool IsDataAvail(FX_FILEAVAIL* param,
                          size_t offset, size_t size);

  
  static void AddSegment(FX_DOWNLOADHINTS* param,
                         size_t offset, size_t size);

  
  
  void LoadDocument();

  
  
  
  
  
  bool TryLoadingDoc(bool with_password,
                     const std::string& password,
                     bool* needs_password);

  
  
  void GetPasswordAndLoad();

  
  void OnGetPasswordComplete(int32_t result,
                             const pp::Var& password);

  
  
  void ContinueLoadingDocument(bool has_password,
                               const std::string& password);

  
  
  
  
  void FinishLoadingDocument();

  
  
  void LoadPageInfo(bool reload);

  
  void CalculateVisiblePages();

  
  
  bool IsPageVisible(int index) const;

  
  
  
  bool CheckPageAvailable(int index, std::vector<int>* pending);

  
  
  pp::Size GetPageSize(int index);

  void UpdateTickMarks();

  
  void ContinueFind(int32_t result);

  
  void AddFindResult(const PDFiumRange& result);

  
  
  void SearchUsingPDFium(const base::string16& term,
                         bool case_sensitive,
                         bool first_search,
                         int character_to_start_searching_from,
                         int current_page);

  
  void SearchUsingICU(const base::string16& term,
                      bool case_sensitive,
                      bool first_search,
                      int character_to_start_searching_from,
                      int current_page);

  
  bool OnMouseDown(const pp::MouseInputEvent& event);
  bool OnMouseUp(const pp::MouseInputEvent& event);
  bool OnMouseMove(const pp::MouseInputEvent& event);
  bool OnKeyDown(const pp::KeyboardInputEvent& event);
  bool OnKeyUp(const pp::KeyboardInputEvent& event);
  bool OnChar(const pp::KeyboardInputEvent& event);

  FPDF_DOCUMENT CreateSinglePageRasterPdf(
      double source_page_width,
      double source_page_height,
      const PP_PrintSettings_Dev& print_settings,
      PDFiumPage* page_to_print);

  pp::Buffer_Dev PrintPagesAsRasterPDF(
      const PP_PrintPageNumberRange_Dev* page_ranges,
      uint32_t page_range_count,
      const PP_PrintSettings_Dev& print_settings);

  pp::Buffer_Dev PrintPagesAsPDF(const PP_PrintPageNumberRange_Dev* page_ranges,
                                 uint32_t page_range_count,
                                 const PP_PrintSettings_Dev& print_settings);

  pp::Buffer_Dev GetFlattenedPrintData(const FPDF_DOCUMENT& doc);
  void FitContentsToPrintableAreaIfRequired(
      const FPDF_DOCUMENT& doc,
      const PP_PrintSettings_Dev& print_settings);
  void SaveSelectedFormForPrint();

  
  
  PDFiumPage::Area GetCharIndex(const pp::MouseInputEvent& event,
                                int* page_index,
                                int* char_index,
                                PDFiumPage::LinkTarget* target);
  PDFiumPage::Area GetCharIndex(const pp::Point& point,
                                int* page_index,
                                int* char_index,
                                PDFiumPage::LinkTarget* target);

  void OnSingleClick(int page_index, int char_index);
  void OnMultipleClick(int click_count, int page_index, int char_index);

  
  
  int StartPaint(int page_index, const pp::Rect& dirty);

  
  
  bool ContinuePaint(int progressive_index, pp::ImageData* image_data);

  
  
  void FinishPaint(int progressive_index, pp::ImageData* image_data);

  
  void CancelPaints();

  
  
  void InvalidateAllPages();

  
  
  void FillPageSides(int progressive_index);

  void PaintPageShadow(int progressive_index, pp::ImageData* image_data);

  
  void DrawSelections(int progressive_index, pp::ImageData* image_data);

  
  void PaintUnavailablePage(int page_index,
                            const pp::Rect& dirty,
                            pp::ImageData* image_data);

  
  
  int GetProgressiveIndex(int page_index) const;

  
  FPDF_BITMAP CreateBitmap(const pp::Rect& rect,
                           pp::ImageData* image_data) const;

  
  
  void GetPDFiumRect(int page_index, const pp::Rect& rect, int* start_x,
                     int* start_y, int* size_x, int* size_y) const;

  
  int GetRenderingFlags() const;

  
  pp::Rect GetVisibleRect() const;

  
  
  pp::Rect GetPageScreenRect(int page_index) const;

  
  
  
  pp::Rect GetScreenRect(const pp::Rect& rect) const;

  
  void Highlight(void* buffer,
                 int stride,
                 const pp::Rect& rect,
                 std::vector<pp::Rect>* highlighted_rects);

  
  
  void DeviceToPage(int page_index,
                    float device_x,
                    float device_y,
                    double* page_x,
                    double* page_y);

  
  
  int GetVisiblePageIndex(FPDF_PAGE page);

  
  
  void SetCurrentPage(int index);

  
  void TransformPDFPageForPrinting(FPDF_PAGE page,
                                   const PP_PrintSettings_Dev& print_settings);

  void DrawPageShadow(const pp::Rect& page_rect,
                      const pp::Rect& shadow_rect,
                      const pp::Rect& clip_rect,
                      pp::ImageData* image_data);

  void GetRegion(const pp::Point& location,
                 pp::ImageData* image_data,
                 void** region,
                 int* stride) const;

  
  void OnSelectionChanged();

  
  static void Form_Invalidate(FPDF_FORMFILLINFO* param,
                              FPDF_PAGE page,
                              double left,
                              double top,
                              double right,
                              double bottom);
  static void Form_OutputSelectedRect(FPDF_FORMFILLINFO* param,
                                      FPDF_PAGE page,
                                      double left,
                                      double top,
                                      double right,
                                      double bottom);
  static void Form_SetCursor(FPDF_FORMFILLINFO* param, int cursor_type);
  static int Form_SetTimer(FPDF_FORMFILLINFO* param,
                           int elapse,
                           TimerCallback timer_func);
  static void Form_KillTimer(FPDF_FORMFILLINFO* param, int timer_id);
  static FPDF_SYSTEMTIME Form_GetLocalTime(FPDF_FORMFILLINFO* param);
  static void Form_OnChange(FPDF_FORMFILLINFO* param);
  static FPDF_PAGE Form_GetPage(FPDF_FORMFILLINFO* param,
                                FPDF_DOCUMENT document,
                                int page_index);
  static FPDF_PAGE Form_GetCurrentPage(FPDF_FORMFILLINFO* param,
                                       FPDF_DOCUMENT document);
  static int Form_GetRotation(FPDF_FORMFILLINFO* param, FPDF_PAGE page);
  static void Form_ExecuteNamedAction(FPDF_FORMFILLINFO* param,
                                      FPDF_BYTESTRING named_action);
  static void Form_SetTextFieldFocus(FPDF_FORMFILLINFO* param,
                                     FPDF_WIDESTRING value,
                                     FPDF_DWORD valueLen,
                                     FPDF_BOOL is_focus);
  static void Form_DoURIAction(FPDF_FORMFILLINFO* param, FPDF_BYTESTRING uri);
  static void Form_DoGoToAction(FPDF_FORMFILLINFO* param,
                                int page_index,
                                int zoom_mode,
                                float* position_array,
                                int size_of_array);

  
  static int Form_Alert(IPDF_JSPLATFORM* param,
                        FPDF_WIDESTRING message,
                        FPDF_WIDESTRING title,
                        int type,
                        int icon);
  static void Form_Beep(IPDF_JSPLATFORM* param, int type);
  static int Form_Response(IPDF_JSPLATFORM* param,
                           FPDF_WIDESTRING question,
                           FPDF_WIDESTRING title,
                           FPDF_WIDESTRING default_response,
                           FPDF_WIDESTRING label,
                           FPDF_BOOL password,
                           void* response,
                           int length);
  static int Form_GetFilePath(IPDF_JSPLATFORM* param,
                              void* file_path,
                              int length);
  static void Form_Mail(IPDF_JSPLATFORM* param,
                        void* mail_data,
                        int length,
                        FPDF_BOOL ui,
                        FPDF_WIDESTRING to,
                        FPDF_WIDESTRING subject,
                        FPDF_WIDESTRING cc,
                        FPDF_WIDESTRING bcc,
                        FPDF_WIDESTRING message);
  static void Form_Print(IPDF_JSPLATFORM* param,
                         FPDF_BOOL ui,
                         int start,
                         int end,
                         FPDF_BOOL silent,
                         FPDF_BOOL shrink_to_fit,
                         FPDF_BOOL print_as_image,
                         FPDF_BOOL reverse,
                         FPDF_BOOL annotations);
  static void Form_SubmitForm(IPDF_JSPLATFORM* param,
                              void* form_data,
                              int length,
                              FPDF_WIDESTRING url);
  static void Form_GotoPage(IPDF_JSPLATFORM* param, int page_number);
  static int Form_Browse(IPDF_JSPLATFORM* param, void* file_path, int length);

  
  static FPDF_BOOL Pause_NeedToPauseNow(IFSDK_PAUSE* param);

  PDFEngine::Client* client_;
  pp::Size document_size_;  

  
  pp::Point position_;
  
  pp::Point page_offset_;
  
  pp::Size plugin_size_;
  double current_zoom_;
  unsigned int current_rotation_;

  DocumentLoader doc_loader_;  
  std::string url_;
  std::string headers_;
  pp::CompletionCallbackFactory<PDFiumEngine> find_factory_;

  pp::CompletionCallbackFactory<PDFiumEngine> password_factory_;
  int32_t password_tries_remaining_;

  
  std::string current_find_text_;

  
  FPDF_DOCUMENT doc_;

  
  
  FPDF_FORMHANDLE form_;

  
  
  
  std::vector<PDFiumPage*> pages_;

  
  std::vector<int> visible_pages_;

  
  std::vector<int> pending_pages_;

  
  
  
  bool defer_page_unload_;
  std::vector<int> deferred_page_unloads_;

  
  
  std::vector<PDFiumRange> selection_;
  
  bool selecting_;

  MouseDownState mouse_down_state_;

  
  typedef std::vector<PDFiumRange> FindResults;
  FindResults find_results_;
  
  int next_page_to_search_;
  
  int last_page_to_search_;
  int last_character_index_to_search_;  
  
  int current_find_index_;

  
  unsigned long permissions_;

  
  FPDF_FILEACCESS file_access_;
  
  FileAvail file_availability_;
  
  DownloadHints download_hints_;
  
  FPDF_AVAIL fpdf_availability_;

  pp::Size default_page_size_;

  
  
  std::map<int, std::pair<int, TimerCallback> > timers_;
  int next_timer_id_;

  
  int last_page_mouse_down_;

  
  
  int first_visible_page_;

  
  
  int most_visible_page_;

  
  
  bool called_do_document_action_;

  
  
  std::vector<pp::Rect> form_highlights_;

  
  bool render_grayscale_;

  
  std::string link_under_cursor_;

  
  struct ProgressivePaint {
    pp::Rect rect;  
    FPDF_BITMAP bitmap;
    int page_index;
    
    
    int painted_;
  };
  std::vector<ProgressivePaint> progressive_paints_;

  
  
  base::Time last_progressive_start_time_;

  
  int progressive_paint_timeout_;

  
  scoped_ptr<ShadowMatrix> page_shadow_;

  
  
  bool getting_password_;
};

class ScopedUnsupportedFeature {
 public:
  explicit ScopedUnsupportedFeature(PDFiumEngine* engine);
  ~ScopedUnsupportedFeature();
 private:
  PDFiumEngine* engine_;
  PDFiumEngine* old_engine_;
};

class PDFiumEngineExports : public PDFEngineExports {
 public:
  PDFiumEngineExports() {}
#if defined(OS_WIN)
  
  virtual bool RenderPDFPageToDC(const void* pdf_buffer,
                                 int buffer_size,
                                 int page_number,
                                 const RenderingSettings& settings,
                                 HDC dc);
#endif  
  virtual bool RenderPDFPageToBitmap(const void* pdf_buffer,
                                     int pdf_buffer_size,
                                     int page_number,
                                     const RenderingSettings& settings,
                                     void* bitmap_buffer);

  virtual bool GetPDFDocInfo(const void* pdf_buffer,
                             int buffer_size,
                             int* page_count,
                             double* max_page_width);

  
  virtual bool GetPDFPageSizeByIndex(const void* pdf_buffer,
                                     int pdf_buffer_size, int page_number,
                                     double* width, double* height);
};

}  

#endif  
