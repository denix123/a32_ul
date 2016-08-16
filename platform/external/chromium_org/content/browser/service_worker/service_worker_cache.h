// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CACHE_H_

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "content/common/service_worker/service_worker_types.h"
#include "net/base/completion_callback.h"
#include "net/disk_cache/disk_cache.h"

namespace net {
class URLRequestContext;
class IOBufferWithSize;
}

namespace storage {
class BlobData;
class BlobDataHandle;
class BlobStorageContext;
}

namespace content {
class ChromeBlobStorageContext;
class ServiceWorkerRequestResponseHeaders;


class CONTENT_EXPORT ServiceWorkerCache
    : public base::RefCounted<ServiceWorkerCache> {
 public:
  enum ErrorType {
    ErrorTypeOK = 0,
    ErrorTypeExists,
    ErrorTypeStorage,
    ErrorTypeNotFound
  };
  enum EntryIndex { INDEX_HEADERS = 0, INDEX_RESPONSE_BODY };
  typedef base::Callback<void(ErrorType)> ErrorCallback;
  typedef base::Callback<void(ErrorType,
                              scoped_ptr<ServiceWorkerResponse>,
                              scoped_ptr<storage::BlobDataHandle>)>
      ResponseCallback;
  typedef std::vector<ServiceWorkerFetchRequest> Requests;
  typedef base::Callback<void(ErrorType, scoped_ptr<Requests>)>
      RequestsCallback;

  static scoped_refptr<ServiceWorkerCache> CreateMemoryCache(
      net::URLRequestContext* request_context,
      base::WeakPtr<storage::BlobStorageContext> blob_context);
  static scoped_refptr<ServiceWorkerCache> CreatePersistentCache(
      const base::FilePath& path,
      net::URLRequestContext* request_context,
      base::WeakPtr<storage::BlobStorageContext> blob_context);

  
  void Match(scoped_ptr<ServiceWorkerFetchRequest> request,
             const ResponseCallback& callback);

  
  
  
  void Put(scoped_ptr<ServiceWorkerFetchRequest> request,
           scoped_ptr<ServiceWorkerResponse> response,
           const ErrorCallback& callback);

  
  
  void Delete(scoped_ptr<ServiceWorkerFetchRequest> request,
              const ErrorCallback& callback);

  
  
  
  void Keys(const RequestsCallback& callback);

  
  void Close();

  void set_backend(scoped_ptr<disk_cache::Backend> backend) {
    backend_ = backend.Pass();
  }

  base::WeakPtr<ServiceWorkerCache> AsWeakPtr();

 private:
  friend class base::RefCounted<ServiceWorkerCache>;

  struct KeysContext;
  typedef std::vector<disk_cache::Entry*> Entries;

  ServiceWorkerCache(const base::FilePath& path,
                     net::URLRequestContext* request_context,
                     base::WeakPtr<storage::BlobStorageContext> blob_context);

  
  
  virtual ~ServiceWorkerCache();

  void PutImpl(scoped_ptr<ServiceWorkerFetchRequest> request,
               scoped_ptr<ServiceWorkerResponse> response,
               scoped_ptr<storage::BlobDataHandle> blob_data_handle,
               const ErrorCallback& callback);

  
  static void KeysDidOpenNextEntry(scoped_ptr<KeysContext> keys_context,
                                   int rv);
  static void KeysProcessNextEntry(scoped_ptr<KeysContext> keys_context,
                                   const Entries::iterator& iter);
  static void KeysDidReadHeaders(
      scoped_ptr<KeysContext> keys_context,
      const Entries::iterator& iter,
      scoped_ptr<ServiceWorkerRequestResponseHeaders> headers);

  
  
  void CreateBackend(const ErrorCallback& callback);

  void Init(const base::Closure& callback);
  void InitDone(ErrorType error);

  
  
  scoped_ptr<disk_cache::Backend> backend_;
  base::FilePath path_;
  net::URLRequestContext* request_context_;
  base::WeakPtr<storage::BlobStorageContext> blob_storage_context_;
  bool initialized_;
  std::vector<base::Closure> init_callbacks_;

  base::WeakPtrFactory<ServiceWorkerCache> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerCache);
};

}  

#endif  
