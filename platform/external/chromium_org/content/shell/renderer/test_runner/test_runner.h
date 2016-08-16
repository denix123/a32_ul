// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_TEST_RUNNER_TEST_RUNNER_H_
#define CONTENT_SHELL_RENDERER_TEST_RUNNER_TEST_RUNNER_H_

#include <deque>
#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/shell/renderer/test_runner/web_task.h"
#include "content/shell/renderer/test_runner/web_test_runner.h"
#include "v8/include/v8.h"

class GURL;
class SkBitmap;

namespace blink {
class WebFrame;
class WebNotificationPresenter;
class WebPermissionClient;
class WebString;
class WebView;
class WebURLResponse;
}

namespace gin {
class ArrayBufferView;
class Arguments;
}

namespace content {

class InvokeCallbackTask;
class NotificationPresenter;
class TestInterfaces;
class TestPageOverlay;
class WebPermissions;
class WebTestDelegate;
class WebTestProxyBase;

class TestRunner : public WebTestRunner,
                   public base::SupportsWeakPtr<TestRunner> {
 public:
  explicit TestRunner(TestInterfaces*);
  virtual ~TestRunner();

  void Install(blink::WebFrame* frame);

  void SetDelegate(WebTestDelegate*);
  void SetWebView(blink::WebView*, WebTestProxyBase*);

  void Reset();

  WebTaskList* mutable_task_list() { return &task_list_; }

  void SetTestIsRunning(bool);
  bool TestIsRunning() const { return test_is_running_; }

  bool UseMockTheme() const { return use_mock_theme_; }

  void InvokeCallback(scoped_ptr<InvokeCallbackTask> callback);

  
  virtual bool ShouldGeneratePixelResults() OVERRIDE;
  virtual bool ShouldDumpAsAudio() const OVERRIDE;
  virtual void GetAudioData(
      std::vector<unsigned char>* buffer_view) const OVERRIDE;
  virtual bool ShouldDumpBackForwardList() const OVERRIDE;
  virtual blink::WebPermissionClient* GetWebPermissions() const OVERRIDE;

  
  bool shouldDumpSelectionRect() const;
  bool isPrinting() const;
  bool shouldDumpAsText();
  bool shouldDumpAsTextWithPixelResults();
  bool shouldDumpAsCustomText() const;
  std:: string customDumpText() const;
  bool shouldDumpAsMarkup();
  bool shouldDumpChildFrameScrollPositions() const;
  bool shouldDumpChildFramesAsMarkup() const;
  bool shouldDumpChildFramesAsText() const;
  void ShowDevTools(const std::string& settings,
                    const std::string& frontend_url);
  void ClearDevToolsLocalStorage();
  void setShouldDumpAsText(bool);
  void setShouldDumpAsMarkup(bool);
  void setCustomTextOutput(std::string text);
  void setShouldGeneratePixelResults(bool);
  void setShouldDumpFrameLoadCallbacks(bool);
  void setShouldDumpPingLoaderCallbacks(bool);
  void setShouldEnableViewSource(bool);
  bool shouldDumpEditingCallbacks() const;
  bool shouldDumpFrameLoadCallbacks() const;
  bool shouldDumpPingLoaderCallbacks() const;
  bool shouldDumpUserGestureInFrameLoadCallbacks() const;
  bool shouldDumpTitleChanges() const;
  bool shouldDumpIconChanges() const;
  bool shouldDumpCreateView() const;
  bool canOpenWindows() const;
  bool shouldDumpResourceLoadCallbacks() const;
  bool shouldDumpResourceRequestCallbacks() const;
  bool shouldDumpResourceResponseMIMETypes() const;
  bool shouldDumpStatusCallbacks() const;
  bool shouldDumpProgressFinishedCallback() const;
  bool shouldDumpSpellCheckCallbacks() const;
  bool shouldStayOnPageAfterHandlingBeforeUnload() const;
  bool shouldWaitUntilExternalURLLoad() const;
  const std::set<std::string>* httpHeadersToClear() const;
  void setTopLoadingFrame(blink::WebFrame*, bool);
  blink::WebFrame* topLoadingFrame() const;
  void policyDelegateDone();
  bool policyDelegateEnabled() const;
  bool policyDelegateIsPermissive() const;
  bool policyDelegateShouldNotifyDone() const;
  bool shouldInterceptPostMessage() const;
  bool shouldDumpResourcePriorities() const;
  blink::WebNotificationPresenter* notification_presenter() const;
  bool RequestPointerLock();
  void RequestPointerUnlock();
  bool isPointerLocked();
  void setToolTipText(const blink::WebString&);

  bool midiAccessorResult();

  
  class WorkItem {
   public:
    virtual ~WorkItem() {}

    
    virtual bool Run(WebTestDelegate*, blink::WebView*) = 0;
  };

 private:
  friend class InvokeCallbackTask;
  friend class TestRunnerBindings;
  friend class WorkQueue;

  
  
  class WorkQueue {
   public:
    explicit WorkQueue(TestRunner* controller);
    virtual ~WorkQueue();
    void ProcessWorkSoon();

    
    void Reset();

    void AddWork(WorkItem*);

    void set_frozen(bool frozen) { frozen_ = frozen; }
    bool is_empty() { return queue_.empty(); }
    WebTaskList* mutable_task_list() { return &task_list_; }

   private:
    void ProcessWork();

    class WorkQueueTask : public WebMethodTask<WorkQueue> {
     public:
      WorkQueueTask(WorkQueue* object) : WebMethodTask<WorkQueue>(object) {}

      virtual void RunIfValid() OVERRIDE;
    };

    WebTaskList task_list_;
    std::deque<WorkItem*> queue_;
    bool frozen_;
    TestRunner* controller_;
  };

  
  

  
  
  void NotifyDone();
  void WaitUntilDone();

  
  
  void QueueBackNavigation(int how_far_back);
  void QueueForwardNavigation(int how_far_forward);
  void QueueReload();
  void QueueLoadingScript(const std::string& script);
  void QueueNonLoadingScript(const std::string& script);
  void QueueLoad(const std::string& url, const std::string& target);
  void QueueLoadHTMLString(gin::Arguments* args);

  
  
  
  void SetCustomPolicyDelegate(gin::Arguments* args);

  
  void WaitForPolicyDelegate();

  
  int WindowCount();
  void SetCloseRemainingWindowsWhenComplete(bool close_remaining_windows);
  void ResetTestHelperControllers();

  
  

  
  
  void SetTabKeyCyclesThroughElements(bool tab_key_cycles_through_elements);

  
  void ExecCommand(gin::Arguments* args);

  
  bool IsCommandEnabled(const std::string& command);

  bool CallShouldCloseOnWebView();
  void SetDomainRelaxationForbiddenForURLScheme(bool forbidden,
                                                const std::string& scheme);
  v8::Handle<v8::Value> EvaluateScriptInIsolatedWorldAndReturnValue(
      int world_id, const std::string& script);
  void EvaluateScriptInIsolatedWorld(int world_id, const std::string& script);
  void SetIsolatedWorldSecurityOrigin(int world_id,
                                      v8::Handle<v8::Value> origin);
  void SetIsolatedWorldContentSecurityPolicy(int world_id,
                                             const std::string& policy);

  
  void AddOriginAccessWhitelistEntry(const std::string& source_origin,
                                     const std::string& destination_protocol,
                                     const std::string& destination_host,
                                     bool allow_destination_subdomains);
  void RemoveOriginAccessWhitelistEntry(const std::string& source_origin,
                                        const std::string& destination_protocol,
                                        const std::string& destination_host,
                                        bool allow_destination_subdomains);

  
  
  bool HasCustomPageSizeStyle(int page_index);

  
  void ForceRedSelectionColors();

  
  void InjectStyleSheet(const std::string& source_code, bool all_frames);

  bool FindString(const std::string& search_text,
                  const std::vector<std::string>& options_array);

  std::string SelectionAsMarkup();

  
  
  
  
  
  void SetTextSubpixelPositioning(bool value);

  
  void SetPageVisibility(const std::string& new_visibility);

  
  void SetTextDirection(const std::string& direction_name);

  
  
  // some tests that were written before browsers had multi-process architecture
  
  
  
  
  void UseUnfortunateSynchronousResizeMode();

  bool EnableAutoResizeMode(int min_width,
                            int min_height,
                            int max_width,
                            int max_height);
  bool DisableAutoResizeMode(int new_width, int new_height);

  void SetMockDeviceLight(double value);
  void ResetDeviceLight();
  
  void SetMockDeviceMotion(bool has_acceleration_x, double acceleration_x,
                           bool has_acceleration_y, double acceleration_y,
                           bool has_acceleration_z, double acceleration_z,
                           bool has_acceleration_including_gravity_x,
                           double acceleration_including_gravity_x,
                           bool has_acceleration_including_gravity_y,
                           double acceleration_including_gravity_y,
                           bool has_acceleration_including_gravity_z,
                           double acceleration_including_gravity_z,
                           bool has_rotation_rate_alpha,
                           double rotation_rate_alpha,
                           bool has_rotation_rate_beta,
                           double rotation_rate_beta,
                           bool has_rotation_rate_gamma,
                           double rotation_rate_gamma,
                           double interval);
  void SetMockDeviceOrientation(bool has_alpha, double alpha,
                                bool has_beta, double beta,
                                bool has_gamma, double gamma,
                                bool has_absolute, bool absolute);

  void SetMockScreenOrientation(const std::string& orientation);

  void DidChangeBatteryStatus(bool charging,
                              double chargingTime,
                              double dischargingTime,
                              double level);
  void ResetBatteryStatus();

  void DidAcquirePointerLock();
  void DidNotAcquirePointerLock();
  void DidLosePointerLock();
  void SetPointerLockWillFailSynchronously();
  void SetPointerLockWillRespondAsynchronously();

  
  

  
  void SetPopupBlockingEnabled(bool block_popups);

  void SetJavaScriptCanAccessClipboard(bool can_access);
  void SetXSSAuditorEnabled(bool enabled);
  void SetAllowUniversalAccessFromFileURLs(bool allow);
  void SetAllowFileAccessFromFileURLs(bool allow);
  void OverridePreference(const std::string key, v8::Handle<v8::Value> value);

  
  void SetAcceptLanguages(const std::string& accept_languages);

  
  void SetPluginsEnabled(bool enabled);

  
  

  
  
  
  void DumpEditingCallbacks();

  
  
  
  void DumpAsText();

  
  
  
  void DumpAsMarkup();

  
  
  
  void DumpAsTextWithPixelResults();

  
  
  void DumpChildFrameScrollPositions();

  
  
  
  void DumpChildFramesAsText();

  
  
  
  void DumpChildFramesAsMarkup();

  
  
  void DumpIconChanges();

  
  void SetAudioData(const gin::ArrayBufferView& view);

  
  
  
  void DumpFrameLoadCallbacks();

  
  
  
  void DumpPingLoaderCallbacks();

  
  
  
  void DumpUserGestureInFrameLoadCallbacks();

  void DumpTitleChanges();

  
  
  
  void DumpCreateView();

  void SetCanOpenWindows();

  
  
  
  void DumpResourceLoadCallbacks();

  
  
  
  void DumpResourceRequestCallbacks();

  
  
  
  void DumpResourceResponseMIMETypes();

  
  void SetImagesAllowed(bool allowed);
  void SetMediaAllowed(bool allowed);
  void SetScriptsAllowed(bool allowed);
  void SetStorageAllowed(bool allowed);
  void SetPluginsAllowed(bool allowed);
  void SetAllowDisplayOfInsecureContent(bool allowed);
  void SetAllowRunningOfInsecureContent(bool allowed);
  void DumpPermissionClientCallbacks();

  
  
  
  void DumpWindowStatusChanges();

  
  
  
  void DumpProgressFinishedCallback();

  
  
  void DumpSpellCheckCallbacks();

  
  
  void DumpBackForwardList();

  void DumpSelectionRect();

  
  void SetPrinting();

  
  void ClearPrinting();

  void SetShouldStayOnPageAfterHandlingBeforeUnload(bool value);

  
  void SetWillSendRequestClearHeader(const std::string& header);

  
  
  
  void DumpResourceRequestPriorities();

  
  void SetUseMockTheme(bool use);

  
  
  void WaitUntilExternalURLLoad();

  
  

  
  

  
  void ShowWebInspector(const std::string& str,
                        const std::string& frontend_url);
  void CloseWebInspector();

  
  bool IsChooserShown();

  
  void EvaluateInWebInspector(int call_id, const std::string& script);

  
  void ClearAllDatabases();
  
  void SetDatabaseQuota(int quota);

  
  void SetAlwaysAcceptCookies(bool accept);

  
  void SetWindowIsKey(bool value);

  
  std::string PathToLocalResource(const std::string& path);

  
  void SetBackingScaleFactor(double value, v8::Handle<v8::Function> callback);

  
  void SetColorProfile(const std::string& name,
                       v8::Handle<v8::Function> callback);

  
  
  void SetPOSIXLocale(const std::string& locale);

  
  void SetMIDIAccessorResult(bool result);
  void SetMIDISysexPermission(bool value);

  
  void GrantWebNotificationPermission(const GURL& origin,
                                      bool permission_granted);

  
  void ClearWebNotificationPermissions();

  
  bool SimulateWebNotificationClick(const std::string& value);

  
  void AddMockSpeechRecognitionResult(const std::string& transcript,
                                      double confidence);
  void SetMockSpeechRecognitionError(const std::string& error,
                                     const std::string& message);
  bool WasMockSpeechRecognitionAborted();

  
  
  void AddMockCredentialManagerResponse(const std::string& id,
                                        const std::string& name,
                                        const std::string& avatar,
                                        const std::string& password);

  
  
  void AddWebPageOverlay();
  void RemoveWebPageOverlay();

  void DisplayAsync();
  void DisplayAsyncThen(v8::Handle<v8::Function> callback);

  
  
  
  void CapturePixelsAsyncThen(v8::Handle<v8::Function> callback);
  
  
  
  
  void CopyImageAtAndCapturePixelsAsyncThen(
      int x, int y, const v8::Handle<v8::Function> callback);

  void SetMockPushClientSuccess(const std::string& endpoint,
                                const std::string& registration_id);
  void SetMockPushClientError(const std::string& message);

  void GetManifestThen(v8::Handle<v8::Function> callback);

  
  

  void GetManifestCallback(scoped_ptr<InvokeCallbackTask> task,
                           const blink::WebURLResponse& response,
                           const std::string& data);
  void CapturePixelsCallback(scoped_ptr<InvokeCallbackTask> task,
                             const SkBitmap& snapshot);

  void CheckResponseMimeType();
  void CompleteNotifyDone();

  void DidAcquirePointerLockInternal();
  void DidNotAcquirePointerLockInternal();
  void DidLosePointerLockInternal();

  
  
  
  void LocationChangeDone();

  bool test_is_running_;

  
  
  
  bool close_remaining_windows_;

  
  bool wait_until_done_;

  
  
  bool wait_until_external_url_load_;

  
  
  
  bool policy_delegate_enabled_;

  
  
  bool policy_delegate_is_permissive_;

  
  bool policy_delegate_should_notify_done_;

  WorkQueue work_queue_;

  
  std::string platform_name_;

  
  std::string tooltip_text_;

  
  
  
  
  bool disable_notify_done_;

  
  int web_history_item_count_;

  
  bool intercept_post_message_;

  
  
  bool dump_editting_callbacks_;

  
  bool generate_pixel_results_;

  
  
  bool dump_as_text_;

  
  
  bool dump_child_frames_as_text_;

  
  
  bool dump_as_markup_;

  
  
  
  bool dump_child_frames_as_markup_;

  
  
  bool dump_child_frame_scroll_positions_;

  
  bool dump_icon_changes_;

  
  bool dump_as_audio_;

  
  
  bool dump_frame_load_callbacks_;

  
  
  bool dump_ping_loader_callbacks_;

  
  
  bool dump_user_gesture_in_frame_load_callbacks_;

  
  bool dump_title_changes_;

  
  
  bool dump_create_view_;

  
  
  
  bool can_open_windows_;

  
  
  bool dump_resource_load_callbacks_;

  
  
  bool dump_resource_request_callbacks_;

  
  
  bool dump_resource_reqponse_mime_types_;

  
  bool dump_window_status_changes_;

  
  
  bool dump_progress_finished_callback_;

  
  
  bool dump_spell_check_callbacks_;

  
  
  bool dump_back_forward_list_;

  
  
  bool dump_selection_rect_;

  
  
  bool test_repaint_;

  
  
  bool sweep_horizontally_;

  
  bool is_printing_;

  
  bool midi_accessor_result_;

  bool should_stay_on_page_after_handling_before_unload_;

  bool should_dump_resource_priorities_;

  bool has_custom_text_output_;
  std::string custom_text_output_;

  std::set<std::string> http_headers_to_clear_;

  
  std::vector<unsigned char> audio_data_;

  
  WebTaskList task_list_;

  TestInterfaces* test_interfaces_;
  WebTestDelegate* delegate_;
  blink::WebView* web_view_;
  TestPageOverlay* page_overlay_;
  WebTestProxyBase* proxy_;

  
  blink::WebFrame* top_loading_frame_;

  
  scoped_ptr<WebPermissions> web_permissions_;

  scoped_ptr<NotificationPresenter> notification_presenter_;

  bool pointer_locked_;
  enum {
    PointerLockWillSucceed,
    PointerLockWillRespondAsync,
    PointerLockWillFailSync,
  } pointer_lock_planned_result_;
  bool use_mock_theme_;

  base::WeakPtrFactory<TestRunner> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(TestRunner);
};

}  

#endif  
