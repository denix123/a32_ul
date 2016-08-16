// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_NET_NET_ERROR_HELPER_CORE_H_
#define CHROME_RENDERER_NET_NET_ERROR_HELPER_CORE_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "chrome/common/localized_error.h"
#include "chrome/common/net/net_error_info.h"
#include "url/gurl.h"

namespace base {
class ListValue;
}

namespace blink {
struct WebURLError;
}

class NetErrorHelperCore {
 public:
  enum FrameType {
    MAIN_FRAME,
    SUB_FRAME,
  };

  enum PageType {
    NON_ERROR_PAGE,
    ERROR_PAGE,
  };

  enum Button {
    NO_BUTTON,
    RELOAD_BUTTON,
    LOAD_STALE_BUTTON,
    MORE_BUTTON,
  };

  
  
  class Delegate {
   public:
    
    virtual void GenerateLocalizedErrorPage(
        const blink::WebURLError& error,
        bool is_failed_post,
        scoped_ptr<LocalizedError::ErrorPageParams> params,
        bool* reload_button_shown,
        bool* load_stale_button_shown,
        std::string* html) const = 0;

    
    virtual void LoadErrorPageInMainFrame(const std::string& html,
                                          const GURL& failed_url) = 0;

    
    virtual void EnablePageHelperFunctions() = 0;

    
    
    
    virtual void UpdateErrorPage(const blink::WebURLError& error,
                                 bool is_failed_post) = 0;

    
    
    
    virtual void FetchNavigationCorrections(
        const GURL& navigation_correction_url,
        const std::string& navigation_correction_request_body) = 0;

    
    
    virtual void CancelFetchNavigationCorrections() = 0;

    
    
    virtual void SendTrackingRequest(
        const GURL& tracking_url,
        const std::string& tracking_request_body) = 0;

    
    virtual void ReloadPage() = 0;

    
    virtual void LoadPageFromCache(const GURL& page_url) = 0;

   protected:
    virtual ~Delegate() {}
  };

  struct NavigationCorrectionParams {
    NavigationCorrectionParams();
    ~NavigationCorrectionParams();

    
    GURL url;

    std::string language;
    std::string country_code;
    std::string api_key;
    GURL search_url;
  };

  NetErrorHelperCore(Delegate* delegate,
                     bool auto_reload_enabled,
                     bool auto_reload_visible_only,
                     bool is_visible);
  ~NetErrorHelperCore();

  
  
  
  
  
  
  
  
  void GetErrorHTML(FrameType frame_type,
                    const blink::WebURLError& error,
                    bool is_failed_post,
                    std::string* error_html);

  
  void OnStartLoad(FrameType frame_type, PageType page_type);
  void OnCommitLoad(FrameType frame_type, const GURL& url);
  void OnFinishLoad(FrameType frame_type);
  void OnStop();
  void OnWasShown();
  void OnWasHidden();

  void CancelPendingFetches();

  
  
  void OnNavigationCorrectionsFetched(const std::string& corrections,
                                      const std::string& accept_languages,
                                      bool is_rtl);

  
  
  void OnNetErrorInfo(chrome_common_net::DnsProbeStatus status);

  void OnSetNavigationCorrectionInfo(const GURL& navigation_correction_url,
                                     const std::string& language,
                                     const std::string& country_code,
                                     const std::string& api_key,
                                     const GURL& search_url);
  
  
  
  
  
  
  
  
  
  
  
  void NetworkStateChanged(bool online);

  int auto_reload_count() const { return auto_reload_count_; }

  bool ShouldSuppressErrorPage(FrameType frame_type, const GURL& url);

  void set_timer_for_testing(scoped_ptr<base::Timer> timer) {
    auto_reload_timer_.reset(timer.release());
  }

  
  
  
  void ExecuteButtonPress(Button button);

  
  
  
  
  void TrackClick(int tracking_id);

 private:
  struct ErrorPageInfo;

  
  
  
  void GetErrorHtmlForMainFrame(ErrorPageInfo* pending_error_page_info,
                                std::string* error_html);

  
  
  
  void UpdateErrorPage();

  blink::WebURLError GetUpdatedError(const blink::WebURLError& error) const;

  void Reload();
  bool MaybeStartAutoReloadTimer();
  void StartAutoReloadTimer();
  void AutoReloadTimerFired();
  void PauseAutoReloadTimer();

  static bool IsReloadableError(const ErrorPageInfo& info);

  Delegate* delegate_;

  
  chrome_common_net::DnsProbeStatus last_probe_status_;

  
  
  scoped_ptr<ErrorPageInfo> pending_error_page_info_;

  
  
  scoped_ptr<ErrorPageInfo> committed_error_page_info_;

  NavigationCorrectionParams navigation_correction_params_;

  
  const bool auto_reload_enabled_;

  
  const bool auto_reload_visible_only_;

  
  scoped_ptr<base::Timer> auto_reload_timer_;

  
  
  bool auto_reload_paused_;

  
  
  
  
  
  
  
  bool uncommitted_load_started_;

  
  bool online_;

  
  bool visible_;

  int auto_reload_count_;

  
  
  
  Button navigation_from_button_;
};

#endif  
