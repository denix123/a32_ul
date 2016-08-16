// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_APPCACHE_APPCACHE_HOST_H_
#define CONTENT_BROWSER_APPCACHE_APPCACHE_HOST_H_

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "content/browser/appcache/appcache_group.h"
#include "content/browser/appcache/appcache_service_impl.h"
#include "content/browser/appcache/appcache_storage.h"
#include "content/common/appcache_interfaces.h"
#include "content/common/content_export.h"
#include "content/public/common/resource_type.h"
#include "url/gurl.h"

namespace net {
class URLRequest;
}  

namespace content {
FORWARD_DECLARE_TEST(AppCacheGroupTest, CleanupUnusedGroup);
FORWARD_DECLARE_TEST(AppCacheGroupTest, QueueUpdate);
FORWARD_DECLARE_TEST(AppCacheHostTest, Basic);
FORWARD_DECLARE_TEST(AppCacheHostTest, SelectNoCache);
FORWARD_DECLARE_TEST(AppCacheHostTest, ForeignEntry);
FORWARD_DECLARE_TEST(AppCacheHostTest, FailedCacheLoad);
FORWARD_DECLARE_TEST(AppCacheHostTest, FailedGroupLoad);
FORWARD_DECLARE_TEST(AppCacheHostTest, SetSwappableCache);
FORWARD_DECLARE_TEST(AppCacheHostTest, ForDedicatedWorker);
FORWARD_DECLARE_TEST(AppCacheHostTest, SelectCacheAllowed);
FORWARD_DECLARE_TEST(AppCacheHostTest, SelectCacheBlocked);
FORWARD_DECLARE_TEST(AppCacheTest, CleanupUnusedCache);
class AppCache;
class AppCacheFrontend;
class AppCacheGroupTest;
class AppCacheHostTest;
class AppCacheRequestHandler;
class AppCacheRequestHandlerTest;
class AppCacheStorageImplTest;
class AppCacheTest;
class AppCacheUpdateJobTest;

typedef base::Callback<void(AppCacheStatus, void*)> GetStatusCallback;
typedef base::Callback<void(bool, void*)> StartUpdateCallback;
typedef base::Callback<void(bool, void*)> SwapCacheCallback;

class CONTENT_EXPORT AppCacheHost
    : public AppCacheStorage::Delegate,
      public AppCacheGroup::UpdateObserver,
      public AppCacheServiceImpl::Observer {
 public:

  class CONTENT_EXPORT Observer {
   public:
    
    virtual void OnCacheSelectionComplete(AppCacheHost* host) = 0;

    
    virtual void OnDestructionImminent(AppCacheHost* host) = 0;

    virtual ~Observer() {}
  };

  AppCacheHost(int host_id, AppCacheFrontend* frontend,
               AppCacheServiceImpl* service);
  virtual ~AppCacheHost();

  
  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  void SelectCache(const GURL& document_url,
                   const int64 cache_document_was_loaded_from,
                   const GURL& manifest_url);
  void SelectCacheForWorker(int parent_process_id,
                            int parent_host_id);
  void SelectCacheForSharedWorker(int64 appcache_id);
  void MarkAsForeignEntry(const GURL& document_url,
                          int64 cache_document_was_loaded_from);
  void GetStatusWithCallback(const GetStatusCallback& callback,
                             void* callback_param);
  void StartUpdateWithCallback(const StartUpdateCallback& callback,
                               void* callback_param);
  void SwapCacheWithCallback(const SwapCacheCallback& callback,
                             void* callback_param);

  
  
  
  void SetSpawningHostId(int spawning_process_id, int spawning_host_id);

  
  
  const AppCacheHost* GetSpawningHost() const;

  const GURL& preferred_manifest_url() const {
    return preferred_manifest_url_;
  }
  void set_preferred_manifest_url(const GURL& url) {
    preferred_manifest_url_ = url;
  }

  
  
  AppCacheRequestHandler* CreateRequestHandler(
      net::URLRequest* request,
      ResourceType resource_type);

  
  void GetResourceList(std::vector<AppCacheResourceInfo>* resource_infos);

  
  
  
  
  
  
  void AssociateNoCache(const GURL& manifest_url);

  
  
  
  
  void AssociateIncompleteCache(AppCache* cache, const GURL& manifest_url);

  
  
  
  
  void AssociateCompleteCache(AppCache* cache);

  
  
  void SetSwappableCache(AppCacheGroup* group);

  
  void LoadMainResourceCache(int64 cache_id);

  
  
  void NotifyMainResourceIsNamespaceEntry(const GURL& namespace_entry_url);

  
  
  void NotifyMainResourceBlocked(const GURL& manifest_url);

  
  
  const GURL& pending_master_entry_url() const {
    return new_master_entry_url_;
  }

  int host_id() const { return host_id_; }
  AppCacheServiceImpl* service() const { return service_; }
  AppCacheStorage* storage() const { return storage_; }
  AppCacheFrontend* frontend() const { return frontend_; }
  AppCache* associated_cache() const { return associated_cache_.get(); }

  bool is_selection_pending() const {
    return pending_selected_cache_id_ != kAppCacheNoCacheId ||
           !pending_selected_manifest_url_.is_empty();
  }

  const GURL& first_party_url() const { return first_party_url_; }

  
  void PrepareForTransfer();
  void CompleteTransfer(int host_id, AppCacheFrontend* frontend);

 private:
  friend class content::AppCacheHostTest;
  friend class content::AppCacheStorageImplTest;
  friend class content::AppCacheRequestHandlerTest;
  friend class content::AppCacheUpdateJobTest;

  AppCacheStatus GetStatus();
  void LoadSelectedCache(int64 cache_id);
  void LoadOrCreateGroup(const GURL& manifest_url);

  
  void AssociateCacheHelper(AppCache* cache, const GURL& manifest_url);

  
  virtual void OnCacheLoaded(AppCache* cache, int64 cache_id) OVERRIDE;
  virtual void OnGroupLoaded(AppCacheGroup* group,
                             const GURL& manifest_url) OVERRIDE;
  
  virtual void OnServiceReinitialized(
      AppCacheStorageReference* old_storage_ref) OVERRIDE;

  void FinishCacheSelection(AppCache* cache, AppCacheGroup* group);
  void DoPendingGetStatus();
  void DoPendingStartUpdate();
  void DoPendingSwapCache();

  void ObserveGroupBeingUpdated(AppCacheGroup* group);

  
  virtual void OnUpdateComplete(AppCacheGroup* group) OVERRIDE;

  
  bool is_for_dedicated_worker() const {
    return parent_host_id_ != kAppCacheNoHostId;
  }

  
  
  AppCacheHost* GetParentAppCacheHost() const;

  
  int host_id_;

  
  
  
  int spawning_host_id_;
  int spawning_process_id_;
  GURL preferred_manifest_url_;

  
  
  
  
  
  int parent_host_id_;
  int parent_process_id_;

  
  
  
  scoped_refptr<AppCacheStorageReference> disabled_storage_reference_;

  
  scoped_refptr<AppCache> associated_cache_;

  
  
  
  
  scoped_refptr<AppCache> swappable_cache_;

  
  scoped_refptr<AppCacheGroup> group_being_updated_;

  
  
  
  scoped_refptr<AppCache> newest_cache_of_group_being_updated_;

  
  
  scoped_refptr<AppCache> main_resource_cache_;
  int64 pending_main_resource_cache_id_;

  
  
  
  int64 pending_selected_cache_id_;
  GURL pending_selected_manifest_url_;

  
  GURL new_master_entry_url_;

  
  AppCacheFrontend* frontend_;

  
  AppCacheServiceImpl* service_;

  
  
  
  
  
  
  
  AppCacheStorage* storage_;

  
  
  
  
  GetStatusCallback pending_get_status_callback_;
  StartUpdateCallback pending_start_update_callback_;
  SwapCacheCallback pending_swap_cache_callback_;
  void* pending_callback_param_;

  
  
  bool main_resource_was_namespace_entry_;
  GURL namespace_entry_url_;

  
  bool main_resource_blocked_;
  GURL blocked_manifest_url_;

  
  
  bool associated_cache_info_pending_;

  
  ObserverList<Observer> observers_;

  
  GURL origin_in_use_;

  
  GURL first_party_url_;

  FRIEND_TEST_ALL_PREFIXES(content::AppCacheGroupTest, CleanupUnusedGroup);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheGroupTest, QueueUpdate);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, Basic);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, SelectNoCache);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, ForeignEntry);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, FailedCacheLoad);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, FailedGroupLoad);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, SetSwappableCache);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, ForDedicatedWorker);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, SelectCacheAllowed);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheHostTest, SelectCacheBlocked);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheTest, CleanupUnusedCache);

  DISALLOW_COPY_AND_ASSIGN(AppCacheHost);
};

}  

#endif  
