// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_SAFE_BROWSING_BLOCKING_PAGE_H_
#define CHROME_BROWSER_SAFE_BROWSING_SAFE_BROWSING_BLOCKING_PAGE_H_

#include <map>
#include <string>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/time/time.h"
#include "chrome/browser/history/history_service.h"
#include "chrome/browser/safe_browsing/ui_manager.h"
#include "content/public/browser/interstitial_page_delegate.h"
#include "url/gurl.h"

class MalwareDetails;
class SafeBrowsingBlockingPageFactory;

namespace base {
class DictionaryValue;
class MessageLoop;
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

class SafeBrowsingBlockingPage : public content::InterstitialPageDelegate {
 public:
  typedef SafeBrowsingUIManager::UnsafeResource UnsafeResource;
  typedef std::vector<UnsafeResource> UnsafeResourceList;
  typedef std::map<content::WebContents*, UnsafeResourceList> UnsafeResourceMap;

  virtual ~SafeBrowsingBlockingPage();

  
  
  static SafeBrowsingBlockingPage* CreateBlockingPage(
      SafeBrowsingUIManager* ui_manager,
      content::WebContents* web_contents,
      const UnsafeResource& unsafe_resource);

  
  
  
  
  
  static void ShowBlockingPage(
      SafeBrowsingUIManager* ui_manager, const UnsafeResource& resource);

  
  
  static void RegisterFactory(SafeBrowsingBlockingPageFactory* factory) {
    factory_ = factory;
  }

  
  virtual std::string GetHTMLContents() OVERRIDE;
  virtual void OnProceed() OVERRIDE;
  virtual void OnDontProceed() OVERRIDE;
  virtual void CommandReceived(const std::string& command) OVERRIDE;
  virtual void OverrideRendererPrefs(
      content::RendererPreferences* prefs) OVERRIDE;

 protected:
  friend class SafeBrowsingBlockingPageTest;
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingBlockingPageTest,
                           ProceedThenDontProceed);

  void DontCreateViewForTesting();
  void Show();
  void SetReportingPreference(bool report);
  void UpdateReportingPref();  

  
  SafeBrowsingBlockingPage(SafeBrowsingUIManager* ui_manager,
                           content::WebContents* web_contents,
                           const UnsafeResourceList& unsafe_resources);

  
  
  
  
  int64 malware_details_proceed_delay_ms_;
  content::InterstitialPage* interstitial_page() const {
    return interstitial_page_;
  }

  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingBlockingPageTest,
      MalwareReportsTransitionDisabled);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingBlockingPageTest,
      MalwareReportsToggling);

  
  
  enum Decision {
    SHOW,
    PROCEED,
    DONT_PROCEED,
    PROCEEDING_DISABLED,
    MAX_DECISION
  };
  enum Interaction {
    TOTAL_VISITS,
    SHOW_ADVANCED,
    SHOW_PRIVACY_POLICY,
    SHOW_DIAGNOSTIC,
    SHOW_LEARN_MORE,
    MAX_INTERACTION
  };

  
  void RecordUserDecision(Decision decision);
  void RecordUserInteraction(Interaction interaction);

  
  void OnGotHistoryCount(bool success, int num_visits, base::Time first_visit);

  
  
  bool CanShowMalwareDetailsOption();

  
  
  
  
  void FinishMalwareDetails(int64 delay_ms);

  
  
  bool IsPrefEnabled(const char* pref);

  
  
  
  static UnsafeResourceMap* GetUnsafeResourcesMap();

  
  
  static void NotifySafeBrowsingUIManager(
      SafeBrowsingUIManager* ui_manager,
      const UnsafeResourceList& resources, bool proceed);

  
  
  static bool IsMainPageLoadBlocked(
      const UnsafeResourceList& unsafe_resources);

  friend class SafeBrowsingBlockingPageFactoryImpl;

  
  SafeBrowsingUIManager* ui_manager_;
  base::MessageLoop* report_loop_;

  
  
  
  
  bool is_main_frame_load_blocked_;

  
  
  int navigation_entry_index_to_remove_;

  
  UnsafeResourceList unsafe_resources_;

  
  
  
  scoped_refptr<MalwareDetails> malware_details_;

  bool proceeded_;

  content::WebContents* web_contents_;
  GURL url_;
  content::InterstitialPage* interstitial_page_;  

  
  bool create_view_;

  
  enum {
    TYPE_MALWARE,
    TYPE_HARMFUL,
    TYPE_PHISHING,
  } interstitial_type_;

  
  
  
  static SafeBrowsingBlockingPageFactory* factory_;

  
  int num_visits_;
  base::CancelableTaskTracker request_tracker_;

 private:
  
  
  void PopulateMalwareLoadTimeData(base::DictionaryValue* load_time_data);
  void PopulateHarmfulLoadTimeData(base::DictionaryValue* load_time_data);
  void PopulatePhishingLoadTimeData(base::DictionaryValue* load_time_data);

#if defined(ENABLE_EXTENSIONS)
  scoped_ptr<extensions::ExperienceSamplingEvent> sampling_event_;
#endif

  DISALLOW_COPY_AND_ASSIGN(SafeBrowsingBlockingPage);
};

class SafeBrowsingBlockingPageFactory {
 public:
  virtual ~SafeBrowsingBlockingPageFactory() { }

  virtual SafeBrowsingBlockingPage* CreateSafeBrowsingPage(
      SafeBrowsingUIManager* ui_manager,
      content::WebContents* web_contents,
      const SafeBrowsingBlockingPage::UnsafeResourceList& unsafe_resources) = 0;
};

#endif  
