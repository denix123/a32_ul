// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRERENDER_PRERENDER_MANAGER_H_
#define CHROME_BROWSER_PRERENDER_PRERENDER_MANAGER_H_

#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chrome/browser/history/history_service.h"
#include "chrome/browser/media/media_capture_devices_dispatcher.h"
#include "chrome/browser/predictors/logged_in_predictor_table.h"
#include "chrome/browser/prerender/prerender_config.h"
#include "chrome/browser/prerender/prerender_contents.h"
#include "chrome/browser/prerender/prerender_events.h"
#include "chrome/browser/prerender/prerender_final_status.h"
#include "chrome/browser/prerender/prerender_histograms.h"
#include "chrome/browser/prerender/prerender_origin.h"
#include "chrome/browser/prerender/prerender_tracker.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/render_process_host_observer.h"
#include "content/public/browser/session_storage_namespace.h"
#include "content/public/browser/web_contents_observer.h"
#include "net/cookies/canonical_cookie.h"
#include "net/cookies/cookie_monster.h"
#include "url/gurl.h"

class Profile;
class InstantSearchPrerendererTest;
struct ChromeCookieDetails;

namespace base {
class DictionaryValue;
}

namespace chrome {
struct NavigateParams;
}

namespace content {
class WebContents;
}

namespace gfx {
class Size;
}

namespace net {
class URLRequestContextGetter;
}

