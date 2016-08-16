// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_HISTORY_BACKEND_H_
#define CHROME_BROWSER_HISTORY_HISTORY_BACKEND_H_

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/containers/mru_cache.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/memory_pressure_listener.h"
#include "base/memory/scoped_ptr.h"
#include "base/single_thread_task_runner.h"
#include "base/task/cancelable_task_tracker.h"
#include "chrome/browser/history/expire_history_backend.h"
#include "chrome/browser/history/history_database.h"
#include "chrome/browser/history/thumbnail_database.h"
#include "chrome/browser/history/visit_tracker.h"
#include "components/history/core/browser/history_types.h"
#include "components/history/core/browser/keyword_id.h"
#include "components/visitedlink/browser/visitedlink_delegate.h"
#include "sql/init_status.h"

#if defined(OS_ANDROID)
#include "components/history/core/android/android_history_types.h"
#endif

class HistoryURLProvider;
struct HistoryURLProviderParams;
struct ImportedFaviconUsage;
class SkBitmap;
class TestingProfile;
struct ThumbnailScore;

namespace base {
class MessageLoop;
class SingleThreadTaskRunner;
}

namespace history {
#if defined(OS_ANDROID)
class AndroidProviderBackend;
#endif

class CommitLaterTask;
struct DownloadRow;
class HistoryClient;
class HistoryDBTask;
class InMemoryHistoryBackend;
class TypedUrlSyncableService;
class VisitFilter;

static const size_t kMaxFaviconsPerPage = 8;

static const size_t kMaxFaviconBitmapsPerIconURL = 8;

class QueuedHistoryDBTask {
 public:
  QueuedHistoryDBTask(
      scoped_ptr<HistoryDBTask> task,
      scoped_refptr<base::SingleThreadTaskRunner> origin_loop,
      const base::CancelableTaskTracker::IsCanceledCallback& is_canceled);
  ~QueuedHistoryDBTask();

  bool is_canceled();
  bool Run(HistoryBackend* backend, HistoryDatabase* db);
  void DoneRun();

 private:
  scoped_ptr<HistoryDBTask> task_;
  scoped_refptr<base::SingleThreadTaskRunner> origin_loop_;
  base::CancelableTaskTracker::IsCanceledCallback is_canceled_;

  DISALLOW_COPY_AND_ASSIGN(QueuedHistoryDBTask);
};

class HistoryBackend : public base::RefCountedThreadSafe<HistoryBackend>,
                       public BroadcastNotificationDelegate {
 public:
  
  
  
  
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    virtual void NotifyProfileError(sql::InitStatus init_status) = 0;

    
    
    
    
    
    
    
    virtual void SetInMemoryBackend(
        scoped_ptr<InMemoryHistoryBackend> backend) = 0;

    
    
    virtual void NotifyFaviconChanged(const std::set<GURL>& urls) = 0;

    
    
    
    
    virtual void BroadcastNotifications(int type,
                                        scoped_ptr<HistoryDetails> details) = 0;

    
    virtual void DBLoaded() = 0;

    virtual void NotifyVisitDBObserversOnAddVisit(
        const history::BriefVisitInfo& info) = 0;
  };

  
  
  
  
  
  
  
  
  
  
  
  
  HistoryBackend(const base::FilePath& history_dir,
                 Delegate* delegate,
                 HistoryClient* history_client);

  
  
  
  
  
  
  
  void Init(const std::string& languages, bool force_fail);

  
  
  
  void Closing();

  void ClearCachedDataForContextID(ContextID context_id);

  

  
  void AddPage(const HistoryAddPageArgs& request);
  virtual void SetPageTitle(const GURL& url, const base::string16& title);
  void AddPageNoVisitForBookmark(const GURL& url, const base::string16& title);
  void UpdateWithPageEndTime(ContextID context_id,
                             int32 page_id,
                             const GURL& url,
                             base::Time end_ts);

  

  
  
  
  
