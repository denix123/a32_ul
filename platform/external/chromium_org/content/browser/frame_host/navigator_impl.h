// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_NAVIGATOR_IMPL_H_
#define CONTENT_BROWSER_FRAME_HOST_NAVIGATOR_IMPL_H_

#include "base/memory/ref_counted.h"
#include "content/browser/frame_host/navigation_controller_impl.h"
#include "content/browser/frame_host/navigator.h"
#include "content/common/content_export.h"

struct FrameMsg_Navigate_Params;

namespace content {

class NavigationControllerImpl;
class NavigatorDelegate;
struct LoadCommittedDetails;

class CONTENT_EXPORT NavigatorImpl : public Navigator {
 public:
  NavigatorImpl(NavigationControllerImpl* navigation_controller,
                NavigatorDelegate* delegate);

  
  static void MakeNavigateParams(const NavigationEntryImpl& entry,
                                 const NavigationControllerImpl& controller,
                                 NavigationController::ReloadType reload_type,
                                 base::TimeTicks navigation_start,
                                 FrameMsg_Navigate_Params* params);

  
  virtual NavigationController* GetController() OVERRIDE;
  virtual void DidStartProvisionalLoad(RenderFrameHostImpl* render_frame_host,
                                       const GURL& url,
                                       bool is_transition_navigation) OVERRIDE;
  virtual void DidFailProvisionalLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const FrameHostMsg_DidFailProvisionalLoadWithError_Params& params)
      OVERRIDE;
  virtual void DidFailLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      int error_code,
      const base::string16& error_description) OVERRIDE;
  virtual void DidNavigate(
      RenderFrameHostImpl* render_frame_host,
      const FrameHostMsg_DidCommitProvisionalLoad_Params&
          input_params) OVERRIDE;
  virtual bool NavigateToPendingEntry(
      RenderFrameHostImpl* render_frame_host,
      NavigationController::ReloadType reload_type) OVERRIDE;
  virtual void RequestOpenURL(RenderFrameHostImpl* render_frame_host,
                              const GURL& url,
                              const Referrer& referrer,
                              WindowOpenDisposition disposition,
                              bool should_replace_current_entry,
                              bool user_gesture) OVERRIDE;
  virtual void RequestTransferURL(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      const std::vector<GURL>& redirect_chain,
      const Referrer& referrer,
      ui::PageTransition page_transition,
      WindowOpenDisposition disposition,
      const GlobalRequestID& transferred_global_request_id,
      bool should_replace_current_entry,
      bool user_gesture) OVERRIDE;
  virtual void CommitNavigation(
      RenderFrameHostImpl* render_frame_host,
      const NavigationBeforeCommitInfo& info) OVERRIDE;

 private:
  virtual ~NavigatorImpl() {}

  
  
  bool NavigateToEntry(
      RenderFrameHostImpl* render_frame_host,
      const NavigationEntryImpl& entry,
      NavigationController::ReloadType reload_type);

  bool ShouldAssignSiteForURL(const GURL& url);

  void CheckWebUIRendererDoesNotDisplayNormalURL(
    RenderFrameHostImpl* render_frame_host,
    const GURL& url);

  
  
  
  
  NavigationControllerImpl* controller_;

  
  
  NavigatorDelegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(NavigatorImpl);
};

}  

#endif  
