// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_SEARCH_INSTANT_CONTROLLER_H_
#define CHROME_BROWSER_UI_SEARCH_INSTANT_CONTROLLER_H_

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/ui/search/instant_page.h"
#include "chrome/common/search_types.h"
#include "ui/gfx/native_widget_types.h"

class BrowserInstantController;
class GURL;
class InstantService;
class InstantTab;
class Profile;

namespace content {
class WebContents;
}

#define LOG_INSTANT_DEBUG_EVENT(controller, message) \
    controller->LogDebugEvent(message)

class InstantController : public InstantPage::Delegate {
 public:
  explicit InstantController(BrowserInstantController* browser);
  virtual ~InstantController();

  
  
  
  bool SubmitQuery(const base::string16& search_terms);

  
  
  void SearchModeChanged(const SearchMode& old_mode,
                         const SearchMode& new_mode);

  
  
  void ActiveTabChanged();

  
  void TabDeactivated(content::WebContents* contents);

  
  
  void LogDebugEvent(const std::string& info) const;

  
  void ClearDebugEvents();

  
  const std::list<std::pair<int64, std::string> >& debug_events() {
    return debug_events_;
  }

  
  
  void InstantSupportChanged(InstantSupportState instant_support);

 protected:
  
  virtual InstantTab* instant_tab() const;

  virtual Profile* profile() const;

 private:
  friend class InstantExtendedManualTest;
  friend class InstantTestBase;

  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, ExtendedModeIsOn);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, MostVisited);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, ProcessIsolation);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, UnrelatedSiteInstance);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, OnDefaultSearchProviderChanged);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest,
                           AcceptingURLSearchDoesNotNavigate);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, AcceptingJSSearchDoesNotRunJS);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest,
                           ReloadSearchAfterBackReloadsCorrectQuery);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedFirstTabTest,
                           RedirectToLocalOnLoadFailure);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, KeyboardTogglesVoiceSearch);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, HomeButtonAffectsMargin);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, SearchReusesInstantTab);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest,
                           SearchDoesntReuseInstantTabWithoutSupport);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest,
                           TypedSearchURLDoesntReuseInstantTab);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest,
                           DispatchMVChangeEventWhileNavigatingBackToNTP);

  
  
  
  virtual void InstantSupportDetermined(
      const content::WebContents* contents,
      bool supports_instant) OVERRIDE;
  virtual void InstantPageAboutToNavigateMainFrame(
      const content::WebContents* contents,
      const GURL& url) OVERRIDE;

  
  
  void RedirectToLocalNTP(content::WebContents* contents);

  
  void OmniboxLostFocus(gfx::NativeView view_gaining_focus);

  
  
  void ResetInstantTab();

  
  void UpdateInfoForInstantTab();

  
  InstantService* GetInstantService() const;

  BrowserInstantController* const browser_;

  
  scoped_ptr<InstantTab> instant_tab_;

  
  SearchMode search_mode_;

  
  mutable std::list<std::pair<int64, std::string> > debug_events_;

  DISALLOW_COPY_AND_ASSIGN(InstantController);
};

#endif  
