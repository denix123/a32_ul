// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_APPCACHE_APPCACHE_QUOTA_CLIENT_H_
#define CONTENT_BROWSER_APPCACHE_APPCACHE_QUOTA_CLIENT_H_

#include <deque>
#include <map>
#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/appcache/appcache_storage.h"
#include "content/common/content_export.h"
#include "net/base/completion_callback.h"
#include "storage/browser/quota/quota_client.h"
#include "storage/browser/quota/quota_task.h"
#include "storage/common/quota/quota_types.h"

namespace content {
class AppCacheQuotaClientTest;
class AppCacheServiceImpl;
class AppCacheStorageImpl;

class AppCacheQuotaClient : public storage::QuotaClient {
 public:
  typedef std::deque<base::Closure> RequestQueue;

  virtual ~AppCacheQuotaClient();

  
  virtual ID id() const OVERRIDE;
  virtual void OnQuotaManagerDestroyed() OVERRIDE;
  virtual void GetOriginUsage(const GURL& origin,
                              storage::StorageType type,
                              const GetUsageCallback& callback) OVERRIDE;
  virtual void GetOriginsForType(storage::StorageType type,
                                 const GetOriginsCallback& callback) OVERRIDE;
  virtual void GetOriginsForHost(storage::StorageType type,
                                 const std::string& host,
                                 const GetOriginsCallback& callback) OVERRIDE;
  virtual void DeleteOriginData(const GURL& origin,
                                storage::StorageType type,
                                const DeletionCallback& callback) OVERRIDE;
  virtual bool DoesSupport(storage::StorageType type) const OVERRIDE;

 private:
  friend class content::AppCacheQuotaClientTest;
  friend class AppCacheServiceImpl;  
  friend class AppCacheStorageImpl;  

  CONTENT_EXPORT
      explicit AppCacheQuotaClient(AppCacheServiceImpl* service);

  void DidDeleteAppCachesForOrigin(int rv);
  void GetOriginsHelper(storage::StorageType type,
                        const std::string& opt_host,
                        const GetOriginsCallback& callback);
  void ProcessPendingRequests();
  void DeletePendingRequests();
  const AppCacheStorage::UsageMap* GetUsageMap();
  net::CancelableCompletionCallback* GetServiceDeleteCallback();

  
  CONTENT_EXPORT void NotifyAppCacheReady();
  CONTENT_EXPORT void NotifyAppCacheDestroyed();

  
  
  RequestQueue pending_batch_requests_;
  RequestQueue pending_serial_requests_;

  
  
  DeletionCallback current_delete_request_callback_;
  scoped_ptr<net::CancelableCompletionCallback> service_delete_callback_;

  AppCacheServiceImpl* service_;
  bool appcache_is_ready_;
  bool quota_manager_is_destroyed_;

  DISALLOW_COPY_AND_ASSIGN(AppCacheQuotaClient);
};

}  

#endif  
