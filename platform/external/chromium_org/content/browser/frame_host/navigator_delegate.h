// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_NAVIGATOR_DELEGATE_H_
#define CONTENT_BROWSER_FRAME_HOST_NAVIGATOR_DELEGATE_H_

#include "base/strings/string16.h"
#include "content/public/browser/invalidate_type.h"
#include "content/public/browser/navigation_controller.h"
#include "ui/base/page_transition_types.h"
#include "ui/base/window_open_disposition.h"

class GURL;
struct FrameHostMsg_DidCommitProvisionalLoad_Params;
struct FrameHostMsg_DidFailProvisionalLoadWithError_Params;

namespace content {

class RenderFrameHostImpl;
struct LoadCommittedDetails;
struct OpenURLParams;

class CONTENT_EXPORT NavigatorDelegate {
 public:
  
  
  virtual void DidStartProvisionalLoad(
      RenderFrameHostImpl* render_frame_host,
      const GURL& validated_url,
      bool is_error_page,
      bool is_iframe_srcdoc) {}

  
  virtual void DidStartNavigationTransition(
      RenderFrameHostImpl* render_frame_host) {}

  
  virtual void DidFailProvisionalLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const FrameHostMsg_DidFailProvisionalLoadWithError_Params& params) {}

  
  virtual void DidFailLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      int error_code,
      const base::string16& error_description) {}

  
  virtual void DidCommitProvisionalLoad(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      ui::PageTransition transition_type) {}

  
  
  virtual void DidNavigateMainFramePreCommit(bool navigation_is_within_page) {}

  
  
  
  
  virtual void DidNavigateMainFramePostCommit(
      const LoadCommittedDetails& details,
      const FrameHostMsg_DidCommitProvisionalLoad_Params& params) {}
  virtual void DidNavigateAnyFramePostCommit(
      RenderFrameHostImpl* render_frame_host,
      const LoadCommittedDetails& details,
      const FrameHostMsg_DidCommitProvisionalLoad_Params& params) {}

  virtual void SetMainFrameMimeType(const std::string& mime_type) {}
  virtual bool CanOverscrollContent() const;

  
  
  
  virtual void NotifyChangedNavigationState(InvalidateTypes changed_flags) {}

  
  virtual void AboutToNavigateRenderFrame(
      RenderFrameHostImpl* render_frame_host) {}

  
  
  virtual void DidStartNavigationToPendingEntry(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      NavigationController::ReloadType reload_type) {}

  
  
  virtual void RequestOpenURL(RenderFrameHostImpl* render_frame_host,
                              const OpenURLParams& params) {}

  
  
  virtual bool ShouldPreserveAbortedURLs();
};

}  

#endif  
