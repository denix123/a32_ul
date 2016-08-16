// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CONTEXT_WRAPPER_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CONTEXT_WRAPPER_H_

#include <vector>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/service_worker/service_worker_context_core.h"
#include "content/common/content_export.h"
#include "content/public/browser/service_worker_context.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
class SingleThreadTaskRunner;
}

namespace net {
class URLRequestContextGetter;
}

namespace storage {
class QuotaManagerProxy;
}

namespace content {

class BrowserContext;
class ChromeBlobStorageContext;
class ServiceWorkerContextCore;
class ServiceWorkerContextObserver;

class CONTENT_EXPORT ServiceWorkerContextWrapper
    : NON_EXPORTED_BASE(public ServiceWorkerContext),
      public base::RefCountedThreadSafe<ServiceWorkerContextWrapper> {
 public:
  ServiceWorkerContextWrapper(BrowserContext* browser_context);

  
  
  void Init(const base::FilePath& user_data_directory,
            storage::QuotaManagerProxy* quota_manager_proxy);
  void Shutdown();

  
  
  
  void DeleteAndStartOver();

  
  ServiceWorkerContextCore* context();

  
  ServiceWorkerProcessManager* process_manager() {
    return process_manager_.get();
  }

  
  virtual void RegisterServiceWorker(
      const GURL& pattern,
      const GURL& script_url,
      const ResultCallback& continuation) OVERRIDE;
  virtual void UnregisterServiceWorker(const GURL& pattern,
                                       const ResultCallback& continuation)
      OVERRIDE;
  virtual void Terminate() OVERRIDE;
  virtual void GetAllOriginsInfo(const GetUsageInfoCallback& callback) OVERRIDE;
  virtual void DeleteForOrigin(const GURL& origin_url) OVERRIDE;

  void AddObserver(ServiceWorkerContextObserver* observer);
  void RemoveObserver(ServiceWorkerContextObserver* observer);

  bool is_incognito() const { return is_incognito_; }

  
  
  
  
  
  
  void SetBlobParametersForCache(
      net::URLRequestContextGetter* request_context,
      ChromeBlobStorageContext* blob_storage_context);

 private:
  friend class base::RefCountedThreadSafe<ServiceWorkerContextWrapper>;
  friend class EmbeddedWorkerTestHelper;
  friend class ServiceWorkerProcessManager;
  virtual ~ServiceWorkerContextWrapper();

  void InitInternal(
      const base::FilePath& user_data_directory,
      const scoped_refptr<base::SequencedTaskRunner>& stores_task_runner,
      const scoped_refptr<base::SequencedTaskRunner>& database_task_runner,
      const scoped_refptr<base::SingleThreadTaskRunner>& disk_cache_thread,
      storage::QuotaManagerProxy* quota_manager_proxy);
  void ShutdownOnIO();

  void DidDeleteAndStartOver(ServiceWorkerStatusCode status);

  void DidGetAllRegistrationsForGetAllOrigins(
      const GetUsageInfoCallback& callback,
      const std::vector<ServiceWorkerRegistrationInfo>& registrations);
  void DidGetAllRegistrationsForDeleteForOrigin(
      const GURL& origin,
      const std::vector<ServiceWorkerRegistrationInfo>& registrations);

  const scoped_refptr<ObserverListThreadSafe<ServiceWorkerContextObserver> >
      observer_list_;
  const scoped_ptr<ServiceWorkerProcessManager> process_manager_;
  
  scoped_ptr<ServiceWorkerContextCore> context_core_;

  
  bool is_incognito_;
};

}  

#endif  
