// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_HISTORY_SERVICE_H_
#define CHROME_BROWSER_HISTORY_HISTORY_SERVICE_H_

#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/bind.h"
#include "base/callback.h"
#include "base/callback_list.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "chrome/browser/history/delete_directive_handler.h"
#include "chrome/browser/history/typed_url_syncable_service.h"
#include "chrome/common/ref_counted_util.h"
#include "components/favicon_base/favicon_callback.h"
#include "components/history/core/browser/history_client.h"
#include "components/history/core/browser/keyword_id.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/visitedlink/browser/visitedlink_delegate.h"
#include "content/public/browser/download_manager_delegate.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "sql/init_status.h"
#include "sync/api/syncable_service.h"
#include "ui/base/page_transition_types.h"

#if defined(OS_ANDROID)
class AndroidHistoryProviderService;
#endif

class GURL;
class PageUsageData;
class PageUsageRequest;
class Profile;
struct ImportedFaviconUsage;
class SkBitmap;

namespace base {
class FilePath;
class Thread;
}

namespace visitedlink {
class VisitedLinkMaster;
}

namespace history {

class HistoryBackend;
class HistoryClient;
class HistoryDatabase;
class HistoryDBTask;
class HistoryQueryTest;
class HistoryTest;
class InMemoryHistoryBackend;
class InMemoryURLIndex;
class InMemoryURLIndexTest;
class URLDatabase;
class VisitDatabaseObserver;
class VisitFilter;
struct DownloadRow;
struct HistoryAddPageArgs;
struct HistoryDetails;
struct KeywordSearchTermVisit;

}  

