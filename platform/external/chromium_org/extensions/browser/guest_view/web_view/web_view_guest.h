// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_GUEST_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_GUEST_H_

#include <vector>

#include "base/observer_list.h"
#include "content/public/browser/javascript_dialog_manager.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/guest_view/guest_view.h"
#include "extensions/browser/guest_view/web_view/javascript_dialog_helper.h"
#include "extensions/browser/guest_view/web_view/web_view_find_helper.h"
#include "extensions/browser/guest_view/web_view/web_view_guest_delegate.h"
#include "extensions/browser/guest_view/web_view/web_view_permission_helper.h"
#include "extensions/browser/guest_view/web_view/web_view_permission_types.h"
#include "extensions/browser/script_executor.h"

namespace blink {
struct WebFindOptions;
}  

namespace extensions {

class WebViewInternalFindFunction;

class WebViewGuest : public GuestView<WebViewGuest>,
                     public content::NotificationObserver {
 public:
  static GuestViewBase* Create(content::BrowserContext* browser_context,
                               int guest_instance_id);

  
  
  
  
  
  
  
  static bool GetGuestPartitionConfigForSite(const GURL& site,
                                             std::string* partition_domain,
                                             std::string* partition_name,
                                             bool* in_memory);

  
  
  static int GetViewInstanceId(content::WebContents* contents);

  static const char Type[];

  
  void NavigateGuest(const std::string& src);

  
  
  
  
  void ShowContextMenu(
      int request_id,
      const WebViewGuestDelegate::MenuItemVector* items);

  
  void SetName(const std::string& name);

  
  void SetZoom(double zoom_factor);

  
  void SetAllowTransparency(bool allow);

  
  virtual const char* GetAPINamespace() const OVERRIDE;
  virtual int GetTaskPrefix() const OVERRIDE;
  virtual void CreateWebContents(
      const std::string& embedder_extension_id,
      int embedder_render_process_id,
      const GURL& embedder_site_url,
      const base::DictionaryValue& create_params,
      const WebContentsCreatedCallback& callback) OVERRIDE;
  virtual void DidAttachToEmbedder() OVERRIDE;
  virtual void DidInitialize() OVERRIDE;
  virtual void DidStopLoading() OVERRIDE;
  virtual void EmbedderDestroyed() OVERRIDE;
  virtual void GuestDestroyed() OVERRIDE;
  virtual void GuestReady() OVERRIDE;
  virtual void GuestSizeChangedDueToAutoSize(
      const gfx::Size& old_size,
      const gfx::Size& new_size) OVERRIDE;
  virtual bool IsAutoSizeSupported() const OVERRIDE;
  virtual bool IsDragAndDropEnabled() const OVERRIDE;
  virtual void WillAttachToEmbedder() OVERRIDE;
  virtual void WillDestroy() OVERRIDE;

  
  virtual bool AddMessageToConsole(content::WebContents* source,
                                   int32 level,
                                   const base::string16& message,
                                   int32 line_no,
                                   const base::string16& source_id) OVERRIDE;
  virtual void LoadProgressChanged(content::WebContents* source,
                                   double progress) OVERRIDE;
  virtual void CloseContents(content::WebContents* source) OVERRIDE;
  virtual void FindReply(content::WebContents* source,
                         int request_id,
                         int number_of_matches,
                         const gfx::Rect& selection_rect,
                         int active_match_ordinal,
                         bool final_update) OVERRIDE;
  virtual bool HandleContextMenu(
      const content::ContextMenuParams& params) OVERRIDE;
  virtual void HandleKeyboardEvent(
      content::WebContents* source,
      const content::NativeWebKeyboardEvent& event) OVERRIDE;
  virtual void RendererResponsive(content::WebContents* source) OVERRIDE;
  virtual void RendererUnresponsive(content::WebContents* source) OVERRIDE;
  virtual void RequestMediaAccessPermission(
      content::WebContents* source,
      const content::MediaStreamRequest& request,
      const content::MediaResponseCallback& callback) OVERRIDE;
  virtual bool CheckMediaAccessPermission(
      content::WebContents* source,
      const GURL& security_origin,
      content::MediaStreamType type) OVERRIDE;
  virtual void CanDownload(content::RenderViewHost* render_view_host,
                           const GURL& url,
                           const std::string& request_method,
                           const base::Callback<void(bool)>& callback) OVERRIDE;
  virtual content::JavaScriptDialogManager*
      GetJavaScriptDialogManager() OVERRIDE;
  virtual content::ColorChooser* OpenColorChooser(
      content::WebContents* web_contents,
      SkColor color,
      const std::vector<content::ColorSuggestion>& suggestions) OVERRIDE;
  virtual void AddNewContents(content::WebContents* source,
                              content::WebContents* new_contents,
                              WindowOpenDisposition disposition,
                              const gfx::Rect& initial_pos,
                              bool user_gesture,
                              bool* was_blocked) OVERRIDE;
  virtual content::WebContents* OpenURLFromTab(
      content::WebContents* source,
      const content::OpenURLParams& params) OVERRIDE;
  virtual void WebContentsCreated(content::WebContents* source_contents,
                                  int opener_render_frame_id,
                                  const base::string16& frame_name,
                                  const GURL& target_url,
                                  content::WebContents* new_contents) OVERRIDE;

  
  virtual content::WebContents* CreateNewGuestWindow(
      const content::WebContents::CreateParams& create_params) OVERRIDE;
  virtual void RequestPointerLockPermission(
      bool user_gesture,
      bool last_unlocked_by_target,
      const base::Callback<void(bool)>& callback) OVERRIDE;
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  double GetZoom();

  
  void Find(const base::string16& search_text,
            const blink::WebFindOptions& options,
            scoped_refptr<WebViewInternalFindFunction> find_function);

  
  void StopFinding(content::StopFindAction);

  
  
  void Go(int relative_index);

  
  void Reload();

  typedef base::Callback<void(bool ,
                              const std::string& )>
      PermissionResponseCallback;
  int RequestPermission(
      WebViewPermissionType permission_type,
      const base::DictionaryValue& request_info,
      const PermissionResponseCallback& callback,
      bool allowed_by_default);

  
  void RequestGeolocationPermission(int bridge_id,
                                    const GURL& requesting_frame,
                                    bool user_gesture,
                                    const base::Callback<void(bool)>& callback);
  void CancelGeolocationPermissionRequest(int bridge_id);

  
  
  
  
  
  
  
  
  void RequestFileSystemPermission(const GURL& url,
                                   bool allowed_by_default,
                                   const base::Callback<void(bool)>& callback);

  
  
  void SetUserAgentOverride(const std::string& user_agent_override);

  
  void Stop();

  
  void Terminate();

  
  
  
  
  bool ClearData(const base::Time remove_since,
                 uint32 removal_mask,
                 const base::Closure& callback);

  ScriptExecutor* script_executor() { return script_executor_.get(); }

 private:
  friend class WebViewPermissionHelper;
  WebViewGuest(content::BrowserContext* browser_context,
               int guest_instance_id);

  virtual ~WebViewGuest();

  void AttachWebViewHelpers(content::WebContents* contents);

  void OnWebViewNewWindowResponse(int new_window_instance_id,
                                  bool allow,
                                  const std::string& user_input);

  
  virtual void DidCommitProvisionalLoadForFrame(
      content::RenderFrameHost* render_frame_host,
      const GURL& url,
      ui::PageTransition transition_type) OVERRIDE;
  virtual void DidFailProvisionalLoad(
      content::RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      int error_code,
      const base::string16& error_description) OVERRIDE;
  virtual void DidStartProvisionalLoadForFrame(
      content::RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      bool is_error_page,
      bool is_iframe_srcdoc) OVERRIDE;
  virtual void DocumentLoadedInFrame(
      content::RenderFrameHost* render_frame_host) OVERRIDE;
  virtual bool OnMessageReceived(
      const IPC::Message& message,
      content::RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void RenderProcessGone(base::TerminationStatus status) OVERRIDE;
  virtual void UserAgentOverrideSet(const std::string& user_agent) OVERRIDE;

  
  void ReportFrameNameChange(const std::string& name);

  
  void LoadHandlerCalled();

  
  void LoadRedirect(const GURL& old_url,
                    const GURL& new_url,
                    bool is_top_level);

  void PushWebViewStateToIOThread();
  static void RemoveWebViewStateFromIOThread(
      content::WebContents* web_contents);

  void LoadURLWithParams(const GURL& url,
                         const content::Referrer& referrer,
                         ui::PageTransition transition_type,
                         content::WebContents* web_contents);

  void RequestNewWindowPermission(
      WindowOpenDisposition disposition,
      const gfx::Rect& initial_bounds,
      bool user_gesture,
      content::WebContents* new_contents);

  
  
  void DestroyUnattachedWindows();

  
  GURL ResolveURL(const std::string& src);

  
  
  void LoadAbort(bool is_top_level,
                 const GURL& url,
                 const std::string& error_type);

  void OnFrameNameChanged(bool is_top_level, const std::string& name);

  
  void CreateNewGuestWebViewWindow(const content::OpenURLParams& params);

  void NewGuestWebViewCallback(const content::OpenURLParams& params,
                               content::WebContents* guest_web_contents);

  bool HandleKeyboardShortcuts(const content::NativeWebKeyboardEvent& event);

  void SetUpAutoSize();

  
  WebViewFindHelper find_helper_;

  ObserverList<ScriptExecutionObserver> script_observers_;
  scoped_ptr<ScriptExecutor> script_executor_;

  content::NotificationRegistrar notification_registrar_;

  
  bool is_overriding_user_agent_;

  
  std::string name_;

  
  bool guest_opaque_;

  
  JavaScriptDialogHelper javascript_dialog_helper_;

  
  scoped_ptr<WebViewPermissionHelper> web_view_permission_helper_;

  scoped_ptr<WebViewGuestDelegate> web_view_guest_delegate_;

  
  
  struct NewWindowInfo {
    GURL url;
    std::string name;
    bool changed;
    NewWindowInfo(const GURL& url, const std::string& name) :
        url(url),
        name(name),
        changed(false) {}
  };

  typedef std::map<WebViewGuest*, NewWindowInfo> PendingWindowMap;
  PendingWindowMap pending_new_windows_;

  DISALLOW_COPY_AND_ASSIGN(WebViewGuest);
};

}  

#endif  