  void ScheduleAutocomplete(const base::Callback<
      void(history::HistoryBackend*, history::URLDatabase*)>& callback);

  void IterateURLs(
      const scoped_refptr<visitedlink::VisitedLinkDelegate::URLEnumerator>&
          enumerator);
  void QueryURL(const GURL& url,
                bool want_visits,
                QueryURLResult* query_url_result);
  void QueryHistory(const base::string16& text_query,
                    const QueryOptions& options,
                    QueryResults* query_results);

  
  
  
  
  
  void QueryRedirectsFrom(const GURL& url, RedirectList* redirects);

  
  
  
  
  void QueryRedirectsTo(const GURL& url, RedirectList* redirects);

  void GetVisibleVisitCountToHost(const GURL& url,
                                  VisibleVisitCountToHostResult* result);

  
  
  
  void QueryMostVisitedURLs(int result_count,
                            int days_back,
                            MostVisitedURLList* result);

  
  
  
  void QueryFilteredURLs(int result_count,
                         const history::VisitFilter& filter,
                         bool debug,
                         history::FilteredURLList* result);

  

  void GetFavicons(
      const std::vector<GURL>& icon_urls,
      int icon_types,
      const std::vector<int>& desired_sizes,
      std::vector<favicon_base::FaviconRawBitmapResult>* bitmap_results);

  void GetLargestFaviconForURL(
      const GURL& page_url,
      const std::vector<int>& icon_types,
      int minimum_size_in_pixels,
      favicon_base::FaviconRawBitmapResult* bitmap_result);

  void GetFaviconsForURL(
      const GURL& page_url,
      int icon_types,
      const std::vector<int>& desired_sizes,
      std::vector<favicon_base::FaviconRawBitmapResult>* bitmap_results);

  void GetFaviconForID(
      favicon_base::FaviconID favicon_id,
      int desired_size,
      std::vector<favicon_base::FaviconRawBitmapResult>* bitmap_results);

  void UpdateFaviconMappingsAndFetch(
      const GURL& page_url,
      const std::vector<GURL>& icon_urls,
      int icon_types,
      const std::vector<int>& desired_sizes,
      std::vector<favicon_base::FaviconRawBitmapResult>* bitmap_results);

  void MergeFavicon(const GURL& page_url,
                    const GURL& icon_url,
                    favicon_base::IconType icon_type,
                    scoped_refptr<base::RefCountedMemory> bitmap_data,
                    const gfx::Size& pixel_size);

  void SetFavicons(const GURL& page_url,
                   favicon_base::IconType icon_type,
                   const GURL& icon_url,
                   const std::vector<SkBitmap>& bitmaps);

  void SetFaviconsOutOfDateForPage(const GURL& page_url);

  void CloneFavicons(const GURL& old_page_url, const GURL& new_page_url);

  void SetImportedFavicons(
      const std::vector<ImportedFaviconUsage>& favicon_usage);

  

  uint32 GetNextDownloadId();
  void QueryDownloads(std::vector<DownloadRow>* rows);
  void UpdateDownload(const DownloadRow& data);
  bool CreateDownload(const history::DownloadRow& history_info);
  void RemoveDownloads(const std::set<uint32>& ids);

  

  void SetKeywordSearchTermsForURL(const GURL& url,
                                   KeywordID keyword_id,
                                   const base::string16& term);

  void DeleteAllSearchTermsForKeyword(KeywordID keyword_id);

  void DeleteKeywordSearchTermForURL(const GURL& url);

  void DeleteMatchingURLsForKeyword(KeywordID keyword_id,
                                    const base::string16& term);

#if defined(OS_ANDROID)
  

  
  
  AndroidURLID InsertHistoryAndBookmark(const HistoryAndBookmarkRow& row);

  
  
  
  
  
  
  history::AndroidStatement* QueryHistoryAndBookmarks(
      const std::vector<HistoryAndBookmarkRow::ColumnID>& projections,
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const std::string& sort_order);

  
  
  
  
  
  int UpdateHistoryAndBookmarks(
      const HistoryAndBookmarkRow& row,
      const std::string& selection,
      const std::vector<base::string16>& selection_args);

  
  
  
  
  
  
