// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SSL_SSL_BLOCKING_PAGE_H_
#define CHROME_BROWSER_SSL_SSL_BLOCKING_PAGE_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/strings/string16.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/time/time.h"
#include "chrome/browser/history/history_service.h"
#include "content/public/browser/interstitial_page_delegate.h"
#include "net/ssl/ssl_info.h"
#include "url/gurl.h"

namespace base {
class DictionaryValue;
}

namespace content {
class InterstitialPage;
class WebContents;
}

#if defined(ENABLE_EXTENSIONS)
namespace extensions {
class ExperienceSamplingEvent;
}
#endif

class SSLErrorClassification;

class SSLBlockingPage : public content::InterstitialPageDelegate {
 public:
  
  
  
  enum SSLBlockingPageCommands {
    CMD_DONT_PROCEED = 0,
    CMD_PROCEED = 1,
    CMD_MORE = 2,
    CMD_RELOAD = 3,
    CMD_HELP = 4,
    CMD_CLOCK = 5
  };

  enum SSLBlockingPageOptionsMask {
    OVERRIDABLE = 1 << 0,
    STRICT_ENFORCEMENT = 1 << 1,
    EXPIRED_BUT_PREVIOUSLY_ALLOWED = 1 << 2
  };

  virtual ~SSLBlockingPage();

  
  void Show();

  
  
  
  
  SSLBlockingPage(content::WebContents* web_contents,
                  int cert_error,
                  const net::SSLInfo& ssl_info,
                  const GURL& request_url,
                  int options_mask,
                  const base::Callback<void(bool)>& callback);

  
  
  
  
  static void SetExtraInfo(base::DictionaryValue* strings,
                           const std::vector<base::string16>& extra_info);

 protected:
  
  virtual std::string GetHTMLContents() OVERRIDE;
  virtual void CommandReceived(const std::string& command) OVERRIDE;
  virtual void OverrideEntry(content::NavigationEntry* entry) OVERRIDE;
  virtual void OverrideRendererPrefs(
      content::RendererPreferences* prefs) OVERRIDE;
  virtual void OnProceed() OVERRIDE;
  virtual void OnDontProceed() OVERRIDE;

 private:
  void NotifyDenyCertificate();
  void NotifyAllowCertificate();

  
  void OnGotHistoryCount(bool success, int num_visits, base::Time first_visit);

  base::Callback<void(bool)> callback_;

  content::WebContents* web_contents_;
  const int cert_error_;
  const net::SSLInfo ssl_info_;
  const GURL request_url_;
  
  
  const bool overridable_;
  
  const bool strict_enforcement_;
  content::InterstitialPage* interstitial_page_;  
  
  bool internal_;
  
  int num_visits_;
  
  base::CancelableTaskTracker request_tracker_;
  
  
  const bool expired_but_previously_allowed_;
  scoped_ptr<SSLErrorClassification> ssl_error_classification_;

#if defined(ENABLE_EXTENSIONS)
  
  scoped_ptr<extensions::ExperienceSamplingEvent> sampling_event_;
#endif

  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(SSLBlockingPage);
};

#endif  
