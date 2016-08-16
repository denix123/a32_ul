// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_STORAGE_MANAGER_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_STORAGE_MANAGER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "content/browser/service_worker/service_worker_cache_storage.h"
#include "content/common/content_export.h"
#include "url/gurl.h"

namespace base {
class SequencedTaskRunner;
}

namespace net {
class URLRequestContext;
}

namespace storage {
class BlobStorageContext;
}

namespace content {

class CONTENT_EXPORT ServiceWorkerCacheStorageManager {
 public:
  static scoped_ptr<ServiceWorkerCacheStorageManager> Create(
      const base::FilePath& path,
      const scoped_refptr<base::SequencedTaskRunner>& cache_task_runner);

  static scoped_ptr<ServiceWorkerCacheStorageManager> Create(
      ServiceWorkerCacheStorageManager* old_manager);

  virtual ~ServiceWorkerCacheStorageManager();

  
  
  void CreateCache(
      const GURL& origin,
      const std::string& cache_name,
      const ServiceWorkerCacheStorage::CacheAndErrorCallback& callback);
  void GetCache(
      const GURL& origin,
      const std::string& cache_name,
      const ServiceWorkerCacheStorage::CacheAndErrorCallback& callback);
  void HasCache(
      const GURL& origin,
      const std::string& cache_name,
      const ServiceWorkerCacheStorage::BoolAndErrorCallback& callback);
  void DeleteCache(
      const GURL& origin,
      const std::string& cache_name,
      const ServiceWorkerCacheStorage::BoolAndErrorCallback& callback);
  void EnumerateCaches(
      const GURL& origin,
      const ServiceWorkerCacheStorage::StringsAndErrorCallback& callback);
  

  
  
  void SetBlobParametersForCache(
      net::URLRequestContext* request_context,
      base::WeakPtr<storage::BlobStorageContext> blob_storage_context);

 private:
  typedef std::map<GURL, ServiceWorkerCacheStorage*>
      ServiceWorkerCacheStorageMap;

  ServiceWorkerCacheStorageManager(
      const base::FilePath& path,
      const scoped_refptr<base::SequencedTaskRunner>& cache_task_runner);

  
  
  ServiceWorkerCacheStorage* FindOrCreateServiceWorkerCacheManager(
      const GURL& origin);

  net::URLRequestContext* url_request_context() const {
    return request_context_;
  }
  base::WeakPtr<storage::BlobStorageContext> blob_storage_context() const {
    return blob_context_;
  }
  base::FilePath root_path() const { return root_path_; }
  const scoped_refptr<base::SequencedTaskRunner>& cache_task_runner() const {
    return cache_task_runner_;
  }

  base::FilePath root_path_;
  scoped_refptr<base::SequencedTaskRunner> cache_task_runner_;

  
  
  ServiceWorkerCacheStorageMap cache_storage_map_;

  net::URLRequestContext* request_context_;
  base::WeakPtr<storage::BlobStorageContext> blob_context_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerCacheStorageManager);
};

}  

#endif  