  int DeleteHistoryAndBookmarks(
      const std::string& selection,
      const std::vector<base::string16>& selection_args);

  
  int DeleteHistory(const std::string& selection,
                    const std::vector<base::string16>& selection_args);

  
  
  int MoveStatement(history::AndroidStatement* statement,
                    int current_pos,
                    int destination);

  
  void CloseStatement(AndroidStatement* statement);

  
  
  SearchTermID InsertSearchTerm(const SearchRow& row);

  
  
  
  
  
  int UpdateSearchTerms(const SearchRow& row,
                        const std::string& selection,
                        const std::vector<base::string16> selection_args);

  
  
  
  
  
  
  int DeleteSearchTerms(const std::string& selection,
                        const std::vector<base::string16> selection_args);

  
  
  
  
  
  
  history::AndroidStatement* QuerySearchTerms(
      const std::vector<SearchRow::ColumnID>& projections,
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const std::string& sort_order);

#endif  

  

  void ProcessDBTask(
      scoped_ptr<HistoryDBTask> task,
      scoped_refptr<base::SingleThreadTaskRunner> origin_loop,
      const base::CancelableTaskTracker::IsCanceledCallback& is_canceled);

  virtual bool GetAllTypedURLs(URLRows* urls);

  virtual bool GetVisitsForURL(URLID id, VisitVector* visits);

  
  virtual bool GetMostRecentVisitsForURL(URLID id,
                                         int max_visits,
                                         VisitVector* visits);

  
  
  
  virtual size_t UpdateURLs(const history::URLRows& urls);

  
  virtual bool AddVisits(const GURL& url,
                         const std::vector<history::VisitInfo>& visits,
                         VisitSource visit_source);

  virtual bool RemoveVisits(const VisitVector& visits);

  
  
  
  bool GetVisitsSource(const VisitVector& visits, VisitSourceMap* sources);

  virtual bool GetURL(const GURL& url, history::URLRow* url_row);

  
  
  virtual TypedUrlSyncableService* GetTypedUrlSyncableService() const;

  

  virtual void DeleteURLs(const std::vector<GURL>& urls);

  virtual void DeleteURL(const GURL& url);

  
  void ExpireHistoryBetween(
      const std::set<GURL>& restrict_urls,
      base::Time begin_time,
      base::Time end_time);

  
  
  
  
  
  void ExpireHistoryForTimes(const std::set<base::Time>& times,
                             base::Time begin_time, base::Time end_time);

  
  
  
  void ExpireHistory(const std::vector<ExpireHistoryArgs>& expire_list);

  

  
  
  void URLsNoLongerBookmarked(const std::set<GURL>& urls);

  

  
  
  void DatabaseErrorCallback(int error, sql::Statement* stmt);

  
  
  
  
  
  void KillHistoryDatabase();

  

  
  
  
  void SetOnBackendDestroyTask(base::MessageLoop* message_loop,
                               const base::Closure& task);

  
  
  
  
  void AddPagesWithDetails(const URLRows& info, VisitSource visit_source);

#if defined(UNIT_TEST)
  HistoryDatabase* db() const { return db_.get(); }

  ExpireHistoryBackend* expire_backend() { return &expirer_; }
#endif

  
  
  virtual bool IsExpiredVisitTime(const base::Time& time);

  base::Time GetFirstRecordedTimeForTest() {
    return first_recorded_time_;
  }

 protected:
  virtual ~HistoryBackend();

