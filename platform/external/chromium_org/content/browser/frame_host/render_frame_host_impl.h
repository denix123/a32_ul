// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_HOST_IMPL_H_
#define CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_HOST_IMPL_H_

#include <map>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "content/browser/accessibility/browser_accessibility_manager.h"
#include "content/common/accessibility_mode_enums.h"
#include "content/common/content_export.h"
#include "content/common/mojo/service_registry_impl.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/common/javascript_message_type.h"
#include "net/http/http_response_headers.h"
#include "third_party/WebKit/public/platform/WebNotificationPermission.h"
#include "third_party/WebKit/public/web/WebTextDirection.h"
#include "ui/accessibility/ax_node_data.h"
#include "ui/base/page_transition_types.h"

class GURL;
struct AccessibilityHostMsg_EventParams;
struct AccessibilityHostMsg_LocationChangeParams;
struct FrameHostMsg_DidFailProvisionalLoadWithError_Params;
struct FrameHostMsg_OpenURL_Params;
struct FrameHostMsg_BeginNavigation_Params;
struct FrameMsg_Navigate_Params;
#if defined(OS_MACOSX) || defined(OS_ANDROID)
struct FrameHostMsg_ShowPopup_Params;
#endif

namespace base {
class FilePath;
class ListValue;
}

