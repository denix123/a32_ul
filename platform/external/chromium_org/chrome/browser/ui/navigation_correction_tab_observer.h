// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_NAVIGATION_CORRECTION_TAB_OBSERVER_H_
#define CHROME_BROWSER_UI_NAVIGATION_CORRECTION_TAB_OBSERVER_H_

#include "base/prefs/pref_change_registrar.h"
#include "components/google/core/browser/google_url_tracker.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class Profile;

namespace user_prefs {
class PrefRegistrySyncable;
}

class NavigationCorrectionTabObserver
    : public content::WebContentsObserver,
      public content::WebContentsUserData<NavigationCorrectionTabObserver> {
 public:
  virtual ~NavigationCorrectionTabObserver();

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

 private:
  explicit NavigationCorrectionTabObserver(content::WebContents* web_contents);
  friend class content::WebContentsUserData<NavigationCorrectionTabObserver>;

  
  virtual void RenderViewCreated(
      content::RenderViewHost* render_view_host) OVERRIDE;

  

  
  void OnGoogleURLUpdated();

  
  
  GURL GetNavigationCorrectionURL() const;

  
  void OnEnabledChanged();

  
  void UpdateNavigationCorrectionInfo(content::RenderViewHost* rvh);

  Profile* profile_;
  PrefChangeRegistrar pref_change_registrar_;
  scoped_ptr<GoogleURLTracker::Subscription> google_url_updated_subscription_;

  DISALLOW_COPY_AND_ASSIGN(NavigationCorrectionTabObserver);
};

#endif  
