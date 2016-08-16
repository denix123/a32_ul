// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_INSTANCE_H_
#define PDF_INSTANCE_H_

#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "pdf/button.h"
#include "pdf/fading_controls.h"
#include "pdf/page_indicator.h"
#include "pdf/paint_manager.h"
#include "pdf/pdf_engine.h"
#include "pdf/preview_mode_client.h"
#include "pdf/progress_control.h"
#include "pdf/thumbnail_control.h"

#include "ppapi/c/private/ppb_pdf.h"
#include "ppapi/cpp/dev/printing_dev.h"
#include "ppapi/cpp/dev/scriptable_object_deprecated.h"
#include "ppapi/cpp/dev/scrollbar_dev.h"
#include "ppapi/cpp/dev/selection_dev.h"
#include "ppapi/cpp/dev/widget_client_dev.h"
#include "ppapi/cpp/dev/zoom_dev.h"
#include "ppapi/cpp/graphics_2d.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/private/find_private.h"
#include "ppapi/cpp/private/instance_private.h"
#include "ppapi/cpp/private/var_private.h"
#include "ppapi/cpp/url_loader.h"
#include "ppapi/utility/completion_callback_factory.h"

namespace pp {
class TextInput_Dev;
}

namespace chrome_pdf {

struct ToolbarButtonInfo;

class Instance : public pp::InstancePrivate,
                 public pp::Find_Private,
                 public pp::Printing_Dev,
                 public pp::Selection_Dev,
                 public pp::WidgetClient_Dev,
                 public pp::Zoom_Dev,
                 public PaintManager::Client,
                 public PDFEngine::Client,
                 public PreviewModeClient::Client,
                 public ControlOwner {
 public:
  explicit Instance(PP_Instance instance);
  virtual ~Instance();

  
  virtual bool Init(uint32_t argc,
                    const char* argn[],
                    const char* argv[]) OVERRIDE;
  virtual bool HandleDocumentLoad(const pp::URLLoader& loader) OVERRIDE;
  virtual bool HandleInputEvent(const pp::InputEvent& event) OVERRIDE;
  virtual void DidChangeView(const pp::View& view) OVERRIDE;
  virtual pp::Var GetInstanceObject() OVERRIDE;

  
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

  
  virtual void InvalidateWidget(pp::Widget_Dev widget,
                                const pp::Rect& dirty_rect) OVERRIDE;
  virtual void ScrollbarValueChanged(pp::Scrollbar_Dev scrollbar,
                                     uint32_t value) OVERRIDE;
  virtual void ScrollbarOverlayChanged(pp::Scrollbar_Dev scrollbar,
                                       bool overlay) OVERRIDE;

  
  virtual void Zoom(double scale, bool text_only) OVERRIDE;
  void ZoomChanged(double factor);  

  void FlushCallback(int32_t result);
  void DidOpen(int32_t result);
  void DidOpenPreview(int32_t result);
  
  
  void PaintIfWidgetIntersects(pp::Widget_Dev* widget,
                               const pp::Rect& rect,
                               std::vector<PaintManager::ReadyRect>* ready,
                               std::vector<pp::Rect>* pending);

  
  void OnTimerFired(int32_t);
  void OnClientTimerFired(int32_t id);

  
  void OnControlTimerFired(int32_t,
                           const uint32& control_id,
                           const uint32& timer_id);

  
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

  
  virtual void OnEvent(uint32 control_id, uint32 event_id, void* data);
  virtual void Invalidate(uint32 control_id, const pp::Rect& rc);
  virtual uint32 ScheduleTimer(uint32 control_id, uint32 timeout_ms);
  virtual void SetEventCapture(uint32 control_id, bool set_capture);
  virtual void SetCursor(uint32 control_id, PP_CursorType_Dev cursor_type);
  virtual pp::Instance* GetInstance();

  bool dont_paint() const { return dont_paint_; }
  void set_dont_paint(bool dont_paint) { dont_paint_ = dont_paint; }

  
  bool HasScriptableMethod(const pp::Var& method, pp::Var* exception);
  pp::Var CallScriptableMethod(const pp::Var& method,
                               const std::vector<pp::Var>& args,
                               pp::Var* exception);

  
  virtual void PreviewDocumentLoadComplete() OVERRIDE;
  virtual void PreviewDocumentLoadFailed() OVERRIDE;

  
  void RotateClockwise();
  void RotateCounterclockwise();

 private:
  
  
  void OnGeometryChanged(double old_zoom, float old_device_scale);

  
  void RunCallback(int32_t, pp::Var callback);

  void CreateHorizontalScrollbar();
  void CreateVerticalScrollbar();
  void DestroyHorizontalScrollbar();
  void DestroyVerticalScrollbar();

  
  
  int GetScrollbarThickness();

  
  
  int GetScrollbarReservedThickness();

  
  bool IsOverlayScrollbar();

  
  
  void CalculateBackgroundParts();

  
  
  int GetDocumentPixelWidth() const;
  int GetDocumentPixelHeight() const;

  
  void FillRect(const pp::Rect& rect, uint32 color);

  std::vector<pp::ImageData> GetThumbnailResources();
  std::vector<pp::ImageData> GetProgressBarResources(pp::ImageData* background);

  void CreateToolbar(const ToolbarButtonInfo* tb_info, size_t size);
  int GetToolbarRightOffset();
  int GetToolbarBottomOffset();
  void CreateProgressBar();
  void ConfigureProgressBar();
  void CreateThumbnails();
  void CreatePageIndicator(bool always_visible);
  void ConfigurePageIndicator();

  void PaintOverlayControl(Control* ctrl,
                           pp::ImageData* image_data,
                           std::vector<PaintManager::ReadyRect>* ready);

  void LoadUrl(const std::string& url);
  void LoadPreviewUrl(const std::string& url);
  void LoadUrlInternal(const std::string& url, pp::URLLoader* loader,
                       void (Instance::* method)(int32_t));

  
  
  pp::URLLoader CreateURLLoaderInternal();

  
  
  
  
  int GetInitialPage(const std::string& url);

  void UpdateToolbarPosition(bool invalidate);
  void UpdateProgressBarPosition(bool invalidate);
  void UpdatePageIndicatorPosition(bool invalidate);

  void FormDidOpen(int32_t result);

  std::string GetLocalizedString(PP_ResourceString id);

  void UserMetricsRecordAction(const std::string& action);

  void SaveAs();

  enum ZoomMode {
    ZOOM_SCALE,  
    ZOOM_FIT_TO_WIDTH,  
    ZOOM_FIT_TO_PAGE,  
    ZOOM_AUTO  
  };

  enum DocumentLoadState {
    LOAD_STATE_LOADING,
    LOAD_STATE_COMPLETE,
    LOAD_STATE_FAILED,
  };

  
  void SetZoom(ZoomMode zoom_mode, double scale);

  
  
  void UpdateZoomScale();

  
  
  
  
  double CalculateZoom(uint32 control_id) const;

  pp::ImageData CreateResourceImage(PP_ResourceImage image_id);

  void DrawText(const pp::Point& top_center, PP_ResourceString id);

  
  
  
  void SetPrintPreviewMode(int page_count);

  
  
  
  int GetPageNumberToDisplay();

  
  
  
  
  
  void ProcessPreviewPageInfo(const std::string& src_url, int dst_page_index);
  
  void LoadAvailablePreviewPage();

  
  void EnableAutoscroll(const pp::Point& origin);
  
  void DisableAutoscroll();
  
  
  PP_CursorType_Dev CalculateAutoscroll(const pp::Point& mouse_pos);

  void ConfigureNumberImageGenerator();

  NumberImageGenerator* number_image_generator();

  int GetScaled(int x) const;

  pp::ImageData image_data_;
  
  
  pp::CompletionCallbackFactory<Instance> loader_factory_;
  pp::URLLoader embed_loader_;
  pp::URLLoader embed_preview_loader_;

  scoped_ptr<pp::Scrollbar_Dev> h_scrollbar_;
  scoped_ptr<pp::Scrollbar_Dev> v_scrollbar_;
  int32 valid_v_range_;

  PP_CursorType_Dev cursor_;  

  
  
  bool timer_pending_;
  pp::MouseInputEvent last_mouse_event_;
  pp::CompletionCallbackFactory<Instance> timer_factory_;
  uint32 current_timer_id_;

  
  pp::Size plugin_size_;
  
  pp::Size plugin_dip_size_;
  
  
  pp::Rect available_area_;
  
  
  pp::Size document_size_;

  double zoom_;  

  float device_scale_;  
  bool printing_enabled_;
  bool hidpi_enabled_;
  
  bool full_;
  
  ZoomMode zoom_mode_;

  
  
  
  bool did_call_start_loading_;

  
  bool dont_paint_;

  
  bool is_autoscroll_;
  
  pp::Rect autoscroll_rect_;
  
  pp::ImageData autoscroll_anchor_;
  
  int autoscroll_x_;
  int autoscroll_y_;

  
  int scrollbar_thickness_;

  
  
  int scrollbar_reserved_thickness_;

  
  const ToolbarButtonInfo* current_tb_info_;
  size_t current_tb_info_size_;

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

  scoped_ptr<FadingControls> toolbar_;
  ThumbnailControl thumbnails_;
  ProgressControl progress_bar_;
  uint32 delayed_progress_timer_id_;
  PageIndicator page_indicator_;

  
  scoped_ptr<NumberImageGenerator> number_image_generator_;

  
  pp::CompletionCallbackFactory<Instance> form_factory_;
  pp::URLLoader form_loader_;

  
  
  
  pp::CompletionCallbackFactory<Instance> callback_factory_;

  
  bool first_paint_;

  
  bool painted_first_page_;

  
  bool show_page_indicator_;

  
  pp::Var on_load_callback_;
  pp::Var on_scroll_callback_;
  pp::Var on_plugin_size_changed_callback_;

  DocumentLoadState document_load_state_;
  DocumentLoadState preview_document_load_state_;

  
  
  pp::VarPrivate instance_object_;

  
  
  bool told_browser_about_unsupported_feature_;

  
  
  std::set<std::string> unsupported_features_reported_;

  
  int print_preview_page_count_;
  std::vector<int> print_preview_page_numbers_;

  
  
  
  typedef std::pair<std::string, int> PreviewPageInfo;
  std::queue<PreviewPageInfo> preview_pages_info_;

  
  
  
  scoped_ptr<pp::TextInput_Dev> text_input_;
};

class PDFScriptableObject : public pp::deprecated::ScriptableObject {
 public:
  explicit PDFScriptableObject(Instance* instance);
  virtual ~PDFScriptableObject();

  
  virtual bool HasMethod(const pp::Var& method, pp::Var* exception);
  virtual pp::Var Call(const pp::Var& method,
                       const std::vector<pp::Var>& args,
                       pp::Var* exception);

 private:
  Instance* instance_;
};

}  

#endif  
