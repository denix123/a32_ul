// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SHARED_WORKERT_WORKER_STORAGE_PARTITION_H_
#define CONTENT_BROWSER_SHARED_WORKERT_WORKER_STORAGE_PARTITION_H_

#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"

namespace storage {
class QuotaManager;
}

namespace storage {
class FileSystemContext;
}  

namespace net {
class URLRequestContextGetter;
}

namespace storage {
class DatabaseTracker;
}  

namespace content {
class ChromeAppCacheService;
class IndexedDBContextImpl;
class ServiceWorkerContextWrapper;

class CONTENT_EXPORT WorkerStoragePartition {
 public:
  WorkerStoragePartition(
      net::URLRequestContextGetter* url_request_context,
      net::URLRequestContextGetter* media_url_request_context,
      ChromeAppCacheService* appcache_service,
      storage::QuotaManager* quota_manager,
      storage::FileSystemContext* filesystem_context,
      storage::DatabaseTracker* database_tracker,
      IndexedDBContextImpl* indexed_db_context,
      ServiceWorkerContextWrapper* service_worker_context);
  ~WorkerStoragePartition();

  
  
  
  WorkerStoragePartition(const WorkerStoragePartition& other);
  const WorkerStoragePartition& operator=(const WorkerStoragePartition& rhs);

  bool Equals(const WorkerStoragePartition& other) const;

  net::URLRequestContextGetter* url_request_context() const {
    return url_request_context_.get();
  }

  net::URLRequestContextGetter* media_url_request_context() const {
    return media_url_request_context_.get();
  }

  ChromeAppCacheService* appcache_service() const {
    return appcache_service_.get();
  }

  storage::QuotaManager* quota_manager() const { return quota_manager_.get(); }

  storage::FileSystemContext* filesystem_context() const {
    return filesystem_context_.get();
  }

  storage::DatabaseTracker* database_tracker() const {
    return database_tracker_.get();
  }

  IndexedDBContextImpl* indexed_db_context() const {
    return indexed_db_context_.get();
  }

  ServiceWorkerContextWrapper* service_worker_context() const {
    return service_worker_context_.get();
  }

 private:
  void Copy(const WorkerStoragePartition& other);

  scoped_refptr<net::URLRequestContextGetter> url_request_context_;
  scoped_refptr<net::URLRequestContextGetter> media_url_request_context_;
  scoped_refptr<ChromeAppCacheService> appcache_service_;
  scoped_refptr<storage::QuotaManager> quota_manager_;
  scoped_refptr<storage::FileSystemContext> filesystem_context_;
  scoped_refptr<storage::DatabaseTracker> database_tracker_;
  scoped_refptr<IndexedDBContextImpl> indexed_db_context_;
  scoped_refptr<ServiceWorkerContextWrapper> service_worker_context_;
};

class CONTENT_EXPORT WorkerStoragePartitionId {
 public:
  explicit WorkerStoragePartitionId(const WorkerStoragePartition& partition);
  ~WorkerStoragePartitionId();
  bool Equals(const WorkerStoragePartitionId& other) const;

 private:
  net::URLRequestContextGetter* url_request_context_;
  net::URLRequestContextGetter* media_url_request_context_;
  ChromeAppCacheService* appcache_service_;
  storage::QuotaManager* quota_manager_;
  storage::FileSystemContext* filesystem_context_;
  storage::DatabaseTracker* database_tracker_;
  IndexedDBContextImpl* indexed_db_context_;
  ServiceWorkerContextWrapper* service_worker_context_;
};

}  

#endif  
