// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_WEB_CONTENTS_OBSERVER_H_
#define CONTENT_PUBLIC_BROWSER_WEB_CONTENTS_OBSERVER_H_

#include "base/process/kill.h"
#include "base/process/process_handle.h"
#include "content/common/content_export.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/common/frame_navigate_params.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/base/page_transition_types.h"
#include "ui/base/window_open_disposition.h"

namespace content {

class NavigationEntry;
class RenderFrameHost;
class RenderViewHost;
class WebContents;
class WebContentsImpl;
struct AXEventNotificationDetails;
struct FaviconURL;
struct FrameNavigateParams;
struct LoadCommittedDetails;
struct LoadFromMemoryCacheDetails;
struct Referrer;
struct ResourceRedirectDetails;
struct ResourceRequestDetails;

class CONTENT_EXPORT WebContentsObserver : public IPC::Listener,
                                           public IPC::Sender {
 public:
  
  virtual void RenderFrameCreated(RenderFrameHost* render_frame_host) {}

  
  
  virtual void RenderFrameDeleted(RenderFrameHost* render_frame_host) {}

  
  
  virtual void RenderViewCreated(RenderViewHost* render_view_host) {}

  
  virtual void RenderFrameForInterstitialPageCreated(
      RenderFrameHost* render_frame_host) {}

  
  
  virtual void RenderViewReady() {}

  
  
  
  
  virtual void RenderViewDeleted(RenderViewHost* render_view_host) {}

  
  
  
  
  
  
  
  virtual void RenderProcessGone(base::TerminationStatus status) {}

  
  
  
  virtual void RenderViewHostChanged(RenderViewHost* old_host,
                                     RenderViewHost* new_host) {}

  
  
  
  
  
  
  
  
  
  virtual void RenderFrameHostChanged(RenderFrameHost* old_host,
                                      RenderFrameHost* new_host) {}

  
  
  virtual void AboutToNavigateRenderView(
      RenderViewHost* render_view_host) {}

  
  
  
  
  
  virtual void DidStartNavigationToPendingEntry(
      const GURL& url,
      NavigationController::ReloadType reload_type) {}

  
  
  
  
  
  
  
  
  
  virtual void DidStartProvisionalLoadForFrame(
      RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      bool is_error_page,
      bool is_iframe_srcdoc) {}

  
  
  
  
  
  
  virtual void DidCommitProvisionalLoadForFrame(
      RenderFrameHost* render_frame_host,
      const GURL& url,
      ui::PageTransition transition_type) {}

  
  virtual void DidFailProvisionalLoad(
      RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      int error_code,
      const base::string16& error_description) {}

  
  
  virtual void DidNavigateMainFrame(
      const LoadCommittedDetails& details,
      const FrameNavigateParams& params) {}

  
  
  virtual void DidNavigateAnyFrame(
      const LoadCommittedDetails& details,
      const FrameNavigateParams& params) {}

  
  
  virtual void DocumentAvailableInMainFrame() {}

  
  
  virtual void DocumentOnLoadCompletedInMainFrame() {}

  
  
  
  virtual void DocumentLoadedInFrame(RenderFrameHost* render_frame_host) {}

  
  
  
  
  
  
  virtual void DidFinishLoad(RenderFrameHost* render_frame_host,
                             const GURL& validated_url) {}

  
  
  virtual void DidFailLoad(RenderFrameHost* render_frame_host,
                           const GURL& validated_url,
                           int error_code,
                           const base::string16& error_description) {}

  
  virtual void DidLoadResourceFromMemoryCache(
      const LoadFromMemoryCacheDetails& details) {}

  
  
  virtual void DidGetResourceResponseStart(
      const ResourceRequestDetails& details) {}

  
  
  virtual void DidGetRedirectForResourceRequest(
      RenderViewHost* render_view_host,
      const ResourceRedirectDetails& details) {}

  
  
  
  
  virtual void NavigationEntryCommitted(
      const LoadCommittedDetails& load_details) {}

  
  
  
  
  virtual void DidOpenRequestedURL(WebContents* new_contents,
                                   const GURL& url,
                                   const Referrer& referrer,
                                   WindowOpenDisposition disposition,
                                   ui::PageTransition transition,
                                   int64 source_frame_id) {}

  virtual void FrameDetached(RenderFrameHost* render_frame_host) {}

  
  
  virtual void DidFirstVisuallyNonEmptyPaint() {}

  
  
  virtual void DidStartLoading(RenderViewHost* render_view_host) {}
  virtual void DidStopLoading(RenderViewHost* render_view_host) {}

  
  
  
  virtual void NavigationStopped() {}

  
  virtual void DidGetUserGesture() {}

  
  
  virtual void DidGetIgnoredUIEvent() {}

  
  virtual void WasShown() {}
  virtual void WasHidden() {}

  
  
  
  virtual void TitleWasSet(NavigationEntry* entry, bool explicit_set) {}

  virtual void AppCacheAccessed(const GURL& manifest_url,
                                bool blocked_by_policy) {}

  
  
  
  
  
  virtual void PluginCrashed(const base::FilePath& plugin_path,
                             base::ProcessId plugin_pid) {}

  
  
  
  
  
  
  virtual void PluginHungStatusChanged(int plugin_child_id,
                                       const base::FilePath& plugin_path,
                                       bool is_hung) {}

  
  virtual void DidCloneToNewWebContents(WebContents* old_web_contents,
                                        WebContents* new_web_contents) {}

  
  
  
  virtual void WebContentsDestroyed() {}

  
  virtual void UserAgentOverrideSet(const std::string& user_agent) {}

  
  virtual void DidUpdateFaviconURL(const std::vector<FaviconURL>& candidates) {}

  
  
  virtual void DidShowFullscreenWidget(int routing_id) {}
  virtual void DidDestroyFullscreenWidget(int routing_id) {}

  
  virtual void DidToggleFullscreenModeForTab(bool entered_fullscreen) {}

  
  virtual void DidAttachInterstitialPage() {}
  virtual void DidDetachInterstitialPage() {}

  
  virtual void BeforeFormRepostWarningShow() {}

  
  virtual void BeforeUnloadFired(const base::TimeTicks& proceed_time) {}

  
  virtual void BeforeUnloadDialogCancelled() {}

  
  virtual void AccessibilityEventReceived(
      const std::vector<AXEventNotificationDetails>& details) {}

  
  virtual void DidChangeThemeColor(SkColor theme_color) {}

  
  virtual bool OnMessageReceived(const IPC::Message& message,
                                 RenderFrameHost* render_frame_host);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual bool Send(IPC::Message* message) OVERRIDE;
  int routing_id() const;

  WebContents* web_contents() const;

 protected:
  
  
  explicit WebContentsObserver(WebContents* web_contents);

  
  
  
  WebContentsObserver();

  virtual ~WebContentsObserver();

  
  void Observe(WebContents* web_contents);

 private:
  friend class WebContentsImpl;

  void ResetWebContents();

  WebContentsImpl* web_contents_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsObserver);
};

}  

#endif  
