// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_EXPIRE_HISTORY_BACKEND_H_
#define CHROME_BROWSER_HISTORY_EXPIRE_HISTORY_BACKEND_H_

#include <queue>
#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "components/history/core/browser/history_types.h"

class GURL;
class TestingProfile;

namespace history {

class HistoryClient;
class HistoryDatabase;
struct HistoryDetails;
class ThumbnailDatabase;

class BroadcastNotificationDelegate {
 public:
  
  
  virtual void BroadcastNotifications(int type,
                                      scoped_ptr<HistoryDetails> details) = 0;

  
  virtual void NotifySyncURLsModified(URLRows* rows) = 0;
  virtual void NotifySyncURLsDeleted(bool all_history,
                                     bool expired,
                                     URLRows* rows) = 0;

 protected:
  virtual ~BroadcastNotificationDelegate() {}
};

class ExpiringVisitsReader {
 public:
  virtual ~ExpiringVisitsReader() {}
  
  
  virtual bool Read(base::Time end_time, HistoryDatabase* db,
                    VisitVector* visits, int max_visits) const = 0;
};

typedef std::vector<const ExpiringVisitsReader*> ExpiringVisitsReaders;

class ExpireHistoryBackend {
 public:
  
  
  
  
  ExpireHistoryBackend(BroadcastNotificationDelegate* delegate,
                       HistoryClient* history_client);
  ~ExpireHistoryBackend();

  
  void SetDatabases(HistoryDatabase* main_db,
                    ThumbnailDatabase* thumb_db);

  
  
  void StartExpiringOldStuff(base::TimeDelta expiration_threshold);

  
  void DeleteURL(const GURL& url);

  
  void DeleteURLs(const std::vector<GURL>& url);

  
  
  void ExpireHistoryBetween(const std::set<GURL>& restrict_urls,
                            base::Time begin_time, base::Time end_time);

  
  
  
  void ExpireHistoryForTimes(const std::vector<base::Time>& times);

  
  
  void ExpireVisits(const VisitVector& visits);

  
  
  void ExpireHistoryBefore(base::Time end_time);

  
  
  
  base::Time GetCurrentExpirationTime() const {
    return base::Time::Now() - expiration_threshold_;
  }

 private:
  FRIEND_TEST_ALL_PREFIXES(ExpireHistoryTest, DeleteFaviconsIfPossible);
  FRIEND_TEST_ALL_PREFIXES(ExpireHistoryTest, ExpireSomeOldHistory);
  FRIEND_TEST_ALL_PREFIXES(ExpireHistoryTest, ExpiringVisitsReader);
  FRIEND_TEST_ALL_PREFIXES(ExpireHistoryTest, ExpireSomeOldHistoryWithSource);
  friend class ::TestingProfile;

  struct DeleteEffects {
    DeleteEffects();
    ~DeleteEffects();

    
    
    base::Time begin_time, end_time;

    
    std::map<URLID, URLRow> affected_urls;

    
    URLRows modified_urls;

    
    URLRows deleted_urls;

    
    
    
    std::set<favicon_base::FaviconID> affected_favicons;

    
    std::set<GURL> deleted_favicons;
  };

  
  
  
  void DeleteVisitRelatedInfo(const VisitVector& visits,
                              DeleteEffects* effects);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void DeleteOneURL(const URLRow& url_row,
                    bool is_bookmarked,
                    DeleteEffects* effects);

  
  
  void DeleteURLs(const URLRows& urls, DeleteEffects* effects);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void ExpireURLsForVisits(const VisitVector& visits, DeleteEffects* effects);

  
  
  
  
  
  void DeleteFaviconsIfPossible(DeleteEffects* effects);

  
  enum DeletionType {
    
    DELETION_USER_INITIATED,
    
    
    DELETION_EXPIRED
  };

  
  void BroadcastNotifications(DeleteEffects* effects, DeletionType type);

  
  void ScheduleExpire();

  
  
  
  void DoExpireIteration();

  
  
  
  
  bool ExpireSomeOldHistory(base::Time end_time,
                             const ExpiringVisitsReader* reader,
                             int max_visits);

  
  
  void ParanoidExpireHistory();

  
  
  HistoryClient* GetHistoryClient();

  
  
  void InitWorkQueue();

  
  
  const ExpiringVisitsReader* GetAllVisitsReader();

  
  
  const ExpiringVisitsReader* GetAutoSubframeVisitsReader();

  
  BroadcastNotificationDelegate* delegate_;

  
  HistoryDatabase* main_db_;       
  ThumbnailDatabase* thumb_db_;    

  
  base::TimeDelta expiration_threshold_;

  
  
  ExpiringVisitsReaders readers_;

  
  
  
  std::queue<const ExpiringVisitsReader*> work_queue_;

  
  
  
  scoped_ptr<ExpiringVisitsReader> all_visits_reader_;
  scoped_ptr<ExpiringVisitsReader> auto_subframe_visits_reader_;

  
  
  
  
  HistoryClient* history_client_;

  
  
  base::WeakPtrFactory<ExpireHistoryBackend> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExpireHistoryBackend);
};

}  

#endif  
