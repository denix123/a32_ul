// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_INFOBARS_INFOBAR_SERVICE_H_
#define CHROME_BROWSER_INFOBARS_INFOBAR_SERVICE_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "components/infobars/core/infobar_manager.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
struct LoadCommittedDetails;
class WebContents;
}

namespace infobars {
class InfoBar;
}

class InfoBarService : public infobars::InfoBarManager,
                       public content::WebContentsObserver,
                       public content::WebContentsUserData<InfoBarService> {
 public:
  static infobars::InfoBarDelegate::NavigationDetails
      NavigationDetailsFromLoadCommittedDetails(
          const content::LoadCommittedDetails& details);

  
  
  
  static content::WebContents* WebContentsFromInfoBar(
      infobars::InfoBar* infobar);

  
  
  
  
  
  
  void set_ignore_next_reload() { ignore_next_reload_ = true; }

 private:
  friend class content::WebContentsUserData<InfoBarService>;

  explicit InfoBarService(content::WebContents* web_contents);
  virtual ~InfoBarService();

  
  virtual int GetActiveEntryID() OVERRIDE;
  
  
  virtual void NotifyInfoBarAdded(infobars::InfoBar* infobar) OVERRIDE;
  virtual void NotifyInfoBarRemoved(infobars::InfoBar* infobar,
                                    bool animate) OVERRIDE;

  
  virtual void RenderProcessGone(base::TerminationStatus status) OVERRIDE;
  virtual void DidStartNavigationToPendingEntry(
      const GURL& url,
      content::NavigationController::ReloadType reload_type) OVERRIDE;
  virtual void NavigationEntryCommitted(
      const content::LoadCommittedDetails& load_details) OVERRIDE;
  virtual void WebContentsDestroyed() OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  void OnDidBlockDisplayingInsecureContent();
  void OnDidBlockRunningInsecureContent();

  
  bool ignore_next_reload_;

  DISALLOW_COPY_AND_ASSIGN(InfoBarService);
};

#endif  
