// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_NAVIGATOR_H_
#define CONTENT_BROWSER_FRAME_HOST_NAVIGATOR_H_

#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"
#include "content/public/browser/navigation_controller.h"
#include "ui/base/window_open_disposition.h"

class GURL;
struct FrameHostMsg_BeginNavigation_Params;
struct FrameHostMsg_DidCommitProvisionalLoad_Params;
struct FrameHostMsg_DidFailProvisionalLoadWithError_Params;

namespace base {
class TimeTicks;
}

namespace content {

class NavigationControllerImpl;
class NavigationEntryImpl;
class NavigatorDelegate;
class RenderFrameHostImpl;
struct NavigationBeforeCommitInfo;

class CONTENT_EXPORT Navigator : public base::RefCounted<Navigator> {
 public:
  
  virtual NavigationController* GetController();

  

  
  virtual void DidStartProvisionalLoad(RenderFrameHostImpl* render_frame_host,
                                       const GURL& url,
                                       bool is_transition_navigation) {};

  
  virtual void DidFailProvisionalLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const FrameHostMsg_DidFailProvisionalLoadWithError_Params& params) {};

  
  virtual void DidFailLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      int error_code,
      const base::string16& error_description) {}

  
  virtual void DidNavigate(
      RenderFrameHostImpl* render_frame_host,
      const FrameHostMsg_DidCommitProvisionalLoad_Params& params) {}

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual bool NavigateToPendingEntry(
      RenderFrameHostImpl* render_frame_host,
      NavigationController::ReloadType reload_type);


  

  virtual base::TimeTicks GetCurrentLoadStart();

  
  
  virtual void RequestOpenURL(RenderFrameHostImpl* render_frame_host,
                              const GURL& url,
                              const Referrer& referrer,
                              WindowOpenDisposition disposition,
                              bool should_replace_current_entry,
                              bool user_gesture) {}

  
  
  
  virtual void RequestTransferURL(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      const std::vector<GURL>& redirect_chain,
      const Referrer& referrer,
      ui::PageTransition page_transition,
      WindowOpenDisposition disposition,
      const GlobalRequestID& transferred_global_request_id,
      bool should_replace_current_entry,
      bool user_gesture) {}

  
  
  
  virtual void CommitNavigation(RenderFrameHostImpl* render_frame_host,
                                const NavigationBeforeCommitInfo& info) {};

 protected:
  friend class base::RefCounted<Navigator>;
  virtual ~Navigator() {}
};

}  

#endif  
