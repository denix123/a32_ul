// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_NET_NET_ERROR_HELPER_H_
#define CHROME_RENDERER_NET_NET_ERROR_HELPER_H_

#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/common/localized_error.h"
#include "chrome/common/net/net_error_info.h"
#include "chrome/renderer/net/net_error_helper_core.h"
#include "content/public/renderer/render_frame_observer.h"
#include "content/public/renderer/render_frame_observer_tracker.h"
#include "content/public/renderer/render_process_observer.h"

class GURL;

namespace blink {
class WebFrame;
class WebURLResponse;
struct WebURLError;
}

namespace content {
class ResourceFetcher;
}

class NetErrorHelper
    : public content::RenderFrameObserver,
      public content::RenderFrameObserverTracker<NetErrorHelper>,
      public content::RenderProcessObserver,
      public NetErrorHelperCore::Delegate {
 public:
  explicit NetErrorHelper(content::RenderFrame* render_view);
  virtual ~NetErrorHelper();

  
  void ReloadButtonPressed();
  void LoadStaleButtonPressed();
  void MoreButtonPressed();

  
  virtual void DidStartProvisionalLoad() OVERRIDE;
  virtual void DidCommitProvisionalLoad(bool is_new_navigation) OVERRIDE;
  virtual void DidFinishLoad() OVERRIDE;
  virtual void OnStop() OVERRIDE;
  virtual void WasShown() OVERRIDE;
  virtual void WasHidden() OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void NetworkStateChanged(bool online) OVERRIDE;

  
  
  
  
  
  
  
  
  void GetErrorHTML(blink::WebFrame* frame,
                    const blink::WebURLError& error,
                    bool is_failed_post,
                    std::string* error_html);

  
  
  bool ShouldSuppressErrorPage(blink::WebFrame* frame, const GURL& url);

  
  void TrackClick(int tracking_id);

 private:
  
  virtual void GenerateLocalizedErrorPage(
      const blink::WebURLError& error,
      bool is_failed_post,
      scoped_ptr<LocalizedError::ErrorPageParams> params,
      bool* reload_button_shown,
      bool* load_stale_button_shown,
      std::string* html) const OVERRIDE;
  virtual void LoadErrorPageInMainFrame(const std::string& html,
                                        const GURL& failed_url) OVERRIDE;
  virtual void EnablePageHelperFunctions() OVERRIDE;
  virtual void UpdateErrorPage(const blink::WebURLError& error,
                               bool is_failed_post) OVERRIDE;
  virtual void FetchNavigationCorrections(
      const GURL& navigation_correction_url,
      const std::string& navigation_correction_request_body) OVERRIDE;
  virtual void CancelFetchNavigationCorrections() OVERRIDE;
  virtual void SendTrackingRequest(
      const GURL& tracking_url,
      const std::string& tracking_request_body) OVERRIDE;
  virtual void ReloadPage() OVERRIDE;
  virtual void LoadPageFromCache(const GURL& page_url) OVERRIDE;

  void OnNetErrorInfo(int status);
  void OnSetNavigationCorrectionInfo(const GURL& navigation_correction_url,
                                     const std::string& language,
                                     const std::string& country_code,
                                     const std::string& api_key,
                                     const GURL& search_url);

  void OnNavigationCorrectionsFetched(const blink::WebURLResponse& response,
                                      const std::string& data);

  void OnTrackingRequestComplete(const blink::WebURLResponse& response,
                                 const std::string& data);

  scoped_ptr<content::ResourceFetcher> correction_fetcher_;
  scoped_ptr<content::ResourceFetcher> tracking_fetcher_;

  scoped_ptr<NetErrorHelperCore> core_;

  DISALLOW_COPY_AND_ASSIGN(NetErrorHelper);
};

#endif  
