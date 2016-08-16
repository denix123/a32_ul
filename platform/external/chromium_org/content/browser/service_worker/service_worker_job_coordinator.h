// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_JOB_COORDINATOR_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_JOB_COORDINATOR_H_

#include <deque>
#include <map>

#include "content/browser/service_worker/service_worker_register_job.h"
#include "content/browser/service_worker/service_worker_unregister_job.h"
#include "content/common/content_export.h"
#include "url/gurl.h"

namespace content {

class EmbeddedWorkerRegistry;
class ServiceWorkerProviderHost;
class ServiceWorkerRegistration;
class ServiceWorkerStorage;

class CONTENT_EXPORT ServiceWorkerJobCoordinator {
 public:
  explicit ServiceWorkerJobCoordinator(
      base::WeakPtr<ServiceWorkerContextCore> context);
  ~ServiceWorkerJobCoordinator();

  void Register(const GURL& pattern,
                const GURL& script_url,
                ServiceWorkerProviderHost* provider_host,
                const ServiceWorkerRegisterJob::RegistrationCallback& callback);

  void Unregister(
      const GURL& pattern,
      const ServiceWorkerUnregisterJob::UnregistrationCallback& callback);

  void Update(ServiceWorkerRegistration* registration);

  
  void AbortAll();

  
  
  void FinishJob(const GURL& pattern, ServiceWorkerRegisterJobBase* job);

 private:
  class JobQueue {
   public:
    JobQueue();
    ~JobQueue();

    
    
    
    ServiceWorkerRegisterJobBase* Push(
        scoped_ptr<ServiceWorkerRegisterJobBase> job);

    
    void Pop(ServiceWorkerRegisterJobBase* job);

    bool empty() { return jobs_.empty(); }

    
    void AbortAll();

    
    
    void ClearForShutdown();

   private:
    std::deque<ServiceWorkerRegisterJobBase*> jobs_;
  };

  typedef std::map<GURL, JobQueue> RegistrationJobMap;

  
  
  base::WeakPtr<ServiceWorkerContextCore> context_;
  RegistrationJobMap job_queues_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerJobCoordinator);
};

}  

#endif  
