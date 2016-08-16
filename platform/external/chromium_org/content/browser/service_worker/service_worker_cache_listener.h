// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_LISTENER_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_LISTENER_H_

#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "content/browser/service_worker/embedded_worker_instance.h"
#include "content/browser/service_worker/service_worker_cache_storage.h"

namespace content {

struct ServiceWorkerBatchOperation;
struct ServiceWorkerCacheQueryParams;
struct ServiceWorkerFetchRequest;
class ServiceWorkerVersion;

class ServiceWorkerCacheListener : public EmbeddedWorkerInstance::Listener {
 public:
  ServiceWorkerCacheListener(ServiceWorkerVersion* version,
                             base::WeakPtr<ServiceWorkerContextCore> context);
  virtual ~ServiceWorkerCacheListener();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

 private:
  
  void OnCacheStorageGet(int request_id, const base::string16& cache_name);
  void OnCacheStorageHas(int request_id, const base::string16& cache_name);
  void OnCacheStorageCreate(int request_id,
                          const base::string16& cache_name);
  void OnCacheStorageDelete(int request_id,
                           const base::string16& cache_name);
  void OnCacheStorageKeys(int request_id);

  
  void OnCacheMatch(int request_id,
                    int cache_id,
                    const ServiceWorkerFetchRequest& request,
                    const ServiceWorkerCacheQueryParams& match_params);
  void OnCacheMatchAll(int request_id,
                       int cache_id,
                       const ServiceWorkerFetchRequest& request,
                       const ServiceWorkerCacheQueryParams& match_params);
  void OnCacheKeys(int request_id,
                   int cache_id,
                   const ServiceWorkerFetchRequest& request,
                   const ServiceWorkerCacheQueryParams& match_params);
  void OnCacheBatch(int request_id,
                    int cache_id,
                    const std::vector<ServiceWorkerBatchOperation>& operations);
  void OnCacheClosed(int cache_id);

 private:
  typedef int32_t CacheID;  
  typedef std::map<CacheID, scoped_refptr<ServiceWorkerCache> > IDToCacheMap;

  void Send(const IPC::Message& message);

  void OnCacheStorageGetCallback(
      int request_id,
      const scoped_refptr<ServiceWorkerCache>& cache,
      ServiceWorkerCacheStorage::CacheStorageError error);
  void OnCacheStorageHasCallback(
      int request_id,
      bool has_cache,
      ServiceWorkerCacheStorage::CacheStorageError error);
  void OnCacheStorageCreateCallback(
      int request_id,
      const scoped_refptr<ServiceWorkerCache>& cache,
      ServiceWorkerCacheStorage::CacheStorageError error);
  void OnCacheStorageDeleteCallback(
      int request_id,
      bool deleted,
      ServiceWorkerCacheStorage::CacheStorageError error);
  void OnCacheStorageKeysCallback(
      int request_id,
      const std::vector<std::string>& strings,
      ServiceWorkerCacheStorage::CacheStorageError error);

  
  
  
  CacheID StoreCacheReference(const scoped_refptr<ServiceWorkerCache>& cache);
  void DropCacheReference(CacheID cache_id);

  
  ServiceWorkerVersion* version_;

  
  base::WeakPtr<ServiceWorkerContextCore> context_;

  IDToCacheMap id_to_cache_map_;
  CacheID next_cache_id_;

  base::WeakPtrFactory<ServiceWorkerCacheListener> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerCacheListener);
};

}  

#endif  
