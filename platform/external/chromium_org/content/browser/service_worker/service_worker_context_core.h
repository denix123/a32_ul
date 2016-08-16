// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CONTEXT_CORE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_CONTEXT_CORE_H_

#include <map>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/id_map.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list_threadsafe.h"
#include "content/browser/service_worker/service_worker_info.h"
#include "content/browser/service_worker/service_worker_process_manager.h"
#include "content/browser/service_worker/service_worker_provider_host.h"
#include "content/browser/service_worker/service_worker_registration_status.h"
#include "content/browser/service_worker/service_worker_storage.h"
#include "content/common/content_export.h"

class GURL;

namespace base {
class FilePath;
class SequencedTaskRunner;
class SingleThreadTaskRunner;
}

namespace net {
class URLRequestContext;
}

namespace storage {
class QuotaManagerProxy;
}

namespace content {

class EmbeddedWorkerRegistry;
class ServiceWorkerCacheStorageManager;
class ServiceWorkerContextObserver;
class ServiceWorkerContextWrapper;
class ServiceWorkerHandle;
class ServiceWorkerJobCoordinator;
class ServiceWorkerProviderHost;
class ServiceWorkerRegistration;
class ServiceWorkerStorage;

class CONTENT_EXPORT ServiceWorkerContextCore
    : NON_EXPORTED_BASE(public ServiceWorkerVersion::Listener) {
 public:
  typedef base::Callback<void(ServiceWorkerStatusCode status)> StatusCallback;
  typedef base::Callback<void(ServiceWorkerStatusCode status,
                              int64 registration_id,
                              int64 version_id)> RegistrationCallback;
  typedef base::Callback<
      void(ServiceWorkerStatusCode status)> UnregistrationCallback;
  typedef IDMap<ServiceWorkerProviderHost, IDMapOwnPointer> ProviderMap;
  typedef IDMap<ProviderMap, IDMapOwnPointer> ProcessToProviderMap;

  
  static const base::FilePath::CharType kServiceWorkerDirectory[];

  
  class ProviderHostIterator {
   public:
    ~ProviderHostIterator();
    ServiceWorkerProviderHost* GetProviderHost();
    void Advance();
    bool IsAtEnd();

   private:
    friend class ServiceWorkerContextCore;
    explicit ProviderHostIterator(ProcessToProviderMap* map);
    void Initialize();

    ProcessToProviderMap* map_;
    scoped_ptr<ProcessToProviderMap::iterator> process_iterator_;
    scoped_ptr<ProviderMap::iterator> provider_host_iterator_;

    DISALLOW_COPY_AND_ASSIGN(ProviderHostIterator);
  };

  
  
  
  
  
  
  ServiceWorkerContextCore(
      const base::FilePath& user_data_directory,
      const scoped_refptr<base::SequencedTaskRunner>& cache_task_runner,
      const scoped_refptr<base::SequencedTaskRunner>& database_task_runner,
      const scoped_refptr<base::SingleThreadTaskRunner>& disk_cache_thread,
      storage::QuotaManagerProxy* quota_manager_proxy,
      ObserverListThreadSafe<ServiceWorkerContextObserver>* observer_list,
      ServiceWorkerContextWrapper* wrapper);
  ServiceWorkerContextCore(
      ServiceWorkerContextCore* old_context,
      ServiceWorkerContextWrapper* wrapper);
  virtual ~ServiceWorkerContextCore();

  
  virtual void OnWorkerStarted(ServiceWorkerVersion* version) OVERRIDE;
  virtual void OnWorkerStopped(ServiceWorkerVersion* version) OVERRIDE;
  virtual void OnVersionStateChanged(ServiceWorkerVersion* version) OVERRIDE;
  virtual void OnErrorReported(ServiceWorkerVersion* version,
                               const base::string16& error_message,
                               int line_number,
                               int column_number,
                               const GURL& source_url) OVERRIDE;
  virtual void OnReportConsoleMessage(ServiceWorkerVersion* version,
                                      int source_identifier,
                                      int message_level,
                                      const base::string16& message,
                                      int line_number,
                                      const GURL& source_url) OVERRIDE;

  ServiceWorkerStorage* storage() { return storage_.get(); }
  ServiceWorkerCacheStorageManager* cache_manager() {
    return cache_manager_.get();
  }
  ServiceWorkerProcessManager* process_manager();
  EmbeddedWorkerRegistry* embedded_worker_registry() {
    return embedded_worker_registry_.get();
  }
  ServiceWorkerJobCoordinator* job_coordinator() {
    return job_coordinator_.get();
  }

  
  ServiceWorkerProviderHost* GetProviderHost(int process_id, int provider_id);
  void AddProviderHost(scoped_ptr<ServiceWorkerProviderHost> provider_host);
  void RemoveProviderHost(int process_id, int provider_id);
  void RemoveAllProviderHostsForProcess(int process_id);
  scoped_ptr<ProviderHostIterator> GetProviderHostIterator();

  
  
  
  void RegisterServiceWorker(const GURL& pattern,
                             const GURL& script_url,
                             ServiceWorkerProviderHost* provider_host,
                             const RegistrationCallback& callback);
  void UnregisterServiceWorker(const GURL& pattern,
                               const UnregistrationCallback& callback);
  void UpdateServiceWorker(ServiceWorkerRegistration* registration);

  
  
  ServiceWorkerRegistration* GetLiveRegistration(int64 registration_id);
  void AddLiveRegistration(ServiceWorkerRegistration* registration);
  void RemoveLiveRegistration(int64 registration_id);
  ServiceWorkerVersion* GetLiveVersion(int64 version_id);
  void AddLiveVersion(ServiceWorkerVersion* version);
  void RemoveLiveVersion(int64 registration_id);

  std::vector<ServiceWorkerRegistrationInfo> GetAllLiveRegistrationInfo();
  std::vector<ServiceWorkerVersionInfo> GetAllLiveVersionInfo();

  
  int GetNewServiceWorkerHandleId();
  int GetNewRegistrationHandleId();

  void ScheduleDeleteAndStartOver() const;

  
  
  void DeleteAndStartOver(const StatusCallback& callback);

  void SetBlobParametersForCache(
      net::URLRequestContext* request_context,
      base::WeakPtr<storage::BlobStorageContext> blob_storage_context);

  base::WeakPtr<ServiceWorkerContextCore> AsWeakPtr() {
    return weak_factory_.GetWeakPtr();
  }

 private:
  typedef std::map<int64, ServiceWorkerRegistration*> RegistrationsMap;
  typedef std::map<int64, ServiceWorkerVersion*> VersionMap;

  ProviderMap* GetProviderMapForProcess(int process_id) {
    return providers_->Lookup(process_id);
  }

  void RegistrationComplete(const GURL& pattern,
                            const RegistrationCallback& callback,
                            ServiceWorkerStatusCode status,
                            ServiceWorkerRegistration* registration,
                            ServiceWorkerVersion* version);

  void UnregistrationComplete(const GURL& pattern,
                              const UnregistrationCallback& callback,
                              ServiceWorkerStatusCode status);

  base::WeakPtrFactory<ServiceWorkerContextCore> weak_factory_;
  
  
  
  ServiceWorkerContextWrapper* wrapper_;
  scoped_ptr<ProcessToProviderMap> providers_;
  scoped_ptr<ServiceWorkerStorage> storage_;
  scoped_ptr<ServiceWorkerCacheStorageManager> cache_manager_;
  scoped_refptr<EmbeddedWorkerRegistry> embedded_worker_registry_;
  scoped_ptr<ServiceWorkerJobCoordinator> job_coordinator_;
  std::map<int64, ServiceWorkerRegistration*> live_registrations_;
  std::map<int64, ServiceWorkerVersion*> live_versions_;
  int next_handle_id_;
  int next_registration_handle_id_;
  scoped_refptr<ObserverListThreadSafe<ServiceWorkerContextObserver> >
      observer_list_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerContextCore);
};

}  

#endif  
