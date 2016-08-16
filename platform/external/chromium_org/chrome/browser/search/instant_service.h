// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_INSTANT_SERVICE_H_
#define CHROME_BROWSER_SEARCH_INSTANT_SERVICE_H_

#include <set>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "components/history/core/browser/history_types.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/search_engines/template_url_service_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "url/gurl.h"

class InstantIOContext;
struct InstantMostVisitedItem;
class InstantSearchPrerenderer;
class InstantServiceObserver;
class Profile;
struct TemplateURLData;
class TemplateURLService;
struct ThemeBackgroundInfo;
class ThemeService;

namespace content {
class RenderProcessHost;
}

class InstantService : public KeyedService,
                       public content::NotificationObserver,
                       public TemplateURLServiceObserver {
 public:
  explicit InstantService(Profile* profile);
  virtual ~InstantService();

  
  
  void AddInstantProcess(int process_id);
  bool IsInstantProcess(int process_id) const;

  
  void AddObserver(InstantServiceObserver* observer);
  void RemoveObserver(InstantServiceObserver* observer);

#if defined(UNIT_TEST)
  int GetInstantProcessCount() const {
    return process_ids_.size();
  }
#endif

  

  
  
  void DeleteMostVisitedItem(const GURL& url);

  
  
  void UndoMostVisitedDeletion(const GURL& url);

  
  
  void UndoAllMostVisitedDeletions();

  
  
  
  
  void UpdateThemeInfo();

  
  
  void UpdateMostVisitedItemsInfo();

  
  void SendSearchURLsToRenderer(content::RenderProcessHost* rph);

  
  
  void OnOmniboxStartMarginChanged(int start_margin);

  InstantSearchPrerenderer* instant_search_prerenderer() {
    return instant_prerenderer_.get();
  }

  int omnibox_start_margin() const { return omnibox_start_margin_; }

 private:
  friend class InstantExtendedTest;
  friend class InstantServiceTest;
  friend class InstantTestBase;
  friend class InstantUnitTestBase;

  FRIEND_TEST_ALL_PREFIXES(InstantExtendedManualTest,
                           MANUAL_SearchesFromFakebox);
  FRIEND_TEST_ALL_PREFIXES(InstantExtendedTest, ProcessIsolation);
  FRIEND_TEST_ALL_PREFIXES(InstantServiceEnabledTest,
                           SendsSearchURLsToRenderer);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  
  
  virtual void OnTemplateURLServiceChanged() OVERRIDE;

  
  void OnRendererProcessTerminated(int process_id);

  
  
  
  void OnMostVisitedItemsReceived(const history::MostVisitedURLList& data);

  
  void NotifyAboutMostVisitedItems();

  
  void OnThemeChanged(ThemeService* theme_service);

  void ResetInstantSearchPrerenderer();

  Profile* const profile_;

  
  
  TemplateURLService* template_url_service_;

  
  std::set<int> process_ids_;

  
  std::vector<InstantMostVisitedItem> most_visited_items_;

  
  scoped_ptr<ThemeBackgroundInfo> theme_info_;

  
  
  int omnibox_start_margin_;

  ObserverList<InstantServiceObserver> observers_;

  content::NotificationRegistrar registrar_;

  scoped_refptr<InstantIOContext> instant_io_context_;

  
  scoped_ptr<InstantSearchPrerenderer> instant_prerenderer_;

  
  
  scoped_ptr<TemplateURLData> previous_default_search_provider_;
  GURL previous_google_base_url_;

  
  base::WeakPtrFactory<InstantService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(InstantService);
};

#endif  
