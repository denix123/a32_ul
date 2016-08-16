// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_INTERSTITIAL_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_INTERSTITIAL_H_

#include <string>

#include "base/callback.h"
#include "chrome/browser/supervised_user/supervised_user_service_observer.h"
#include "content/public/browser/interstitial_page_delegate.h"
#include "url/gurl.h"

namespace content {
class InterstitialPage;
class WebContents;
}

class Profile;

class SupervisedUserInterstitial : public content::InterstitialPageDelegate,
                                   public SupervisedUserServiceObserver {
 public:
  static void Show(content::WebContents* web_contents,
                   const GURL& url,
                   const base::Callback<void(bool)>& callback);

 private:
  SupervisedUserInterstitial(content::WebContents* web_contents,
                             const GURL& url,
                             const base::Callback<void(bool)>& callback);
  virtual ~SupervisedUserInterstitial();

  bool Init();

  
  virtual std::string GetHTMLContents() OVERRIDE;
  virtual void CommandReceived(const std::string& command) OVERRIDE;
  virtual void OnProceed() OVERRIDE;
  virtual void OnDontProceed() OVERRIDE;

  
  virtual void OnURLFilterChanged() OVERRIDE;

  
  
  
  bool ShouldProceed();

  void DispatchContinueRequest(bool continue_request);

  
  content::WebContents* web_contents_;

  Profile* profile_;

  content::InterstitialPage* interstitial_page_;  

  GURL url_;

  base::Callback<void(bool)> callback_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserInterstitial);
};

#endif  
