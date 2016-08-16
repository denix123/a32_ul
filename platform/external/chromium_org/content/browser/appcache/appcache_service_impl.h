// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_APPCACHE_APPCACHE_SERVICE_IMPL_H_
#define CONTENT_BROWSER_APPCACHE_APPCACHE_SERVICE_IMPL_H_

#include <map>
#include <set>

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "content/common/appcache_interfaces.h"
#include "content/common/content_export.h"
#include "content/public/browser/appcache_service.h"
#include "net/base/completion_callback.h"
#include "net/base/net_errors.h"
#include "storage/browser/quota/quota_manager_proxy.h"

namespace base {
class FilePath;
class SingleThreadTaskRunner;
}  

namespace net {
class URLRequestContext;
}  

namespace storage {
class SpecialStoragePolicy;
}  

namespace content {
FORWARD_DECLARE_TEST(AppCacheServiceImplTest, ScheduleReinitialize);
class AppCacheBackendImpl;
class AppCacheExecutableHandlerFactory;
class AppCacheQuotaClient;
class AppCachePolicy;
class AppCacheServiceImplTest;
class AppCacheStorageImplTest;
class AppCacheStorage;

class CONTENT_EXPORT AppCacheStorageReference
    : public base::RefCounted<AppCacheStorageReference> {
public:
  AppCacheStorage* storage() const { return storage_.get(); }
private:
  friend class AppCacheServiceImpl;
  friend class base::RefCounted<AppCacheStorageReference>;
  AppCacheStorageReference(scoped_ptr<AppCacheStorage> storage);
  ~AppCacheStorageReference();

  scoped_ptr<AppCacheStorage> storage_;
};

class CONTENT_EXPORT AppCacheServiceImpl
    : public AppCacheService {
 public:

  class CONTENT_EXPORT Observer {
   public:
    
    
    
    
    virtual void OnServiceReinitialized(
        AppCacheStorageReference* old_storage_ref) = 0;
    virtual ~Observer() {}
  };

  
  explicit AppCacheServiceImpl(storage::QuotaManagerProxy* quota_manager_proxy);
  virtual ~AppCacheServiceImpl();

  void Initialize(
      const base::FilePath& cache_directory,
      const scoped_refptr<base::SingleThreadTaskRunner>& db_thread,
      const scoped_refptr<base::SingleThreadTaskRunner>& cache_thread);

  void AddObserver(Observer* observer) {
    observers_.AddObserver(observer);
  }

  void RemoveObserver(Observer* observer) {
    observers_.RemoveObserver(observer);
  }

  
  
  void ScheduleReinitialize();

  
  virtual void CanHandleMainResourceOffline(
      const GURL& url,
      const GURL& first_party,
      const net::CompletionCallback& callback) OVERRIDE;
  virtual void GetAllAppCacheInfo(
      AppCacheInfoCollection* collection,
      const net::CompletionCallback& callback) OVERRIDE;
  virtual void DeleteAppCacheGroup(
      const GURL& manifest_url,
      const net::CompletionCallback& callback) OVERRIDE;

  
  
  
  virtual void DeleteAppCachesForOrigin(
      const GURL& origin, const net::CompletionCallback& callback);

  
  
  void CheckAppCacheResponse(const GURL& manifest_url, int64 cache_id,
                             int64 response_id);

  
  
  
  
  net::URLRequestContext* request_context() const { return request_context_; }
  void set_request_context(net::URLRequestContext* context) {
    request_context_ = context;
  }

  
  
  
  AppCachePolicy* appcache_policy() const { return appcache_policy_; }
  void set_appcache_policy(AppCachePolicy* policy) {
    appcache_policy_ = policy;
  }

  
  
  
  
  AppCacheExecutableHandlerFactory* handler_factory() const {
    return handler_factory_;
  }
  void set_handler_factory(
      AppCacheExecutableHandlerFactory* factory) {
    handler_factory_ = factory;
  }

  storage::SpecialStoragePolicy* special_storage_policy() const {
    return special_storage_policy_.get();
  }
  void set_special_storage_policy(storage::SpecialStoragePolicy* policy);

  storage::QuotaManagerProxy* quota_manager_proxy() const {
    return quota_manager_proxy_.get();
  }

  AppCacheQuotaClient* quota_client() const {
    return quota_client_;
  }

  
  
  void RegisterBackend(AppCacheBackendImpl* backend_impl);
  void UnregisterBackend(AppCacheBackendImpl* backend_impl);
  AppCacheBackendImpl* GetBackend(int id) const {
    BackendMap::const_iterator it = backends_.find(id);
    return (it != backends_.end()) ? it->second : NULL;
  }

  AppCacheStorage* storage() const { return storage_.get(); }

  
  void set_force_keep_session_state() { force_keep_session_state_ = true; }
  bool force_keep_session_state() const { return force_keep_session_state_; }

 protected:
  friend class content::AppCacheServiceImplTest;
  friend class content::AppCacheStorageImplTest;
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheServiceImplTest,
      ScheduleReinitialize);

  class AsyncHelper;
  class CanHandleOfflineHelper;
  class DeleteHelper;
  class DeleteOriginHelper;
  class GetInfoHelper;
  class CheckResponseHelper;

  typedef std::set<AsyncHelper*> PendingAsyncHelpers;
  typedef std::map<int, AppCacheBackendImpl*> BackendMap;

  void Reinitialize();

  base::FilePath cache_directory_;
  scoped_refptr<base::SingleThreadTaskRunner> db_thread_;
  scoped_refptr<base::SingleThreadTaskRunner> cache_thread_;
  AppCachePolicy* appcache_policy_;
  AppCacheQuotaClient* quota_client_;
  AppCacheExecutableHandlerFactory* handler_factory_;
  scoped_ptr<AppCacheStorage> storage_;
  scoped_refptr<storage::SpecialStoragePolicy> special_storage_policy_;
  scoped_refptr<storage::QuotaManagerProxy> quota_manager_proxy_;
  PendingAsyncHelpers pending_helpers_;
  BackendMap backends_;  
  
  net::URLRequestContext* request_context_;
  
  bool force_keep_session_state_;
  base::Time last_reinit_time_;
  base::TimeDelta next_reinit_delay_;
  base::OneShotTimer<AppCacheServiceImpl> reinit_timer_;
  ObserverList<Observer> observers_;

  DISALLOW_COPY_AND_ASSIGN(AppCacheServiceImpl);
};

}  

#endif  