 private:
  friend class base::RefCountedThreadSafe<HistoryBackend>;
  friend class CommitLaterTask;  
  friend class HistoryBackendTest;
  friend class HistoryBackendDBTest;  
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, DeleteAll);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, DeleteAllThenAddData);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, AddPagesWithDetails);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, UpdateURLs);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, ImportedFaviconsTest);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, URLsNoLongerBookmarked);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, StripUsernamePasswordTest);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, DeleteThumbnailsDatabaseTest);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, AddPageVisitSource);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, AddPageVisitNotLastVisit);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           AddPageVisitFiresNotificationWithCorrectDetails);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, AddPageArgsSource);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, AddVisitsSource);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, GetMostRecentVisits);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, RemoveVisitsSource);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, RemoveVisitsTransitions);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, MigrationVisitSource);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           SetFaviconMappingsForPageAndRedirects);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           SetFaviconMappingsForPageDuplicates);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, SetFaviconsDeleteBitmaps);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, SetFaviconsReplaceBitmapData);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           SetFaviconsSameFaviconURLForTwoPages);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           UpdateFaviconMappingsAndFetchNoChange);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, MergeFaviconPageURLNotInDB);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, MergeFaviconPageURLInDB);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, MergeFaviconMaxFaviconsPerPage);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           MergeFaviconIconURLMappedToDifferentPageURL);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           MergeFaviconMaxFaviconBitmapsPerIconURL);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           UpdateFaviconMappingsAndFetchMultipleIconTypes);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, GetFaviconsFromDBEmpty);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           GetFaviconsFromDBNoFaviconBitmaps);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           GetFaviconsFromDBSelectClosestMatch);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, GetFaviconsFromDBIconType);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, GetFaviconsFromDBExpired);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           UpdateFaviconMappingsAndFetchNoDB);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest,
                           CloneFaviconIsRestrictedToSameDomain);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, QueryFilteredURLs);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, UpdateVisitDuration);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, ExpireHistoryForTimes);
  FRIEND_TEST_ALL_PREFIXES(HistoryBackendTest, DeleteFTSIndexDatabases);

  friend class ::TestingProfile;

  
  base::FilePath GetArchivedFileName() const;
  base::FilePath GetThumbnailFileName() const;

  
  
  base::FilePath GetFaviconsFileName() const;

#if defined(OS_ANDROID)
  
  base::FilePath GetAndroidCacheFileName() const;

  
  
  
  

  void PopulateMostVisitedURLMap();
  
  
  
  
  void RecordTopPageVisitStats(const GURL& url);
