// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_WEB_NAVIGATION_FRAME_NAVIGATION_STATE_H_
#define CHROME_BROWSER_EXTENSIONS_API_WEB_NAVIGATION_FRAME_NAVIGATION_STATE_H_

#include <map>
#include <set>

#include "base/compiler_specific.h"
#include "url/gurl.h"

namespace content {
class RenderFrameHost;
class RenderViewHost;
}

namespace extensions {

class FrameNavigationState {
 public:
  typedef std::set<content::RenderFrameHost*>::const_iterator const_iterator;

  FrameNavigationState();
  ~FrameNavigationState();

  
  const_iterator begin() const { return frame_hosts_.begin(); }
  const_iterator end() const { return frame_hosts_.end(); }

  
  bool CanSendEvents(content::RenderFrameHost* frame_host) const;

  
  
  bool IsValidUrl(const GURL& url) const;

  
  void TrackFrame(content::RenderFrameHost* frame_host,
                  const GURL& url,
                  bool is_error_page,
                  bool is_iframe_srcdoc);

  
  void FrameDetached(content::RenderFrameHost* frame_host);

  
  
  void StopTrackingFramesInRVH(content::RenderViewHost* render_view_host,
                               content::RenderFrameHost* frame_host_to_skip);

  
  void UpdateFrame(content::RenderFrameHost* frame_host, const GURL& url);

  
  bool IsValidFrame(content::RenderFrameHost* frame_host) const;

  
  
  
  GURL GetUrl(content::RenderFrameHost* frame_host) const;

  
  content::RenderFrameHost* GetLastCommittedMainFrameHost() const;

  
  
  void SetErrorOccurredInFrame(content::RenderFrameHost* frame_host);

  
  bool GetErrorOccurredInFrame(content::RenderFrameHost* frame_host) const;

  
  
  void SetNavigationCompleted(content::RenderFrameHost* frame_host);

  
  bool GetNavigationCompleted(content::RenderFrameHost* frame_host) const;

  
  void SetParsingFinished(content::RenderFrameHost* frame_host);

  
  bool GetParsingFinished(content::RenderFrameHost* frame_host) const;

  
  
  void SetNavigationCommitted(content::RenderFrameHost* frame_host);

  
  bool GetNavigationCommitted(content::RenderFrameHost* frame_host) const;

  
  void SetIsServerRedirected(content::RenderFrameHost* frame_host);

  
  bool GetIsServerRedirected(content::RenderFrameHost* frame_host) const;

#ifdef UNIT_TEST
  static void set_allow_extension_scheme(bool allow_extension_scheme) {
    allow_extension_scheme_ = allow_extension_scheme;
  }
#endif

 private:
  struct FrameState {
    FrameState();

    bool error_occurred;  
    bool is_iframe_srcdoc;  
    bool is_navigating;  
    bool is_committed;  
    bool is_server_redirected;  
    bool is_parsing;  
    GURL url;  
  };
  typedef std::map<content::RenderFrameHost*, FrameState> FrameHostToStateMap;

  
  FrameHostToStateMap frame_host_state_map_;

  
  std::set<content::RenderFrameHost*> frame_hosts_;

  
  content::RenderFrameHost* main_frame_host_;

  
  static bool allow_extension_scheme_;

  DISALLOW_COPY_AND_ASSIGN(FrameNavigationState);
};

}  

#endif  
