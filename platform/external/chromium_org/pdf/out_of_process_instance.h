// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_OUT_OF_PROCESS_INSTANCE_H_
#define PDF_OUT_OF_PROCESS_INSTANCE_H_

#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "pdf/paint_manager.h"
#include "pdf/pdf_engine.h"
#include "pdf/preview_mode_client.h"

#include "ppapi/c/private/ppb_pdf.h"
#include "ppapi/cpp/dev/printing_dev.h"
#include "ppapi/cpp/dev/scriptable_object_deprecated.h"
#include "ppapi/cpp/dev/selection_dev.h"
#include "ppapi/cpp/graphics_2d.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/private/find_private.h"
#include "ppapi/cpp/private/uma_private.h"
#include "ppapi/cpp/url_loader.h"
#include "ppapi/utility/completion_callback_factory.h"

namespace pp {
class TextInput_Dev;
}

namespace chrome_pdf {

class OutOfProcessInstance : public pp::Instance,
                             public pp::Find_Private,
                             public pp::Printing_Dev,
                             public pp::Selection_Dev,
                             public PaintManager::Client,
                             public PDFEngine::Client,
                             public PreviewModeClient::Client {
 public:
  explicit OutOfProcessInstance(PP_Instance instance);
  virtual ~OutOfProcessInstance();

  
  virtual bool Init(uint32_t argc,
                    const char* argn[],
                    const char* argv[]) OVERRIDE;
  virtual void HandleMessage(const pp::Var& message) OVERRIDE;
  virtual bool HandleInputEvent(const pp::InputEvent& event) OVERRIDE;
  virtual void DidChangeView(const pp::View& view) OVERRIDE;

  
  virtual bool StartFind(const std::string& text, bool case_sensitive) OVERRIDE;
  virtual void SelectFindResult(bool forward) OVERRIDE;
  virtual void StopFind() OVERRIDE;

  
  virtual void OnPaint(const std::vector<pp::Rect>& paint_rects,
                       std::vector<PaintManager::ReadyRect>* ready,
                       std::vector<pp::Rect>* pending) OVERRIDE;

  
  virtual uint32_t QuerySupportedPrintOutputFormats() OVERRIDE;
  virtual int32_t PrintBegin(
      const PP_PrintSettings_Dev& print_settings) OVERRIDE;
  virtual pp::Resource PrintPages(
      const PP_PrintPageNumberRange_Dev* page_ranges,
      uint32_t page_range_count) OVERRIDE;
  virtual void PrintEnd() OVERRIDE;
  virtual bool IsPrintScalingDisabled() OVERRIDE;

  
  virtual pp::Var GetLinkAtPosition(const pp::Point& point);

  
  virtual pp::Var GetSelectedText(bool html) OVERRIDE;

  void FlushCallback(int32_t result);
  void DidOpen(int32_t result);
  void DidOpenPreview(int32_t result);

  
  void OnClientTimerFired(int32_t id);

  
  void OnPrint(int32_t);

  
  virtual void DocumentSizeUpdated(const pp::Size& size);
  virtual void Invalidate(const pp::Rect& rect);
  virtual void Scroll(const pp::Point& point);
  virtual void ScrollToX(int position);
  virtual void ScrollToY(int position);
  virtual void ScrollToPage(int page);
  virtual void NavigateTo(const std::string& url, bool open_in_new_tab);
  virtual void UpdateCursor(PP_CursorType_Dev cursor);
  virtual void UpdateTickMarks(const std::vector<pp::Rect>& tickmarks);
  virtual void NotifyNumberOfFindResultsChanged(int total, bool final_result);
  virtual void NotifySelectedFindResultChanged(int current_find_index);
  virtual void GetDocumentPassword(
      pp::CompletionCallbackWithOutput<pp::Var> callback);
  virtual void Alert(const std::string& message);
  virtual bool Confirm(const std::string& message);
  virtual std::string Prompt(const std::string& question,
                             const std::string& default_answer);
  virtual std::string GetURL();
  virtual void Email(const std::string& to,
                     const std::string& cc,
                     const std::string& bcc,
                     const std::string& subject,
                     const std::string& body);
  virtual void Print();
  virtual void SubmitForm(const std::string& url,
                          const void* data,
                          int length);
  virtual std::string ShowFileSelectionDialog();
  virtual pp::URLLoader CreateURLLoader();
  virtual void ScheduleCallback(int id, int delay_in_ms);
  virtual void SearchString(const base::char16* string,
                            const base::char16* term,
                            bool case_sensitive,
                            std::vector<SearchStringResult>* results);
  virtual void DocumentPaintOccurred();
  virtual void DocumentLoadComplete(int page_count);
  virtual void DocumentLoadFailed();
  virtual pp::Instance* GetPluginInstance();
  virtual void DocumentHasUnsupportedFeature(const std::string& feature);
  virtual void DocumentLoadProgress(uint32 available, uint32 doc_size);
  virtual void FormTextFieldFocusChange(bool in_focus);
  virtual bool IsPrintPreview();

  
  virtual void PreviewDocumentLoadComplete() OVERRIDE;
  virtual void PreviewDocumentLoadFailed() OVERRIDE;

  
  void RotateClockwise();
  void RotateCounterclockwise();

 private:
  void ResetRecentlySentFindUpdate(int32_t);

  
  
  void OnGeometryChanged(double old_zoom, float old_device_scale);

  
  
  void CalculateBackgroundParts();

  
  
  int GetDocumentPixelWidth() const;
  int GetDocumentPixelHeight() const;

  
  void FillRect(const pp::Rect& rect, uint32 color);

  void LoadUrl(const std::string& url);
  void LoadPreviewUrl(const std::string& url);
  void LoadUrlInternal(const std::string& url, pp::URLLoader* loader,
                       void (OutOfProcessInstance::* method)(int32_t));

  
  
  pp::URLLoader CreateURLLoaderInternal();

  
  
  
  
  int GetInitialPage(const std::string& url);

  void FormDidOpen(int32_t result);

  std::string GetLocalizedString(PP_ResourceString id);

  void UserMetricsRecordAction(const std::string& action);

  enum DocumentLoadState {
    LOAD_STATE_LOADING,
    LOAD_STATE_COMPLETE,
    LOAD_STATE_FAILED,
  };

  
  void SetZoom(double scale);

  
  
  void AppendBlankPrintPreviewPages();

  
  
  
  
  
  void ProcessPreviewPageInfo(const std::string& src_url, int dst_page_index);
  
  void LoadAvailablePreviewPage();

  
  pp::Point BoundScrollOffsetToDocument(const pp::Point& scroll_offset);

  pp::ImageData image_data_;
  
  
  pp::CompletionCallbackFactory<OutOfProcessInstance> loader_factory_;
  pp::URLLoader embed_loader_;
  pp::URLLoader embed_preview_loader_;

  PP_CursorType_Dev cursor_;  

  pp::CompletionCallbackFactory<OutOfProcessInstance> timer_factory_;

  
  pp::Size plugin_size_;
  
  pp::Size plugin_dip_size_;
  
  
  pp::Rect available_area_;
  
  
  pp::Size document_size_;

  double zoom_;  

  float device_scale_;  
  bool printing_enabled_;
  
  bool full_;

  PaintManager paint_manager_;

  struct BackgroundPart {
    pp::Rect location;
    uint32 color;
  };
  std::vector<BackgroundPart> background_parts_;

  struct PrintSettings {
    PrintSettings() {
      Clear();
    }
    void Clear() {
      is_printing = false;
      print_pages_called_ = false;
      memset(&pepper_print_settings, 0, sizeof(pepper_print_settings));
    }
    
    
    bool is_printing;
    
    
    bool print_pages_called_;
    PP_PrintSettings_Dev pepper_print_settings;
  };

  PrintSettings print_settings_;

  scoped_ptr<PDFEngine> engine_;

  
  
  
  scoped_ptr<PDFEngine> preview_engine_;

  std::string url_;

  
  pp::CompletionCallbackFactory<OutOfProcessInstance> form_factory_;
  pp::URLLoader form_loader_;

  
  pp::CompletionCallbackFactory<OutOfProcessInstance> print_callback_factory_;

  
  bool first_paint_;

  DocumentLoadState document_load_state_;
  DocumentLoadState preview_document_load_state_;

  
  pp::UMAPrivate uma_;

  
  
  bool told_browser_about_unsupported_feature_;

  
  
  std::set<std::string> unsupported_features_reported_;

  
  int print_preview_page_count_;
  std::vector<int> print_preview_page_numbers_;

  
  
  
  typedef std::pair<std::string, int> PreviewPageInfo;
  std::queue<PreviewPageInfo> preview_pages_info_;

  
  
  
  scoped_ptr<pp::TextInput_Dev> text_input_;

  
  double last_progress_sent_;

  
  
  bool recently_sent_find_update_;

  
  std::vector<pp::Rect> tickmarks_;

  
  
  bool received_viewport_message_;

  
  
  
  bool did_call_start_loading_;

  
  
  
  bool stop_scrolling_;

  
  scoped_ptr<pp::CompletionCallbackWithOutput<pp::Var> > password_callback_;
};

}  

#endif  
