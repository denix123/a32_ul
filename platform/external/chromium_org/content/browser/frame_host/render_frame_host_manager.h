// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_HOST_MANAGER_H_
#define CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_HOST_MANAGER_H_

#include "base/basictypes.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/renderer_host/render_view_host_delegate.h"
#include "content/browser/site_instance_impl.h"
#include "content/common/content_export.h"
#include "content/public/browser/global_request_id.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/common/referrer.h"
#include "ui/base/page_transition_types.h"

struct FrameHostMsg_BeginNavigation_Params;
struct FrameMsg_Navigate_Params;

namespace content {
class BrowserContext;
class CrossProcessFrameConnector;
class CrossSiteTransferringRequest;
class InterstitialPageImpl;
class FrameTreeNode;
class NavigationControllerImpl;
class NavigationEntry;
class NavigationEntryImpl;
class NavigationRequest;
class RenderFrameHost;
class RenderFrameHostDelegate;
class RenderFrameHost;
class RenderFrameHostImpl;
class RenderFrameHostManagerTest;
class RenderFrameProxyHost;
class RenderViewHost;
class RenderViewHostImpl;
class RenderWidgetHostDelegate;
class RenderWidgetHostView;
class TestWebContents;
class WebUIImpl;
struct NavigationBeforeCommitInfo;

class CONTENT_EXPORT RenderFrameHostManager : public NotificationObserver {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  class CONTENT_EXPORT Delegate {
   public:
    
    
    
    
    
    
    
    virtual bool CreateRenderViewForRenderManager(
        RenderViewHost* render_view_host,
        int opener_route_id,
        int proxy_routing_id,
        bool for_main_frame_navigation) = 0;
    virtual bool CreateRenderFrameForRenderManager(
        RenderFrameHost* render_frame_host,
        int parent_routing_id) = 0;
    virtual void BeforeUnloadFiredFromRenderManager(
        bool proceed, const base::TimeTicks& proceed_time,
        bool* proceed_to_fire_unload) = 0;
    virtual void RenderProcessGoneFromRenderManager(
        RenderViewHost* render_view_host) = 0;
    virtual void UpdateRenderViewSizeForRenderManager() = 0;
    virtual void CancelModalDialogsForRenderManager() = 0;
    virtual void NotifySwappedFromRenderManager(RenderFrameHost* old_host,
                                                RenderFrameHost* new_host,
                                                bool is_main_frame) = 0;
    virtual NavigationControllerImpl&
        GetControllerForRenderManager() = 0;

    
    
    
    
    virtual int CreateOpenerRenderViewsForRenderManager(
        SiteInstance* instance) = 0;

    
    
    
    virtual WebUIImpl* CreateWebUIForRenderManager(const GURL& url) = 0;

    
    
    virtual NavigationEntry*
        GetLastCommittedNavigationEntryForRenderManager() = 0;

    
    
    
    virtual bool FocusLocationBarByDefault() = 0;

    
    virtual void SetFocusToLocationBar(bool select_all) = 0;

    
    virtual void CreateViewAndSetSizeForRVH(RenderViewHost* rvh) = 0;

    
    
    virtual bool IsHidden() = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  
  static bool ClearRFHsPendingShutdown(FrameTreeNode* node);

  
  
  
  
  
  
  RenderFrameHostManager(
      FrameTreeNode* frame_tree_node,
      RenderFrameHostDelegate* render_frame_delegate,
      RenderViewHostDelegate* render_view_delegate,
      RenderWidgetHostDelegate* render_widget_delegate,
      Delegate* delegate);
  virtual ~RenderFrameHostManager();

  
  void Init(BrowserContext* browser_context,
            SiteInstance* site_instance,
            int view_routing_id,
            int frame_routing_id);

  
  
  
  
  
  RenderFrameHostImpl* current_frame_host() const {
    return render_frame_host_.get();
  }

  
  RenderViewHostImpl* current_host() const;

  
  
  RenderWidgetHostView* GetRenderWidgetHostView() const;

