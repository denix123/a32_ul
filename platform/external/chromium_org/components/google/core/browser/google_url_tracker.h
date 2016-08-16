// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_URL_TRACKER_H_
#define COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_URL_TRACKER_H_

#include <map>
#include <string>
#include <utility>

#include "base/callback_forward.h"
#include "base/callback_list.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/google/core/browser/google_url_tracker_client.h"
#include "components/google/core/browser/google_url_tracker_map_entry.h"
#include "components/keyed_service/core/keyed_service.h"
#include "net/base/network_change_notifier.h"
#include "net/url_request/url_fetcher.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

class GoogleURLTrackerNavigationHelper;
class PrefService;

namespace infobars {
class InfoBar;
}

class GoogleURLTracker
    : public net::URLFetcherDelegate,
      public net::NetworkChangeNotifier::NetworkChangeObserver,
      public KeyedService {
 public:
  
  
  typedef base::Callback<void()> OnGoogleURLUpdatedCallback;
  typedef base::CallbackList<void()> CallbackList;
  typedef CallbackList::Subscription Subscription;

  
  
  enum Mode {
    NORMAL_MODE,
    UNIT_TEST_MODE,
  };

  static const char kDefaultGoogleHomepage[];

  
  GoogleURLTracker(scoped_ptr<GoogleURLTrackerClient> client, Mode mode);

  virtual ~GoogleURLTracker();

  
  const GURL& google_url() const { return google_url_; }

  
  
  
  
  
  
  
  void RequestServerCheck(bool force);

  
  
  
  
  void SearchCommitted();

  
  void AcceptGoogleURL(bool redo_searches);
  void CancelGoogleURL();
  const GURL& fetched_google_url() const { return fetched_google_url_; }
  GoogleURLTrackerClient* client() { return client_.get(); }

  
  void DeleteMapEntryForManager(
      const infobars::InfoBarManager* infobar_manager);

  
  
  
  
  
  
  
  
  virtual void OnNavigationPending(
      scoped_ptr<GoogleURLTrackerNavigationHelper> nav_helper,
      infobars::InfoBarManager* infobar_manager,
      int pending_id);

  
  
  
  virtual void OnNavigationCommitted(infobars::InfoBarManager* infobar_manager,
                                     const GURL& search_url);

  
  virtual void OnTabClosed(GoogleURLTrackerNavigationHelper* nav_helper);

  scoped_ptr<Subscription> RegisterCallback(
      const OnGoogleURLUpdatedCallback& cb);

 private:
  friend class GoogleURLTrackerTest;
  friend class SyncTest;

  typedef std::map<const infobars::InfoBarManager*, GoogleURLTrackerMapEntry*>
      EntryMap;

  static const char kSearchDomainCheckURL[];

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  virtual void OnNetworkChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  
  virtual void Shutdown() OVERRIDE;

  
  
  
  void SetNeedToFetch();

  
  
  void FinishSleep();

  
  
  void StartFetchIfDesirable();

  
  
  
  void CloseAllEntries(bool redo_searches);

  
  
  
  
  
  
  void UnregisterForEntrySpecificNotifications(
      GoogleURLTrackerMapEntry* map_entry,
      bool must_be_listening_for_commit);

  void NotifyGoogleURLUpdated();

  CallbackList callback_list_;

  scoped_ptr<GoogleURLTrackerClient> client_;

  GURL google_url_;
  GURL fetched_google_url_;
  scoped_ptr<net::URLFetcher> fetcher_;
  int fetcher_id_;
  bool in_startup_sleep_;  
                           
  bool already_fetched_;   
                           
  bool need_to_fetch_;     
                           
                           
                           
                           
  bool need_to_prompt_;    
                           
                           
  bool search_committed_;  
                           
  EntryMap entry_map_;
  base::WeakPtrFactory<GoogleURLTracker> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GoogleURLTracker);
};

#endif  