namespace prerender {

class PrerenderHandle;
class PrerenderHistory;
class PrerenderLocalPredictor;

class PrerenderManager : public base::SupportsWeakPtr<PrerenderManager>,
                         public base::NonThreadSafe,
                         public content::NotificationObserver,
                         public content::RenderProcessHostObserver,
                         public KeyedService,
                         public MediaCaptureDevicesDispatcher::Observer {
 public:
  
  enum PrerenderManagerMode {
    PRERENDER_MODE_DISABLED = 0,
    PRERENDER_MODE_ENABLED = 1,
    PRERENDER_MODE_EXPERIMENT_CONTROL_GROUP = 2,
    PRERENDER_MODE_EXPERIMENT_PRERENDER_GROUP = 3,
    
    PRERENDER_MODE_EXPERIMENT_NO_USE_GROUP = 5,
    PRERENDER_MODE_EXPERIMENT_MULTI_PRERENDER_GROUP = 6,
    PRERENDER_MODE_EXPERIMENT_15MIN_TTL_GROUP = 7,
    PRERENDER_MODE_EXPERIMENT_MATCH_COMPLETE_GROUP = 8,
    PRERENDER_MODE_MAX
  };

  
  
  enum ClearFlags {
    CLEAR_PRERENDER_CONTENTS = 0x1 << 0,
    CLEAR_PRERENDER_HISTORY = 0x1 << 1,
    CLEAR_MAX = 0x1 << 2
  };

  typedef predictors::LoggedInPredictorTable::LoggedInStateMap LoggedInStateMap;

  
  static const uint8 kNoExperiment = 0;

  
  PrerenderManager(Profile* profile, PrerenderTracker* prerender_tracker);

  virtual ~PrerenderManager();

  
  virtual void Shutdown() OVERRIDE;

  

  
  
  
  
  
  
  PrerenderHandle* AddPrerenderFromLinkRelPrerender(
      int process_id,
      int route_id,
      const GURL& url,
      uint32 rel_types,
      const content::Referrer& referrer,
      const gfx::Size& size);

  
  
  
  
  
  
  PrerenderHandle* AddPrerenderFromOmnibox(
      const GURL& url,
      content::SessionStorageNamespace* session_storage_namespace,
      const gfx::Size& size);

  PrerenderHandle* AddPrerenderFromLocalPredictor(
      const GURL& url,
      content::SessionStorageNamespace* session_storage_namespace,
      const gfx::Size& size);

  PrerenderHandle* AddPrerenderFromExternalRequest(
      const GURL& url,
      const content::Referrer& referrer,
      content::SessionStorageNamespace* session_storage_namespace,
      const gfx::Size& size);

  
  
  
  
  PrerenderHandle* AddPrerenderForInstant(
      const GURL& url,
      content::SessionStorageNamespace* session_storage_namespace,
      const gfx::Size& size);

  
  void CancelAllPrerenders();

  
  
  
  
  bool MaybeUsePrerenderedPage(const GURL& url,
                               chrome::NavigateParams* params);

  
  
  virtual void MoveEntryToPendingDelete(PrerenderContents* entry,
                                        FinalStatus final_status);

  
  void RecordPageLoadTimeNotSwappedIn(Origin origin,
                                      base::TimeDelta page_load_time,
                                      const GURL& url);

  
  
  
  
  
  
  void RecordPerceivedPageLoadTime(
      Origin origin,
      NavigationType navigation_type,
      base::TimeDelta perceived_page_load_time,
      double fraction_plt_elapsed_at_swap_in,
      const GURL& url);

  static PrerenderManagerMode GetMode();
  static void SetMode(PrerenderManagerMode mode);
  static const char* GetModeString();
  static bool IsPrerenderingPossible();
  static bool ActuallyPrerendering();
  static bool IsControlGroup(uint8 experiment_id);
  static bool IsNoUseGroup();

  
  
  
  
  bool IsWebContentsPrerendering(const content::WebContents* web_contents,
                                 Origin* origin) const;

  
  
  bool HasPrerenderedUrl(GURL url, content::WebContents* web_contents) const;

  
  
  
  PrerenderContents* GetPrerenderContents(
      const content::WebContents* web_contents) const;

  
  
  
  virtual PrerenderContents* GetPrerenderContentsForRoute(
      int child_id, int route_id) const;

  
  const std::vector<content::WebContents*> GetAllPrerenderingContents() const;

  
  bool HasRecentlyBeenNavigatedTo(Origin origin, const GURL& url);

  
  static bool IsValidHttpMethod(const std::string& method);

  
  static bool DoesURLHaveValidScheme(const GURL& url);

  
  
  static bool DoesSubresourceURLHaveValidScheme(const GURL& url);

  
  
  
  base::DictionaryValue* GetAsValue() const;

  
  
  
  
  
  
  
  
  
  
  
  void ClearData(int clear_flags);

  
  
  
  void RecordFinalStatusWithMatchCompleteStatus(
      Origin origin,
      uint8 experiment_id,
      PrerenderContents::MatchCompleteStatus mc_status,
      FinalStatus final_status) const;

  
  void RecordCookieStatus(Origin origin,
                          uint8 experiment_id,
                          int cookie_status) const;

  
  void RecordCookieSendType(Origin origin,
                            uint8 experiment_id,
                            int cookie_send_type) const;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnCreatingAudioStream(int render_process_id,
                                     int render_frame_id) OVERRIDE;

  const Config& config() const { return config_; }
  Config& mutable_config() { return config_; }

  PrerenderTracker* prerender_tracker() { return prerender_tracker_; }

  bool cookie_store_loaded() { return cookie_store_loaded_; }

  
  
  void RecordNavigation(const GURL& url);

  
  
  void RecordLikelyLoginOnURL(const GURL& url);

  
  
  void CheckIfLikelyLoggedInOnURL(const GURL& url,
                                  bool* lookup_result,
                                  bool* database_was_present,
                                  const base::Closure& result_cb);

  void OnHistoryServiceDidQueryURL(Origin origin,
                                   uint8 experiment_id,
                                   bool success,
                                   const history::URLRow& url_row,
                                   const history::VisitVector& visits);

  Profile* profile() const { return profile_; }

  
  
  
  virtual base::Time GetCurrentTime() const;
  virtual base::TimeTicks GetCurrentTimeTicks() const;

  scoped_refptr<predictors::LoggedInPredictorTable>
  logged_in_predictor_table() {
    return logged_in_predictor_table_;
  }

  PrerenderLocalPredictor* local_predictor() {
    return local_predictor_.get();
  }

  
  
  
  static void RecordCookieEvent(int process_id,
                                int frame_id,
                                const GURL& url,
                                const GURL& frame_url,
                                bool is_for_blocking_resource,
                                PrerenderContents::CookieEvent event,
                                const net::CookieList* cookie_list);

  
  
  static void HangSessionStorageMergesForTesting();

  
  
  void RecordNetworkBytes(Origin origin, bool used, int64 prerender_bytes);

  
  bool IsEnabled() const;

  
  
  void AddProfileNetworkBytesIfEnabled(int64 bytes);

  
  
  void AddPrerenderProcessHost(content::RenderProcessHost* process_host);

  
  
  
  bool MayReuseProcessHost(content::RenderProcessHost* process_host);

  
  virtual void RenderProcessHostDestroyed(
      content::RenderProcessHost* host) OVERRIDE;

  
  void OnCookieStoreLoaded();

  
  
  void set_on_cookie_store_loaded_cb_for_testing(base::Closure cb) {
    on_cookie_store_loaded_cb_for_testing_ = cb;
  }

 protected:
  class PendingSwap;
  class PrerenderData : public base::SupportsWeakPtr<PrerenderData> {
   public:
    struct OrderByExpiryTime;

    PrerenderData(PrerenderManager* manager,
                  PrerenderContents* contents,
                  base::TimeTicks expiry_time);

    ~PrerenderData();

    
    
    void MakeIntoMatchCompleteReplacement();

    
    void OnHandleCreated(PrerenderHandle* prerender_handle);

    
    
    
    
    void OnHandleNavigatedAway(PrerenderHandle* prerender_handle);

    
    
    
    void OnHandleCanceled(PrerenderHandle* prerender_handle);

    PrerenderContents* contents() { return contents_.get(); }

    PrerenderContents* ReleaseContents();

    int handle_count() const { return handle_count_; }

    base::TimeTicks abandon_time() const { return abandon_time_; }

    base::TimeTicks expiry_time() const { return expiry_time_; }
    void set_expiry_time(base::TimeTicks expiry_time) {
      expiry_time_ = expiry_time;
    }

    void ClearPendingSwap();

    PendingSwap* pending_swap() { return pending_swap_.get(); }
    void set_pending_swap(PendingSwap* pending_swap) {
      pending_swap_.reset(pending_swap);
    }

   private:
    PrerenderManager* manager_;
    scoped_ptr<PrerenderContents> contents_;

    
    
    
    
    
    int handle_count_;

    
    base::TimeTicks abandon_time_;

    
    
    base::TimeTicks expiry_time_;

    
    
    scoped_ptr<PendingSwap> pending_swap_;

    DISALLOW_COPY_AND_ASSIGN(PrerenderData);
  };

  
  
  
  
  
  class PendingSwap : public content::WebContentsObserver {
   public:
    PendingSwap(PrerenderManager* manager,
                content::WebContents* target_contents,
                PrerenderData* prerender_data,
                const GURL& url,
                bool should_replace_current_entry);
    virtual ~PendingSwap();

    void set_swap_successful(bool swap_successful) {
      swap_successful_ = swap_successful;
    }

    void BeginSwap();

    
    virtual void AboutToNavigateRenderView(
        content::RenderViewHost* render_view_host) OVERRIDE;
    virtual void DidStartProvisionalLoadForFrame(
        content::RenderFrameHost* render_frame_host,
        const GURL& validated_url,
        bool is_error_page,
        bool is_iframe_srcdoc) OVERRIDE;
    virtual void DidCommitProvisionalLoadForFrame(
        content::RenderFrameHost* render_frame_host,
        const GURL& validated_url,
        ui::PageTransition transition_type) OVERRIDE;
    virtual void DidFailProvisionalLoad(
        content::RenderFrameHost* render_frame_host,
        const GURL& validated_url,
        int error_code,
        const base::string16& error_description) OVERRIDE;
    virtual void WebContentsDestroyed() OVERRIDE;

   private:
    void RecordEvent(PrerenderEvent event) const;

    void OnMergeCompleted(content::SessionStorageNamespace::MergeResult result);
    void OnMergeTimeout();

    
    PrerenderManager* manager_;
    PrerenderData* prerender_data_;
    GURL url_;
    bool should_replace_current_entry_;

    base::TimeTicks start_time_;
    PrerenderTracker::ChildRouteIdPair target_route_id_;
    bool seen_target_route_id_;
    base::OneShotTimer<PendingSwap> merge_timeout_;
    bool swap_successful_;

    base::WeakPtrFactory<PendingSwap> weak_factory_;
  };

  void SetPrerenderContentsFactory(
      PrerenderContents::Factory* prerender_contents_factory);

  
  
  
  
  
  void SourceNavigatedAway(PrerenderData* prerender_data);

  
  
  
  virtual net::URLRequestContextGetter* GetURLRequestContext();

 private:
  friend class ::InstantSearchPrerendererTest;
  friend class PrerenderBrowserTest;
  friend class PrerenderContents;
  friend class PrerenderHandle;
  friend class UnitTestPrerenderManager;

  class OnCloseWebContentsDeleter;
  struct NavigationRecord;

  
  static const int kMinTimeBetweenPrerendersMs = 500;

  
  static const int kNavigationRecordWindowMs = 5000;

  void OnCancelPrerenderHandle(PrerenderData* prerender_data);

  
  
  
  
  
  PrerenderHandle* AddPrerender(
      Origin origin,
      int child_id,
      const GURL& url,
      const content::Referrer& referrer,
      const gfx::Size& size,
      content::SessionStorageNamespace* session_storage_namespace);

  void StartSchedulingPeriodicCleanups();
  void StopSchedulingPeriodicCleanups();

  void EvictOldestPrerendersIfNecessary();

  
  
  
  
  void PeriodicCleanup();

  
  
  
  void PostCleanupTask();

  base::TimeTicks GetExpiryTimeForNewPrerender(Origin origin) const;
  base::TimeTicks GetExpiryTimeForNavigatedAwayPrerender() const;

  void DeleteOldEntries();
  virtual PrerenderContents* CreatePrerenderContents(
      const GURL& url,
      const content::Referrer& referrer,
      Origin origin,
      uint8 experiment_id);

  
  
  
  void SortActivePrerenders();

  
  
  PrerenderData* FindPrerenderData(
      const GURL& url,
      const content::SessionStorageNamespace* session_storage_namespace);

  
  
  PrerenderData* FindPrerenderDataForTargetContents(
      content::WebContents* target_contents);

  
  
  ScopedVector<PrerenderData>::iterator
      FindIteratorForPrerenderContents(PrerenderContents* prerender_contents);

  bool DoesRateLimitAllowPrerender(Origin origin) const;

  
  
  
  void DeleteOldWebContents();

  
  void CleanUpOldNavigations();

  
  
  void ScheduleDeleteOldWebContents(content::WebContents* tab,
                                    OnCloseWebContentsDeleter* deleter);

  
  void AddToHistory(PrerenderContents* contents);

  
  
  base::Value* GetActivePrerendersAsValue() const;

  
  
  
  void DestroyAllContents(FinalStatus final_status);

  
  
  
  void DestroyAndMarkMatchCompleteAsUsed(PrerenderContents* prerender_contents,
                                         FinalStatus final_status);

  
  
  
  
  void RecordFinalStatusWithoutCreatingPrerenderContents(
      const GURL& url, Origin origin, uint8 experiment_id,
      FinalStatus final_status) const;


  void CookieChanged(ChromeCookieDetails* details);
  void CookieChangedAnyCookiesLeftLookupResult(const std::string& domain_key,
                                               bool cookies_exist);
  void LoggedInPredictorDataReceived(scoped_ptr<LoggedInStateMap> new_map);

  void RecordEvent(PrerenderContents* contents, PrerenderEvent event) const;

  
  
  
  
  content::WebContents* SwapInternal(const GURL& url,
                                     content::WebContents* web_contents,
                                     PrerenderData* prerender_data,
                                     bool should_replace_current_entry);

  
  Config config_;

  
  Profile* profile_;

  PrerenderTracker* prerender_tracker_;

  
  ScopedVector<PrerenderData> active_prerenders_;

  
  ScopedVector<PrerenderData> to_delete_prerenders_;

  
  
  std::list<NavigationRecord> navigations_;

  scoped_ptr<PrerenderContents::Factory> prerender_contents_factory_;

  static PrerenderManagerMode mode_;

  
  
  static int prerenders_per_session_count_;

  
  
  base::RepeatingTimer<PrerenderManager> repeating_timer_;

  
  base::TimeTicks last_prerender_start_time_;

  std::list<content::WebContents*> old_web_contents_list_;

  ScopedVector<OnCloseWebContentsDeleter> on_close_web_contents_deleters_;

  scoped_ptr<PrerenderHistory> prerender_history_;

  scoped_ptr<PrerenderHistograms> histograms_;

  scoped_ptr<PrerenderLocalPredictor> local_predictor_;

  scoped_refptr<predictors::LoggedInPredictorTable> logged_in_predictor_table_;

  
  
  
  
  
  
  scoped_ptr<LoggedInStateMap> logged_in_state_;

  content::NotificationRegistrar notification_registrar_;

  base::CancelableTaskTracker query_url_tracker_;

  
  
  int64 profile_network_bytes_;

  
  int64 last_recorded_profile_network_bytes_;

  
  typedef std::set<content::RenderProcessHost*> PrerenderProcessSet;
  PrerenderProcessSet prerender_process_hosts_;

  
  bool cookie_store_loaded_;

  base::Closure on_cookie_store_loaded_cb_for_testing_;

  DISALLOW_COPY_AND_ASSIGN(PrerenderManager);
};

}  

#endif  