  RenderFrameProxyHost* GetProxyToParent();

  
  RenderFrameHostImpl* pending_frame_host() const {
    return pending_render_frame_host_.get();
  }

  
  RenderViewHostImpl* pending_render_view_host() const;

  
  WebUIImpl* web_ui() const { return web_ui_.get(); }

  
  WebUIImpl* pending_web_ui() const {
    return pending_web_ui_.get() ? pending_web_ui_.get() :
                                   pending_and_current_web_ui_.get();
  }

  
  
  void SetPendingWebUI(const NavigationEntryImpl& entry);

  
  
  
  
  RenderFrameHostImpl* Navigate(const NavigationEntryImpl& entry);

  
  
  void Stop();

  
  
  
  void SetIsLoading(bool is_loading);

  
  
  
  bool ShouldCloseTabOnUnresponsiveRenderer();

  
  
  
  
  
  void OnBeforeUnloadACK(bool for_cross_site_transition,
                         bool proceed,
                         const base::TimeTicks& proceed_time);

  
  
  
  
  
  void OnCrossSiteResponse(
      RenderFrameHostImpl* pending_render_frame_host,
      const GlobalRequestID& global_request_id,
      scoped_ptr<CrossSiteTransferringRequest> cross_site_transferring_request,
      const std::vector<GURL>& transfer_url_chain,
      const Referrer& referrer,
      ui::PageTransition page_transition,
      bool should_replace_current_entry);

  
  
  
  void OnDeferredAfterResponseStarted(
      const GlobalRequestID& global_request_id,
      RenderFrameHostImpl* pending_render_frame_host);

  
  void ResumeResponseDeferredAtStart();

  
  void DidNavigateFrame(RenderFrameHostImpl* render_frame_host);

  
  void DidDisownOpener(RenderFrameHost* render_frame_host);

  
  
  
  int CreateRenderFrame(SiteInstance* instance,
                        int opener_route_id,
                        bool swapped_out,
                        bool for_main_frame_navigation,
                        bool hidden);

  
  
  int CreateRenderFrameProxy(SiteInstance* instance);

  
  
  
  
  void set_interstitial_page(InterstitialPageImpl* interstitial_page) {
    DCHECK(!interstitial_page_ && interstitial_page);
    interstitial_page_ = interstitial_page;
  }

  
  void remove_interstitial_page() {
    DCHECK(interstitial_page_);
    interstitial_page_ = NULL;
  }

  
  
  InterstitialPageImpl* interstitial_page() const { return interstitial_page_; }

  
  virtual void Observe(int type,
                       const NotificationSource& source,
                       const NotificationDetails& details) OVERRIDE;

  
  
  bool IsRVHOnSwappedOutList(RenderViewHostImpl* rvh) const;
  bool IsOnSwappedOutList(RenderFrameHostImpl* rfh) const;

  
  
  
  RenderViewHostImpl* GetSwappedOutRenderViewHost(SiteInstance* instance) const;
  RenderFrameProxyHost* GetRenderFrameProxyHost(
      SiteInstance* instance) const;

  
  void ClearPendingShutdownRFHForSiteInstance(int32 site_instance_id,
                                              RenderFrameHostImpl* rfh);

  
  
  void ResetProxyHosts();

  
  
  
  int GetRoutingIdForSiteInstance(SiteInstance* site_instance);

  
  
  
  bool RequestNavigation(const NavigationEntryImpl& entry,
                         const FrameMsg_Navigate_Params& navigate_params);

  
  
  
  
  
  void OnBeginNavigation(const FrameHostMsg_BeginNavigation_Params& params);

  
  
  void CommitNavigation(const NavigationBeforeCommitInfo& info);

 private:
  friend class RenderFrameHostManagerTest;
  friend class TestWebContents;

  FRIEND_TEST_ALL_PREFIXES(CrossProcessFrameTreeBrowserTest,
                           CreateCrossProcessSubframeProxies);

  
  
  NavigationRequest* navigation_request_for_testing() const {
    return navigation_request_.get(); }

  
  