class HistoryService : public content::NotificationObserver,
                       public syncer::SyncableService,
                       public KeyedService,
                       public visitedlink::VisitedLinkDelegate {
 public:
  
  typedef std::vector<PageUsageData*> PageUsageDataList;

  
  
  explicit HistoryService(history::HistoryClient* client, Profile* profile);
  
  HistoryService();

  virtual ~HistoryService();

  
  
  
  bool Init(const base::FilePath& history_dir) {
    return Init(history_dir, false);
  }

  
  
  
  virtual bool BackendLoaded();

  
  bool backend_loaded() const { return backend_loaded_; }

  
  
  
  void ClearCachedDataForContextID(history::ContextID context_id);

  
  
  
  
  
  
  history::URLDatabase* InMemoryDatabase();

  
  
  

  
  bool GetTypedCountForURL(const GURL& url, int* typed_count);

  
  bool GetLastVisitTimeForURL(const GURL& url, base::Time* last_visit);

  
  bool GetVisitCountForURL(const GURL& url, int* visit_count);

  
  
  
  history::TypedUrlSyncableService* GetTypedUrlSyncableService() const;

  
  history::InMemoryURLIndex* InMemoryIndex() const {
    return in_memory_url_index_.get();
  }

  
  virtual void Shutdown() OVERRIDE;

  

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void AddPage(const GURL& url,
               base::Time time,
               history::ContextID context_id,
               int32 page_id,
               const GURL& referrer,
               const history::RedirectList& redirects,
               ui::PageTransition transition,
               history::VisitSource visit_source,
               bool did_replace_entry);

  
  void AddPage(const GURL& url,
               base::Time time,
               history::VisitSource visit_source);

  
  void AddPage(const history::HistoryAddPageArgs& add_page_args);

  
  
  
  void AddPageNoVisitForBookmark(const GURL& url, const base::string16& title);

  
  
  void SetPageTitle(const GURL& url, const base::string16& title);

  
  
  
  void UpdateWithPageEndTime(history::ContextID context_id,
                             int32 page_id,
                             const GURL& url,
                             base::Time end_ts);

  

  
  
  
  
  
  
  
  typedef base::Callback<
      void(bool,  
           const history::URLRow&,
           const history::VisitVector&)> QueryURLCallback;

  
  
  
  
  base::CancelableTaskTracker::TaskId QueryURL(
      const GURL& url,
      bool want_visits,
      const QueryURLCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  typedef base::Callback<void(history::QueryResults*)> QueryHistoryCallback;

  
  
  
  base::CancelableTaskTracker::TaskId QueryHistory(
      const base::string16& text_query,
      const history::QueryOptions& options,
      const QueryHistoryCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  
  
  
  
  typedef base::Callback<void(const history::RedirectList*)>
      QueryRedirectsCallback;

  
  
  
  base::CancelableTaskTracker::TaskId QueryRedirectsFrom(
      const GURL& from_url,
      const QueryRedirectsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  base::CancelableTaskTracker::TaskId QueryRedirectsTo(
      const GURL& to_url,
      const QueryRedirectsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  typedef base::Callback<
      void(bool,         
           int,          
           base::Time)>  
                         
      GetVisibleVisitCountToHostCallback;

  base::CancelableTaskTracker::TaskId GetVisibleVisitCountToHost(
      const GURL& url,
      const GetVisibleVisitCountToHostCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  typedef base::Callback<void(const history::MostVisitedURLList*)>
      QueryMostVisitedURLsCallback;

  base::CancelableTaskTracker::TaskId QueryMostVisitedURLs(
      int result_count,
      int days_back,
      const QueryMostVisitedURLsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  typedef base::Callback<void(const history::FilteredURLList*)>
      QueryFilteredURLsCallback;

  base::CancelableTaskTracker::TaskId QueryFilteredURLs(
      int result_count,
      const history::VisitFilter& filter,
      bool extended_info,
      const QueryFilteredURLsCallback& callback,
      base::CancelableTaskTracker* tracker);

  

  
  void DeleteURL(const GURL& url);

  
  
  void DeleteURLsForTest(const std::vector<GURL>& urls);

  
  
  
  
  
  
  
  
  void ExpireHistoryBetween(const std::set<GURL>& restrict_urls,
                            base::Time begin_time,
                            base::Time end_time,
                            const base::Closure& callback,
                            base::CancelableTaskTracker* tracker);

  
  
  
  
  void ExpireHistory(const std::vector<history::ExpireHistoryArgs>& expire_list,
                     const base::Closure& callback,
                     base::CancelableTaskTracker* tracker);

  
  
  
  void ExpireLocalAndRemoteHistoryBetween(const std::set<GURL>& restrict_urls,
                                          base::Time begin_time,
                                          base::Time end_time,
                                          const base::Closure& callback,
                                          base::CancelableTaskTracker* tracker);

  
  
  
  syncer::SyncError ProcessLocalDeleteDirective(
      const sync_pb::HistoryDeleteDirectiveSpecifics& delete_directive);

  

  
  
  typedef base::Callback<void(bool)> DownloadCreateCallback;

  
  
  
  
  void CreateDownload(
      const history::DownloadRow& info,
      const DownloadCreateCallback& callback);

  
  
  void GetNextDownloadId(const content::DownloadIdCallback& callback);

  
  
  typedef base::Callback<void(
      scoped_ptr<std::vector<history::DownloadRow> >)>
          DownloadQueryCallback;

  
  
  
  
  void QueryDownloads(const DownloadQueryCallback& callback);

  
  
  
  void UpdateDownload(const history::DownloadRow& data);

  
  
  void RemoveDownloads(const std::set<uint32>& ids);

  

  
  
  void SetKeywordSearchTermsForURL(const GURL& url,
                                   history::KeywordID keyword_id,
                                   const base::string16& term);

  
  void DeleteAllSearchTermsForKeyword(history::KeywordID keyword_id);

  
  void DeleteKeywordSearchTermForURL(const GURL& url);

  
  
  void DeleteMatchingURLsForKeyword(history::KeywordID keyword_id,
                                    const base::string16& term);

  

  
  void URLsNoLongerBookmarked(const std::set<GURL>& urls);

  

  
  
  virtual void ScheduleDBTask(scoped_ptr<history::HistoryDBTask> task,
                              base::CancelableTaskTracker* tracker);

  
  void AddVisitDatabaseObserver(history::VisitDatabaseObserver* observer);
  void RemoveVisitDatabaseObserver(history::VisitDatabaseObserver* observer);

  void NotifyVisitDBObserversOnAddVisit(const history::BriefVisitInfo& info);

  
  typedef base::Callback<void(const std::set<GURL>&)> OnFaviconChangedCallback;

  
  
  
  scoped_ptr<base::CallbackList<void(const std::set<GURL>&)>::Subscription>
      AddFaviconChangedCallback(const OnFaviconChangedCallback& callback)
      WARN_UNUSED_RESULT;

  

  
  void FlushForTest(const base::Closure& flushed);

  
  
  
  
  
  
  
  
  
  void SetOnBackendDestroyTask(const base::Closure& task);

  
  
  
  
  
  
  
  
  
  
  
  void AddPageWithDetails(const GURL& url,
                          const base::string16& title,
                          int visit_count,
                          int typed_count,
                          base::Time last_visit,
                          bool hidden,
                          history::VisitSource visit_source);

  
  void AddPagesWithDetails(const history::URLRows& info,
                           history::VisitSource visit_source);

  
  
  static bool CanAddURL(const GURL& url);

  
  history::HistoryClient* history_client() { return history_client_; }

  base::WeakPtr<HistoryService> AsWeakPtr();

  
  virtual syncer::SyncMergeResult MergeDataAndStartSyncing(
      syncer::ModelType type,
      const syncer::SyncDataList& initial_sync_data,
      scoped_ptr<syncer::SyncChangeProcessor> sync_processor,
      scoped_ptr<syncer::SyncErrorFactory> error_handler) OVERRIDE;
  virtual void StopSyncing(syncer::ModelType type) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(
      syncer::ModelType type) const OVERRIDE;
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;

 protected:
  
  
  enum SchedulePriority {
    PRIORITY_UI,      
    PRIORITY_NORMAL,  
    PRIORITY_LOW,     
  };

 private:
  class BackendDelegate;
#if defined(OS_ANDROID)
  friend class AndroidHistoryProviderService;
#endif
  friend class base::RefCountedThreadSafe<HistoryService>;
  friend class BackendDelegate;
  friend class FaviconService;
  friend class history::HistoryBackend;
  friend class history::HistoryQueryTest;
  friend class HistoryOperation;
  friend class HistoryQuickProviderTest;
  friend class history::HistoryTest;
  friend class HistoryURLProvider;
  friend class HistoryURLProviderTest;
  friend class history::InMemoryURLIndexTest;
  template<typename Info, typename Callback> friend class DownloadRequest;
  friend class PageUsageRequest;
  friend class RedirectRequest;
  friend class TestingProfile;

  
  
  
  
  
  
  
  
  
  void Cleanup();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void RebuildTable(
      const scoped_refptr<URLEnumerator>& enumerator) OVERRIDE;

  
  
  bool Init(const base::FilePath& history_dir, bool no_db);

  
  
  
  void ScheduleAutocomplete(const base::Callback<
      void(history::HistoryBackend*, history::URLDatabase*)>& callback);

  
  
  void BroadcastNotificationsHelper(
      int type,
      scoped_ptr<history::HistoryDetails> details);

  
  
  void OnDBLoaded();

  
  
  
  bool GetRowForURL(const GURL& url, history::URLRow* url_row);

  

  
  
  

  
  
  
  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetFavicons(
      const std::vector<GURL>& icon_urls,
      int icon_types,
      const std::vector<int>& desired_sizes,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetFaviconsForURL(
      const GURL& page_url,
      int icon_types,
      const std::vector<int>& desired_sizes,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetLargestFaviconForURL(
      const GURL& page_url,
      const std::vector<int>& icon_types,
      int minimum_size_in_pixels,
      const favicon_base::FaviconRawBitmapCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  base::CancelableTaskTracker::TaskId GetFaviconForID(
      favicon_base::FaviconID favicon_id,
      int desired_size,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId UpdateFaviconMappingsAndFetch(
      const GURL& page_url,
      const std::vector<GURL>& icon_urls,
      int icon_types,
      const std::vector<int>& desired_sizes,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
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

  
  
  // discarded. Existing favicons will not be overwritten.
  void SetImportedFavicons(
      const std::vector<ImportedFaviconUsage>& favicon_usage);

  
  
  void SetInMemoryBackend(
      scoped_ptr<history::InMemoryHistoryBackend> mem_backend);

  
  void NotifyProfileError(sql::InitStatus init_status);

  
  
  void ScheduleTask(SchedulePriority priority, const base::Closure& task);

  
  void NotifyFaviconChanged(const std::set<GURL>& changed_favicons);

  
  
  
  

  template<typename BackendFunc>
  void ScheduleAndForget(SchedulePriority priority,
                         BackendFunc func) {  
    DCHECK(thread_) << "History service being called after cleanup";
    DCHECK(thread_checker_.CalledOnValidThread());
    ScheduleTask(priority, base::Bind(func, history_backend_.get()));
  }

  template<typename BackendFunc, typename ArgA>
  void ScheduleAndForget(SchedulePriority priority,
                         BackendFunc func,  
                         const ArgA& a) {
    DCHECK(thread_) << "History service being called after cleanup";
    DCHECK(thread_checker_.CalledOnValidThread());
    ScheduleTask(priority, base::Bind(func, history_backend_.get(), a));
  }

  template<typename BackendFunc, typename ArgA, typename ArgB>
  void ScheduleAndForget(SchedulePriority priority,
                         BackendFunc func,  
                         const ArgA& a,
                         const ArgB& b) {
    DCHECK(thread_) << "History service being called after cleanup";
    DCHECK(thread_checker_.CalledOnValidThread());
    ScheduleTask(priority, base::Bind(func, history_backend_.get(), a, b));
  }

  template<typename BackendFunc, typename ArgA, typename ArgB, typename ArgC>
  void ScheduleAndForget(SchedulePriority priority,
                         BackendFunc func,  
                         const ArgA& a,
                         const ArgB& b,
                         const ArgC& c) {
    DCHECK(thread_) << "History service being called after cleanup";
    DCHECK(thread_checker_.CalledOnValidThread());
    ScheduleTask(priority, base::Bind(func, history_backend_.get(), a, b, c));
  }

  template<typename BackendFunc,
           typename ArgA,
           typename ArgB,
           typename ArgC,
           typename ArgD>
  void ScheduleAndForget(SchedulePriority priority,
                         BackendFunc func,  
                         const ArgA& a,
                         const ArgB& b,
                         const ArgC& c,
                         const ArgD& d) {
    DCHECK(thread_) << "History service being called after cleanup";
    DCHECK(thread_checker_.CalledOnValidThread());
    ScheduleTask(priority, base::Bind(func, history_backend_.get(),
                                      a, b, c, d));
  }

  template<typename BackendFunc,
           typename ArgA,
           typename ArgB,
           typename ArgC,
           typename ArgD,
           typename ArgE>
  void ScheduleAndForget(SchedulePriority priority,
                         BackendFunc func,  
                         const ArgA& a,
                         const ArgB& b,
                         const ArgC& c,
                         const ArgD& d,
                         const ArgE& e) {
    DCHECK(thread_) << "History service being called after cleanup";
    DCHECK(thread_checker_.CalledOnValidThread());
    ScheduleTask(priority, base::Bind(func, history_backend_.get(),
                                      a, b, c, d, e));
  }

  base::ThreadChecker thread_checker_;

  content::NotificationRegistrar registrar_;

  
  
  base::Thread* thread_;

  
  
  
  
  
  
  scoped_refptr<history::HistoryBackend> history_backend_;

  
  
  
  
  scoped_ptr<history::InMemoryHistoryBackend> in_memory_backend_;

  
  
  history::HistoryClient* history_client_;

  
  Profile* profile_;

  
  
  scoped_ptr<visitedlink::VisitedLinkMaster> visitedlink_master_;

  
  
  bool backend_loaded_;

  
  base::FilePath history_dir_;
  bool no_db_;

  
  
  
  scoped_ptr<history::InMemoryURLIndex> in_memory_url_index_;

  ObserverList<history::VisitDatabaseObserver> visit_database_observers_;

  base::CallbackList<void(const std::set<GURL>&)>
      favicon_changed_callback_list_;

  history::DeleteDirectiveHandler delete_directive_handler_;

  
  base::WeakPtrFactory<HistoryService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HistoryService);
};

#endif  
