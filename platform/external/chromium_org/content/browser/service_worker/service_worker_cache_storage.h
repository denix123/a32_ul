// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_STORAGE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_STORAGE_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/service_worker/service_worker_cache.h"

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


class CONTENT_EXPORT ServiceWorkerCacheStorage {
 public:
  enum CacheStorageError {
    CACHE_STORAGE_ERROR_NO_ERROR,
    CACHE_STORAGE_ERROR_NOT_IMPLEMENTED,
    CACHE_STORAGE_ERROR_NOT_FOUND,
    CACHE_STORAGE_ERROR_EXISTS,
    CACHE_STORAGE_ERROR_STORAGE,
    CACHE_STORAGE_ERROR_CLOSING
  };
  typedef std::vector<std::string> StringVector;
  typedef base::Callback<void(bool, CacheStorageError)> BoolAndErrorCallback;
  typedef base::Callback<void(const scoped_refptr<ServiceWorkerCache>&,
                              CacheStorageError)> CacheAndErrorCallback;
  typedef base::Callback<void(const StringVector&, CacheStorageError)>
      StringsAndErrorCallback;

  ServiceWorkerCacheStorage(
      const base::FilePath& origin_path,
      bool memory_only,
      base::SequencedTaskRunner* cache_task_runner,
      net::URLRequestContext* request_context,
      base::WeakPtr<storage::BlobStorageContext> blob_context);

  virtual ~ServiceWorkerCacheStorage();

  
  
  
  void CreateCache(const std::string& cache_name,
                   const CacheAndErrorCallback& callback);

  
  
  void GetCache(const std::string& cache_name,
                const CacheAndErrorCallback& callback);

  
  void HasCache(const std::string& cache_name,
                const BoolAndErrorCallback& callback);

  
  
  void DeleteCache(const std::string& cache_name,
                   const BoolAndErrorCallback& callback);

  
  void EnumerateCaches(const StringsAndErrorCallback& callback);

  

 private:
  class MemoryLoader;
  class SimpleCacheLoader;
  class CacheLoader;

  typedef std::map<std::string, base::WeakPtr<ServiceWorkerCache> > CacheMap;

  
  
  scoped_refptr<ServiceWorkerCache> GetLoadedCache(
      const std::string& cache_name);

  
  
  void LazyInit(const base::Closure& closure);
  void LazyInitDidLoadIndex(
      const base::Closure& callback,
      scoped_ptr<std::vector<std::string> > indexed_cache_names);

  void AddCacheToMap(const std::string& cache_name,
                     base::WeakPtr<ServiceWorkerCache> cache);

  
  void CreateCacheDidCreateCache(
      const std::string& cache_name,
      const CacheAndErrorCallback& callback,
      const scoped_refptr<ServiceWorkerCache>& cache);
  void CreateCacheDidWriteIndex(const CacheAndErrorCallback& callback,
                                const scoped_refptr<ServiceWorkerCache>& cache,
                                bool success);

  
  void DeleteCacheDidWriteIndex(const std::string& cache_name,
                                const BoolAndErrorCallback& callback,
                                bool success);
  void DeleteCacheDidCleanUp(const BoolAndErrorCallback& callback,
                             bool success);

  
  bool initialized_;

  
  std::vector<base::Closure> init_callbacks_;

  
  CacheMap cache_map_;

  
  StringVector ordered_cache_names_;

  
  base::FilePath origin_path_;

  
  scoped_refptr<base::SequencedTaskRunner> cache_task_runner_;

  
  bool memory_only_;

  
  scoped_ptr<CacheLoader> cache_loader_;

  base::WeakPtrFactory<ServiceWorkerCacheStorage> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerCacheStorage);
};

}  

#endif  