  static bool ClearProxiesInSiteInstance(int32 site_instance_id,
                                         FrameTreeNode* node);

  
  
  
  bool ShouldTransitionCrossSite();

  
  
  
  
  
  
  
  
  
  
  
  
  
  bool ShouldSwapBrowsingInstancesForNavigation(
      const GURL& current_effective_url,
      bool current_is_view_source_mode,
      SiteInstance* new_site_instance,
      const GURL& new_effective_url,
      bool new_is_view_source_mode) const;

  
  
  bool ShouldReuseWebUI(
      const NavigationEntry* current_entry,
      const NavigationEntryImpl* new_entry) const;

  
  SiteInstance* GetSiteInstanceForNavigation(
      const GURL& dest_url,
      SiteInstance* dest_instance,
      ui::PageTransition dest_transition,
      bool dest_is_restore,
      bool dest_is_view_source_mode);

  
  
  
  
  
  SiteInstance* GetSiteInstanceForURL(
      const GURL& dest_url,
      SiteInstance* dest_instance,
      ui::PageTransition dest_transition,
      bool dest_is_restore,
      bool dest_is_view_source_mode,
      SiteInstance* current_instance,
      bool force_browsing_instance_swap);

  
  
  void CreateRenderFrameHostForNewSiteInstance(
      SiteInstance* old_instance,
      SiteInstance* new_instance,
      bool is_main_frame);

  
  scoped_ptr<RenderFrameHostImpl> CreateRenderFrameHost(SiteInstance* instance,
                                                        int view_routing_id,
                                                        int frame_routing_id,
                                                        bool swapped_out,
                                                        bool hidden);

  
  
  
  
  
  
  
  bool InitRenderView(RenderViewHostImpl* render_view_host,
                      int opener_route_id,
                      int proxy_routing_id,
                      bool for_main_frame_navigation);

  
  
  bool InitRenderFrame(RenderFrameHostImpl* render_frame_host);

  
  
  
  void CommitPending();

  
  
  void SwapOutOldPage(RenderFrameHostImpl* old_render_frame_host);

  
  
  
  void ShutdownRenderFrameProxyHostsInSiteInstance(int32 site_instance_id);

  
  void CancelPending();

  
  
  scoped_ptr<RenderFrameHostImpl> SetRenderFrameHost(
      scoped_ptr<RenderFrameHostImpl> render_frame_host);

  RenderFrameHostImpl* UpdateStateForNavigate(
      const NavigationEntryImpl& entry);

  
  
  void RendererProcessClosing(RenderProcessHost* render_process_host);

  
  
  void DeleteRenderFrameProxyHost(SiteInstance* instance);

  
  FrameTreeNode* frame_tree_node_;

  
  Delegate* delegate_;

  
  
  
  bool cross_navigation_pending_;

  
  
  RenderFrameHostDelegate* render_frame_delegate_;
  RenderViewHostDelegate* render_view_delegate_;
  RenderWidgetHostDelegate* render_widget_delegate_;

  
  
  
  
  
  scoped_ptr<RenderFrameHostImpl> render_frame_host_;
  scoped_ptr<WebUIImpl> web_ui_;

  
  
  
  
  
  
  
  
  
  
  scoped_ptr<RenderFrameHostImpl> pending_render_frame_host_;

  
  
  
  scoped_ptr<CrossSiteTransferringRequest> cross_site_transferring_request_;

  
  
  scoped_ptr<GlobalRequestID> response_started_id_;

  
  
  
  
  scoped_ptr<WebUIImpl> pending_web_ui_;
  base::WeakPtr<WebUIImpl> pending_and_current_web_ui_;

  
  typedef base::hash_map<int32, RenderFrameProxyHost*> RenderFrameProxyHostMap;
  RenderFrameProxyHostMap proxy_hosts_;

  
  typedef base::hash_map<int32, linked_ptr<RenderFrameHostImpl> >
      RFHPendingDeleteMap;
  RFHPendingDeleteMap pending_delete_hosts_;

  
  
  InterstitialPageImpl* interstitial_page_;

  NotificationRegistrar registrar_;

  
  
  scoped_ptr<NavigationRequest> navigation_request_;

  base::WeakPtrFactory<RenderFrameHostManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RenderFrameHostManager);
};

}  

#endif  
