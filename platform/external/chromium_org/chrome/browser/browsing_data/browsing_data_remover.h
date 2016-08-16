// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_REMOVER_H_
#define CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_REMOVER_H_

#include <set>

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "base/prefs/pref_member.h"
#include "base/sequenced_task_runner_helpers.h"
#include "base/synchronization/waitable_event_watcher.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/time/time.h"
#include "chrome/browser/pepper_flash_settings_manager.h"
#include "components/search_engines/template_url_service.h"
#if defined(OS_CHROMEOS)
#include "chromeos/dbus/dbus_method_call_status.h"
#endif
#include "storage/common/quota/quota_types.h"
#include "url/gurl.h"

class ExtensionSpecialStoragePolicy;
class IOThread;
class Profile;

namespace chrome_browser_net {
class Predictor;
}

namespace content {
class PluginDataRemover;
class StoragePartition;
}

namespace disk_cache {
class Backend;
}

namespace net {
class URLRequestContextGetter;
}

namespace storage {
class QuotaManager;
}

namespace content {
class DOMStorageContext;
struct LocalStorageUsageInfo;
struct SessionStorageUsageInfo;
}


class BrowsingDataRemover
#if defined(ENABLE_PLUGINS)
    : public PepperFlashSettingsManager::Client
#endif
    {
 public:
  
  enum TimePeriod {
    LAST_HOUR = 0,
    LAST_DAY,
    LAST_WEEK,
    FOUR_WEEKS,
    EVERYTHING
  };

  
  enum RemoveDataMask {
    REMOVE_APPCACHE = 1 << 0,
    REMOVE_CACHE = 1 << 1,
    REMOVE_COOKIES = 1 << 2,
    REMOVE_DOWNLOADS = 1 << 3,
    REMOVE_FILE_SYSTEMS = 1 << 4,
    REMOVE_FORM_DATA = 1 << 5,
    
    REMOVE_HISTORY = 1 << 6,
    REMOVE_INDEXEDDB = 1 << 7,
    REMOVE_LOCAL_STORAGE = 1 << 8,
    REMOVE_PLUGIN_DATA = 1 << 9,
    REMOVE_PASSWORDS = 1 << 10,
    REMOVE_WEBSQL = 1 << 11,
    REMOVE_CHANNEL_IDS = 1 << 12,
    REMOVE_CONTENT_LICENSES = 1 << 13,
    REMOVE_SERVICE_WORKERS = 1 << 14,
#if defined(OS_ANDROID)
    REMOVE_APP_BANNER_DATA = 1 << 15,
#endif
    
    
    
    REMOVE_HOSTED_APP_DATA_TESTONLY = 1 << 31,

    
    
    REMOVE_SITE_DATA = REMOVE_APPCACHE | REMOVE_COOKIES | REMOVE_FILE_SYSTEMS |
                       REMOVE_INDEXEDDB |
                       REMOVE_LOCAL_STORAGE |
                       REMOVE_PLUGIN_DATA |
                       REMOVE_SERVICE_WORKERS |
                       REMOVE_WEBSQL |
#if defined(OS_ANDROID)
                       REMOVE_APP_BANNER_DATA |
#endif
                       REMOVE_CHANNEL_IDS,

    
    
    
    REMOVE_ALL = REMOVE_SITE_DATA | REMOVE_CACHE | REMOVE_DOWNLOADS |
                 REMOVE_FORM_DATA |
                 REMOVE_HISTORY |
                 REMOVE_PASSWORDS |
                 REMOVE_CONTENT_LICENSES,
  };

  
  
  
  struct NotificationDetails {
    NotificationDetails();
    NotificationDetails(const NotificationDetails& details);
    NotificationDetails(base::Time removal_begin,
                       int removal_mask,
                       int origin_set_mask);
    ~NotificationDetails();

    
    base::Time removal_begin;

    
    int removal_mask;

    
    int origin_set_mask;
  };

  
  
  class Observer {
   public:
    virtual void OnBrowsingDataRemoverDone() = 0;

   protected:
    virtual ~Observer() {}
  };

  
  
  
  class CompletionInhibitor {
   public:
    
    
    
    virtual void OnBrowsingDataRemoverWouldComplete(
        BrowsingDataRemover* remover,
        const base::Closure& continue_to_completion) = 0;

   protected:
    virtual ~CompletionInhibitor() {}
  };

  
  
  
  static BrowsingDataRemover* CreateForUnboundedRange(Profile* profile);

  
  
  
  static BrowsingDataRemover* CreateForRange(Profile* profile,
                                             base::Time delete_begin,
                                             base::Time delete_end);

  
  
  
  static BrowsingDataRemover* CreateForPeriod(Profile* profile,
                                              TimePeriod period);

  
  static base::Time CalculateBeginDeleteTime(TimePeriod time_period);

  
  static bool is_removing() { return is_removing_; }

  
  
  
  static void set_completion_inhibitor_for_testing(
      CompletionInhibitor* inhibitor) {
    completion_inhibitor_ = inhibitor;
  }

  
  
  void Remove(int remove_mask, int origin_set_mask);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  void OnHistoryDeletionDone();

  
  void OverrideStoragePartitionForTesting(
      content::StoragePartition* storage_partition);

 private:
  
  
  FRIEND_TEST_ALL_PREFIXES(ExtensionBrowsingDataTest, OneAtATime);

  
  
  
  
  
  
  friend class BrowsingDataRemoverTest;

  enum CacheState {
    STATE_NONE,
    STATE_CREATE_MAIN,
    STATE_CREATE_MEDIA,
    STATE_DELETE_MAIN,
    STATE_DELETE_MEDIA,
    STATE_DONE
  };

  
  
  static void set_removing(bool is_removing);

  
  
  BrowsingDataRemover(Profile* profile,
                      base::Time delete_begin,
                      base::Time delete_end);

  
  
  
  friend class base::DeleteHelper<BrowsingDataRemover>;
  virtual ~BrowsingDataRemover();

  
  
  void OnKeywordsLoaded();

  
  void OnWaitableEventSignaled(base::WaitableEvent* waitable_event);

#if defined(ENABLE_PLUGINS)
  
  virtual void OnDeauthorizeContentLicensesCompleted(uint32 request_id,
                                                     bool success) OVERRIDE;
#endif

#if defined (OS_CHROMEOS)
  void OnClearPlatformKeys(chromeos::DBusMethodCallStatus call_status,
                           bool result);
#endif

  
  
  
  
  void RemoveImpl(int remove_mask,
                  const GURL& origin,
                  int origin_set_mask);

  
  void NotifyAndDelete();

  
  void NotifyAndDeleteIfDone();

  
  
  void OnClearedHostnameResolutionCache();

  
  void ClearHostnameResolutionCacheOnIOThread(IOThread* io_thread);

  
  
  void OnClearedLoggedInPredictor();

  
  void ClearLoggedInPredictor();

  
  
  
  void OnClearedNetworkPredictor();

  
  
  void ClearNetworkPredictorOnIOThread(
      chrome_browser_net::Predictor* predictor);

  
  
  void OnClearedNetworkingHistory();

  
  
  void ClearedCache();

  
  void ClearCacheOnIOThread();

  
  void DoClearCache(int rv);

#if !defined(DISABLE_NACL)
  
  
  void ClearedNaClCache();

  
  void ClearedNaClCacheOnIOThread();

  
  void ClearNaClCacheOnIOThread();

  
  
  void ClearedPnaclCache();

  
  void ClearedPnaclCacheOnIOThread();

  
  void ClearPnaclCacheOnIOThread(base::Time begin, base::Time end);
#endif

  
  void OnClearedCookies(int num_deleted);

  
  void ClearCookiesOnIOThread(net::URLRequestContextGetter* rq_context);

  
  void ClearChannelIDsOnIOThread(
      net::URLRequestContextGetter* rq_context);

  
  
  void OnClearedChannelIDsOnIOThread(
      net::URLRequestContextGetter* rq_context);

  
  
  void OnClearedChannelIDs();

  
  void OnClearedFormData();

  
  
  void OnClearedAutofillOriginURLs();

  
  void OnClearedStoragePartitionData();

#if defined(ENABLE_WEBRTC)
  
  void OnClearedWebRtcLogs();
#endif

  void OnClearedDomainReliabilityMonitor();

  
  bool AllDone();

  
  Profile* profile_;

  
  const base::Time delete_begin_;

  
  base::Time delete_end_;

  
  static bool is_removing_;

  
  
  
  static CompletionInhibitor* completion_inhibitor_;

  CacheState next_cache_state_;
  disk_cache::Backend* cache_;

  
  scoped_refptr<net::URLRequestContextGetter> main_context_getter_;
  scoped_refptr<net::URLRequestContextGetter> media_context_getter_;

#if defined(ENABLE_PLUGINS)
  
  scoped_ptr<content::PluginDataRemover> plugin_data_remover_;
  base::WaitableEventWatcher watcher_;

  // Used to deauthorize content licenses for Pepper Flash.
  scoped_ptr<PepperFlashSettingsManager> pepper_flash_settings_manager_;
#endif

  uint32 deauthorize_content_licenses_request_id_;
  
  
  bool waiting_for_clear_autofill_origin_urls_;
  bool waiting_for_clear_cache_;
  bool waiting_for_clear_channel_ids_;
  bool waiting_for_clear_content_licenses_;
  
  int waiting_for_clear_cookies_count_;
  bool waiting_for_clear_domain_reliability_monitor_;
  bool waiting_for_clear_form_;
  bool waiting_for_clear_history_;
  bool waiting_for_clear_hostname_resolution_cache_;
  bool waiting_for_clear_keyword_data_;
  bool waiting_for_clear_logged_in_predictor_;
  bool waiting_for_clear_nacl_cache_;
  bool waiting_for_clear_network_predictor_;
  bool waiting_for_clear_networking_history_;
  bool waiting_for_clear_platform_keys_;
  bool waiting_for_clear_plugin_data_;
  bool waiting_for_clear_pnacl_cache_;
  bool waiting_for_clear_storage_partition_data_;
#if defined(ENABLE_WEBRTC)
  bool waiting_for_clear_webrtc_logs_;
#endif

  
  int remove_mask_;

  
  GURL remove_origin_;

  
  int origin_set_mask_;

  ObserverList<Observer> observer_list_;

  
  base::CancelableTaskTracker history_task_tracker_;

  scoped_ptr<TemplateURLService::Subscription> template_url_sub_;

  
  content::StoragePartition* storage_partition_for_testing_;

  DISALLOW_COPY_AND_ASSIGN(BrowsingDataRemover);
};

#endif  
