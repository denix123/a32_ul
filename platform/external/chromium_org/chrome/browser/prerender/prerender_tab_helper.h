// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRERENDER_PRERENDER_TAB_HELPER_H_
#define CHROME_BROWSER_PRERENDER_PRERENDER_TAB_HELPER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "chrome/browser/prerender/prerender_histograms.h"
#include "chrome/browser/prerender/prerender_origin.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "url/gurl.h"

namespace autofill {
struct PasswordForm;
}

namespace password_manager {
class PasswordManager;
}

namespace prerender {

class PrerenderManager;

class PrerenderTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<PrerenderTabHelper> {
 public:
  enum Event {
    EVENT_LOGGED_IN_TABLE_REQUESTED = 0,
    EVENT_LOGGED_IN_TABLE_PRESENT = 1,
    EVENT_MAINFRAME_CHANGE = 2,
    EVENT_MAINFRAME_CHANGE_DOMAIN_LOGGED_IN = 3,
    EVENT_MAINFRAME_COMMIT = 4,
    EVENT_MAINFRAME_COMMIT_DOMAIN_LOGGED_IN = 5,
    EVENT_LOGIN_ACTION_ADDED = 6,
    EVENT_LOGIN_ACTION_ADDED_PW_EMPTY = 7,
    EVENT_MAX_VALUE
  };

  static void CreateForWebContentsWithPasswordManager(
      content::WebContents* web_contents,
      password_manager::PasswordManager* password_manager);

  virtual ~PrerenderTabHelper();

  
  virtual void DidGetRedirectForResourceRequest(
      content::RenderViewHost* render_view_host,
      const content::ResourceRedirectDetails& details) OVERRIDE;
  virtual void DidStopLoading(
      content::RenderViewHost* render_view_host) OVERRIDE;
  virtual void DidStartProvisionalLoadForFrame(
      content::RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      bool is_error_page,
      bool is_iframe_srcdoc) OVERRIDE;
  virtual void DidCommitProvisionalLoadForFrame(
      content::RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      ui::PageTransition transition_type) OVERRIDE;

  
  
  void MainFrameUrlDidChange(const GURL& url);

  
  void PasswordSubmitted(const autofill::PasswordForm& form);

  
  void PrerenderSwappedIn();

  
  void WouldHavePrerenderedNextLoad(Origin origin);

 private:
  PrerenderTabHelper(content::WebContents* web_contents,
                     password_manager::PasswordManager* password_manager);
  friend class content::WebContentsUserData<PrerenderTabHelper>;

  void RecordEvent(Event event) const;
  void RecordEventIfLoggedInURL(Event event, const GURL& url);
  void RecordEventIfLoggedInURLResult(Event event, scoped_ptr<bool> is_present,
                                      scoped_ptr<bool> lookup_succeeded);

  void RecordPerceivedPageLoadTime(
      base::TimeDelta perceived_page_load_time,
      double fraction_plt_elapsed_at_swap_in);

  
  PrerenderManager* MaybeGetPrerenderManager() const;

  
  bool IsPrerendering();

  
  
  
  NavigationType navigation_type_;

  
  
  Origin origin_;

  
  
  
  
  bool next_load_is_control_prerender_;
  Origin next_load_origin_;

  
  
  
  base::TimeTicks pplt_load_start_;

  
  
  
  base::TimeTicks actual_load_start_;

  
  GURL url_;

  base::WeakPtrFactory<PrerenderTabHelper> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PrerenderTabHelper);
};

}  

#endif  