namespace content {

class CrossProcessFrameConnector;
class CrossSiteTransferringRequest;
class FrameTree;
class FrameTreeNode;
class RenderFrameHostDelegate;
class RenderFrameProxyHost;
class RenderProcessHost;
class RenderViewHostImpl;
class RenderWidgetHostImpl;
struct ContextMenuParams;
struct GlobalRequestID;
struct Referrer;
struct ShowDesktopNotificationHostMsgParams;
struct TransitionLayerData;

class CONTENT_EXPORT RenderFrameHostImpl
    : public RenderFrameHost,
      public BrowserAccessibilityDelegate {
 public:
  
  
  enum RenderFrameHostImplState {
    
    
    STATE_DEFAULT = 0,
    
    
    
    
    STATE_PENDING_SWAP_OUT,
    
    
    
    STATE_SWAPPED_OUT,
  };
  
  
  static bool IsRFHStateActive(RenderFrameHostImplState rfh_state);

  
  
  
  static const int kMaxAccessibilityResets = 5;

  static RenderFrameHostImpl* FromID(int process_id, int routing_id);

  virtual ~RenderFrameHostImpl();

  
  virtual int GetRoutingID() OVERRIDE;
  virtual SiteInstance* GetSiteInstance() OVERRIDE;
  virtual RenderProcessHost* GetProcess() OVERRIDE;
  virtual RenderFrameHost* GetParent() OVERRIDE;
  virtual const std::string& GetFrameName() OVERRIDE;
  virtual bool IsCrossProcessSubframe() OVERRIDE;
  virtual GURL GetLastCommittedURL() OVERRIDE;
  virtual gfx::NativeView GetNativeView() OVERRIDE;
  virtual void ExecuteJavaScript(
      const base::string16& javascript) OVERRIDE;
  virtual void ExecuteJavaScript(
      const base::string16& javascript,
      const JavaScriptResultCallback& callback) OVERRIDE;
  virtual void ExecuteJavaScriptForTests(
      const base::string16& javascript) OVERRIDE;
  virtual RenderViewHost* GetRenderViewHost() OVERRIDE;
  virtual ServiceRegistry* GetServiceRegistry() OVERRIDE;

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  virtual void AccessibilitySetFocus(int acc_obj_id) OVERRIDE;
  virtual void AccessibilityDoDefaultAction(int acc_obj_id) OVERRIDE;
  virtual void AccessibilityShowMenu(const gfx::Point& global_point) OVERRIDE;
  virtual void AccessibilityScrollToMakeVisible(
      int acc_obj_id, const gfx::Rect& subfocus) OVERRIDE;
  virtual void AccessibilityScrollToPoint(
      int acc_obj_id, const gfx::Point& point) OVERRIDE;
  virtual void AccessibilitySetTextSelection(
      int acc_obj_id, int start_offset, int end_offset) OVERRIDE;
  virtual bool AccessibilityViewHasFocus() const OVERRIDE;
  virtual gfx::Rect AccessibilityGetViewBounds() const OVERRIDE;
  virtual gfx::Point AccessibilityOriginInScreen(const gfx::Rect& bounds)
      const OVERRIDE;
  virtual void AccessibilityHitTest(const gfx::Point& point) OVERRIDE;
  virtual void AccessibilityFatalError() OVERRIDE;
  virtual gfx::AcceleratedWidget AccessibilityGetAcceleratedWidget() OVERRIDE;
  virtual gfx::NativeViewAccessible AccessibilityGetNativeViewAccessible()
      OVERRIDE;
  virtual BrowserAccessibilityManager* AccessibilityGetChildFrame(
      int accessibility_node_id) OVERRIDE;
  virtual BrowserAccessibility* AccessibilityGetParentFrame() OVERRIDE;

  
  
  bool CreateRenderFrame(int parent_routing_id);

  
  
  bool IsRenderFrameLive();

  
  
  
  void set_render_frame_created(bool created) {
    render_frame_created_ = created;
  }

  
  
  void Init();

  int routing_id() const { return routing_id_; }
  void OnCreateChildFrame(int new_routing_id,
                          const std::string& frame_name);

  RenderViewHostImpl* render_view_host() { return render_view_host_; }
  RenderFrameHostDelegate* delegate() { return delegate_; }
  FrameTreeNode* frame_tree_node() { return frame_tree_node_; }
  
  
  RenderWidgetHostImpl* GetRenderWidgetHost();

  
  
  
  
  
  
  
  void set_cross_process_frame_connector(
      CrossProcessFrameConnector* cross_process_frame_connector) {
    cross_process_frame_connector_ = cross_process_frame_connector;
  }

  void set_render_frame_proxy_host(RenderFrameProxyHost* proxy) {
    render_frame_proxy_host_ = proxy;
  }

  
  
  
  int GetEnabledBindings();

  
  
  
  
  void OnCrossSiteResponse(
      const GlobalRequestID& global_request_id,
      scoped_ptr<CrossSiteTransferringRequest> cross_site_transferring_request,
      const std::vector<GURL>& transfer_url_chain,
      const Referrer& referrer,
      ui::PageTransition page_transition,
      bool should_replace_current_entry);

  
  
  void OnDeferredAfterResponseStarted(
      const GlobalRequestID& global_request_id,
      const TransitionLayerData& transition_data);

  
  
  
  
  
  
  void SwapOut(RenderFrameProxyHost* proxy);

  void OnSwappedOut(bool timed_out);
  bool is_swapped_out() { return is_swapped_out_; }
  void set_swapped_out(bool is_swapped_out) {
    is_swapped_out_ = is_swapped_out;
  }

  
  
  void SetPendingShutdown(const base::Closure& on_swap_out);

  
  
  
  
  
  
  
  void Navigate(const FrameMsg_Navigate_Params& params);

  
  void NavigateToURL(const GURL& url);

  
  void Stop();

  
  
  
  bool are_navigations_suspended() const { return navigations_suspended_; }

  
  
  
  
  
  
  
  
  
  
  
  void SetNavigationsSuspended(bool suspend,
                               const base::TimeTicks& proceed_time);

  
  
  
  void CancelSuspendedNavigations();

  
  
  
  void DispatchBeforeUnload(bool for_cross_site_transition);

  
  
  void DisownOpener();

  
  
  void ExtendSelectionAndDelete(size_t before, size_t after);

  
  
  void JavaScriptDialogClosed(IPC::Message* reply_msg,
                              bool success,
                              const base::string16& user_input,
                              bool dialog_was_suppressed);

  
  void NotificationClosed(int notification_id);

  
  
  void ClearPendingTransitionRequestData();

  
  void SetAccessibilityMode(AccessibilityMode AccessibilityMode);

  
  
  
  
  void SetAccessibilityCallbackForTesting(
      const base::Callback<void(ui::AXEvent, int)>& callback);

  
  
  
  const ui::AXTree* GetAXTreeForTesting();

  
  BrowserAccessibilityManager* browser_accessibility_manager() const {
    return browser_accessibility_manager_.get();
  }

  
  
  
  BrowserAccessibilityManager* GetOrCreateBrowserAccessibilityManager();

  void set_disallow_browser_accessibility_manager_for_testing(bool flag) {
    disallow_browser_accessibility_manager_for_testing_ = flag;
  }

#if defined(OS_WIN)
  void SetParentNativeViewAccessible(
      gfx::NativeViewAccessible accessible_parent);
  gfx::NativeViewAccessible GetParentNativeViewAccessible() const;
#elif defined(OS_MACOSX)
  
  void DidSelectPopupMenuItem(int selected_index);
  void DidCancelPopupMenu();
#elif defined(OS_ANDROID)
  void DidSelectPopupMenuItems(const std::vector<int>& selected_indices);
  void DidCancelPopupMenu();
#endif

 protected:
  friend class RenderFrameHostFactory;

  
  
  
  RenderFrameHostImpl(RenderViewHostImpl* render_view_host,
                      RenderFrameHostDelegate* delegate,
                      FrameTree* frame_tree,
                      FrameTreeNode* frame_tree_node,
                      int routing_id,
                      bool is_swapped_out);

 private:
  friend class TestRenderFrameHost;
  friend class TestRenderViewHost;

  FRIEND_TEST_ALL_PREFIXES(SitePerProcessBrowserTest, CrashSubframe);

  
  void OnAddMessageToConsole(int32 level,
                             const base::string16& message,
                             int32 line_no,
                             const base::string16& source_id);
  void OnDetach();
  void OnFrameFocused();
  void OnOpenURL(const FrameHostMsg_OpenURL_Params& params);
  void OnDocumentOnLoadCompleted();
  void OnDidStartProvisionalLoadForFrame(const GURL& url,
                                         bool is_transition_navigation);
  void OnDidFailProvisionalLoadWithError(
      const FrameHostMsg_DidFailProvisionalLoadWithError_Params& params);
  void OnDidFailLoadWithError(
      const GURL& url,
      int error_code,
      const base::string16& error_description);
  void OnDidCommitProvisionalLoad(const IPC::Message& msg);
  void OnBeforeUnloadACK(
      bool proceed,
      const base::TimeTicks& renderer_before_unload_start_time,
      const base::TimeTicks& renderer_before_unload_end_time);
  void OnSwapOutACK();
  void OnContextMenu(const ContextMenuParams& params);
  void OnJavaScriptExecuteResponse(int id, const base::ListValue& result);
  void OnRunJavaScriptMessage(const base::string16& message,
                              const base::string16& default_prompt,
                              const GURL& frame_url,
                              JavaScriptMessageType type,
                              IPC::Message* reply_msg);
  void OnRunBeforeUnloadConfirm(const GURL& frame_url,
                                const base::string16& message,
                                bool is_reload,
                                IPC::Message* reply_msg);
  void OnRequestPlatformNotificationPermission(const GURL& origin,
                                               int request_id);
  void OnShowDesktopNotification(
      int notification_id,
      const ShowDesktopNotificationHostMsgParams& params);
  void OnCancelDesktopNotification(int notification_id);
  void OnTextSurroundingSelectionResponse(const base::string16& content,
                                          size_t start_offset,
                                          size_t end_offset);
  void OnDidAccessInitialDocument();
  void OnDidDisownOpener();
  void OnDidAssignPageId(int32 page_id);
  void OnUpdateTitle(int32 page_id,
                     const base::string16& title,
                     blink::WebTextDirection title_direction);
  void OnUpdateEncoding(const std::string& encoding);
  void OnBeginNavigation(
      const FrameHostMsg_BeginNavigation_Params& params);
  void OnAccessibilityEvents(
      const std::vector<AccessibilityHostMsg_EventParams>& params,
      int reset_token);
  void OnAccessibilityLocationChanges(
      const std::vector<AccessibilityHostMsg_LocationChangeParams>& params);

#if defined(OS_MACOSX) || defined(OS_ANDROID)
  void OnShowPopup(const FrameHostMsg_ShowPopup_Params& params);
  void OnHidePopup();
#endif

  
  
  
  bool CanCommitURL(const GURL& url);

  void PlatformNotificationPermissionRequestDone(
      int request_id, blink::WebNotificationPermission permission);

  
  
  
  void UpdateCrossProcessIframeAccessibility(
      const std::map<int32, int> node_to_frame_routing_id_map);

  
  
  
  void UpdateGuestFrameAccessibility(
      const std::map<int32, int> node_to_browser_plugin_instance_id_map);

  
  
  
  
  
  
  RenderViewHostImpl* render_view_host_;

  RenderFrameHostDelegate* delegate_;

  
  
  
  
  
  
  
  
  
  
  CrossProcessFrameConnector* cross_process_frame_connector_;

  
  
  
  
  RenderFrameProxyHost* render_frame_proxy_host_;

  
  
  
  FrameTree* frame_tree_;

  
  FrameTreeNode* frame_tree_node_;

  
  
  std::map<int, JavaScriptResultCallback> javascript_callbacks_;

  
  std::map<int, base::Closure> cancel_notification_callbacks_;

  int routing_id_;
  bool is_swapped_out_;

  
  
  
  bool render_frame_created_;

  
  
  
  
  bool navigations_suspended_;

  
  
  
  
  
  scoped_ptr<FrameMsg_Navigate_Params> suspended_nav_params_;

  
  base::TimeTicks send_before_unload_start_time_;

  ServiceRegistryImpl service_registry_;

  
  scoped_ptr<BrowserAccessibilityManager> browser_accessibility_manager_;

  
  
  
  int accessibility_reset_token_;

  
  
  int accessibility_reset_count_;

  
  base::Callback<void(ui::AXEvent, int)> accessibility_testing_callback_;
  
  scoped_ptr<ui::AXTree> ax_tree_for_testing_;
  
  bool disallow_browser_accessibility_manager_for_testing_;

  
  base::WeakPtrFactory<RenderFrameHostImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(RenderFrameHostImpl);
};

}  

#endif  
