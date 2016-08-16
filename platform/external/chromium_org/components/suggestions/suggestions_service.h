// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SUGGESTIONS_SUGGESTIONS_SERVICE_H_
#define COMPONENTS_SUGGESTIONS_SUGGESTIONS_SERVICE_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/cancelable_callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/suggestions/image_manager.h"
#include "components/suggestions/proto/suggestions.pb.h"
#include "components/suggestions/suggestions_utils.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "ui/gfx/image/image_skia.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}  

namespace user_prefs {
class PrefRegistrySyncable;
}  

namespace suggestions {

class BlacklistStore;
class SuggestionsStore;

extern const char kSuggestionsFieldTrialName[];
extern const char kSuggestionsFieldTrialURLParam[];
extern const char kSuggestionsFieldTrialCommonParamsParam[];
extern const char kSuggestionsFieldTrialBlacklistPathParam[];
extern const char kSuggestionsFieldTrialBlacklistUrlParam[];
extern const char kSuggestionsFieldTrialStateParam[];
extern const char kSuggestionsFieldTrialControlParam[];
extern const char kSuggestionsFieldTrialStateEnabled[];
extern const int64 kDefaultExpiryUsec;

class SuggestionsService : public KeyedService, public net::URLFetcherDelegate {
 public:
  typedef base::Callback<void(const SuggestionsProfile&)> ResponseCallback;

  SuggestionsService(
      net::URLRequestContextGetter* url_request_context,
      scoped_ptr<SuggestionsStore> suggestions_store,
      scoped_ptr<ImageManager> thumbnail_manager,
      scoped_ptr<BlacklistStore> blacklist_store);
  virtual ~SuggestionsService();

  
  static bool IsEnabled();

  
  static bool IsControlGroup();

  
  
  
  
  
  
  
  
  
  
  
  
  void FetchSuggestionsData(SyncState sync_state,
                            ResponseCallback callback);

  
  
  void GetPageThumbnail(
      const GURL& url,
      base::Callback<void(const GURL&, const SkBitmap*)> callback);

  
  
  void BlacklistURL(const GURL& candidate_url,
                    const ResponseCallback& callback);

  
  
  static bool GetBlacklistedUrl(const net::URLFetcher& request, GURL* url);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  void SetDefaultExpiryTimestamp(SuggestionsProfile* suggestions,
                                 int64 timestamp_usec);
 private:
  friend class SuggestionsServiceTest;
  FRIEND_TEST_ALL_PREFIXES(SuggestionsServiceTest, BlacklistURLFails);
  FRIEND_TEST_ALL_PREFIXES(SuggestionsServiceTest, FetchSuggestionsData);
  FRIEND_TEST_ALL_PREFIXES(SuggestionsServiceTest, UpdateBlacklistDelay);

  
  
  void FetchSuggestionsDataNoTimeout(ResponseCallback callback);

  
  void IssueRequest(const GURL& url);

  
  net::URLFetcher* CreateSuggestionsRequest(const GURL& url);

  
  
  virtual void OnRequestTimeout();

  
  
  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  virtual void Shutdown() OVERRIDE;

  
  void ServeFromCache();

  
  void FilterAndServe(SuggestionsProfile* suggestions);

  
  
  
  void ScheduleBlacklistUpload(bool last_request_successful);

  
  
  void UploadOneFromBlacklist();

  
  void UpdateBlacklistDelay(bool last_request_successful);

  
  int blacklist_delay() const { return blacklist_delay_sec_; }
  void set_blacklist_delay(int delay) { blacklist_delay_sec_ = delay; }

  base::ThreadChecker thread_checker_;

  
  scoped_ptr<SuggestionsStore> suggestions_store_;

  
  scoped_ptr<BlacklistStore> blacklist_store_;

  
  
  scoped_ptr<net::URLFetcher> pending_request_;

  
  
  scoped_ptr<base::CancelableClosure> pending_timeout_closure_;

  
  
  base::TimeTicks last_request_started_time_;

  
  GURL suggestions_url_;

  
  std::string blacklist_url_prefix_;

  
  std::vector<ResponseCallback> waiting_requestors_;

  
  scoped_ptr<ImageManager> thumbnail_manager_;

  net::URLRequestContextGetter* url_request_context_;

  
  int blacklist_delay_sec_;

  
  
  int request_timeout_ms_;

  
  base::WeakPtrFactory<SuggestionsService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SuggestionsService);
};

}  

#endif  