#endif

  class URLQuerier;
  friend class URLQuerier;

  
  void InitImpl(const std::string& languages);

  
  void OnMemoryPressure(
      base::MemoryPressureListener::MemoryPressureLevel memory_pressure_level);

  
  
  void CloseAllDatabases();

  
  
  
  
  
  
  
  std::pair<URLID, VisitID> AddPageVisit(const GURL& url,
                                         base::Time time,
                                         VisitID referring_visit,
                                         ui::PageTransition transition,
                                         VisitSource visit_source);

  
  
  
  void GetRedirectsFromSpecificVisit(
      VisitID cur_visit, history::RedirectList* redirects);

  
  
  void GetRedirectsToSpecificVisit(
      VisitID cur_visit, history::RedirectList* redirects);

  
  void UpdateVisitDuration(VisitID visit_id, const base::Time end_ts);

  

  
  
  
  
  
  void QueryHistoryBasic(const QueryOptions& options, QueryResults* result);
  void QueryHistoryText(const base::string16& text_query,
                        const QueryOptions& options,
                        QueryResults* result);

  

  
  
  
  
  
  
  void Commit();

  
  
  
  void ScheduleCommit();

  
  
  void CancelScheduledCommit();

  

  
  
  SegmentID GetLastSegmentID(VisitID from_visit);

  
  
  SegmentID UpdateSegments(const GURL& url,
                           VisitID from_visit,
                           VisitID visit_id,
                           ui::PageTransition transition_type,
                           const base::Time ts);

  

  
  
  
  
  
  
  
  
  void UpdateFaviconMappingsAndFetchImpl(
      const GURL* page_url,
      const std::vector<GURL>& icon_urls,
      int icon_types,
      const std::vector<int>& desired_sizes,
      std::vector<favicon_base::FaviconRawBitmapResult>* results);

  
  
  
  
  
  
  
  
  bool SetFaviconBitmaps(favicon_base::FaviconID icon_id,
                         const std::vector<SkBitmap>& bitmaps);

  
  bool IsFaviconBitmapDataEqual(
      FaviconBitmapID bitmap_id,
      const scoped_refptr<base::RefCountedMemory>& new_bitmap_data);

  
  
  
  
  
  
  
  
  
  
  
  bool GetFaviconsFromDB(
      const GURL& page_url,
      int icon_types,
      const std::vector<int>& desired_sizes,
      std::vector<favicon_base::FaviconRawBitmapResult>*
          favicon_bitmap_results);

  
  
  
  
  
  
  
  
  
  bool GetFaviconBitmapResultsForBestMatch(
      const std::vector<favicon_base::FaviconID>& candidate_favicon_ids,
      const std::vector<int>& desired_sizes,
      std::vector<favicon_base::FaviconRawBitmapResult>*
          favicon_bitmap_results);

  
  
  
  
  bool SetFaviconMappingsForPageAndRedirects(
      const GURL& page_url,
      favicon_base::IconType icon_type,
      const std::vector<favicon_base::FaviconID>& icon_ids);

  
  
  bool SetFaviconMappingsForPage(
      const GURL& page_url,
      favicon_base::IconType icon_type,
      const std::vector<favicon_base::FaviconID>& icon_ids);

  
  
  void GetCachedRecentRedirects(const GURL& page_url,
                                history::RedirectList* redirect_list);

  
  
  void SendFaviconChangedNotificationForPageAndRedirects(
      const GURL& page_url);

  

  
  
  void ProcessDBTaskImpl();

  virtual void BroadcastNotifications(
      int type,
      scoped_ptr<HistoryDetails> details) OVERRIDE;
  virtual void NotifySyncURLsModified(URLRows* rows) OVERRIDE;
  virtual void NotifySyncURLsDeleted(bool all_history,
                                     bool expired,
                                     URLRows* rows) OVERRIDE;

  

  
  
  
  
  
  
  void DeleteAllHistory();

  
  
  
  bool ClearAllThumbnailHistory(const URLRows& kept_urls);

  
  
  
  
  
  bool ClearAllMainHistory(const URLRows& kept_urls);

  
  void DeleteFTSIndexDatabases();

  
  
  HistoryClient* GetHistoryClient();

  
  void NotifyVisitObservers(const VisitRow& visit);

  

  
  
  
  scoped_ptr<Delegate> delegate_;

  
  base::FilePath history_dir_;

  
  
  
  
  scoped_ptr<HistoryDatabase> db_;
  bool scheduled_kill_db_;  
  scoped_ptr<ThumbnailDatabase> thumbnail_db_;

  
  ExpireHistoryBackend expirer_;

  
  
  
  
  scoped_refptr<CommitLaterTask> scheduled_commit_;

  
  
  
  
  
  
  
  
  
  typedef base::MRUCache<GURL, history::RedirectList> RedirectCache;
  RedirectCache recent_redirects_;

  
  base::Time first_recorded_time_;

  
  base::MessageLoop* backend_destroy_message_loop_;
  base::Closure backend_destroy_task_;

  
  VisitTracker tracker_;

  
  
  bool segment_queried_;

  
  std::list<QueuedHistoryDBTask*> queued_history_db_tasks_;

  
  
  
  
  HistoryClient* history_client_;

#if defined(OS_ANDROID)
  
  scoped_ptr<AndroidProviderBackend> android_provider_backend_;

  
  
  
  
  std::map<GURL, int> most_visited_urls_map_;
#endif

  
  
  scoped_ptr<TypedUrlSyncableService> typed_url_syncable_service_;

  
  scoped_ptr<base::MemoryPressureListener> memory_pressure_listener_;

  DISALLOW_COPY_AND_ASSIGN(HistoryBackend);
};

}  

#endif  
