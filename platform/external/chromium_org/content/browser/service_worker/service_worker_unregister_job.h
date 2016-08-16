// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_UNREGISTER_JOB_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_UNREGISTER_JOB_H_

#include <vector>

#include "base/memory/weak_ptr.h"
#include "content/browser/service_worker/service_worker_register_job_base.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "url/gurl.h"

namespace content {

class EmbeddedWorkerRegistry;
class ServiceWorkerContextCore;
class ServiceWorkerJobCoordinator;
class ServiceWorkerRegistration;
class ServiceWorkerStorage;

class ServiceWorkerUnregisterJob : public ServiceWorkerRegisterJobBase {
 public:
  typedef base::Callback<void(ServiceWorkerStatusCode status)>
      UnregistrationCallback;

  ServiceWorkerUnregisterJob(base::WeakPtr<ServiceWorkerContextCore> context,
                             const GURL& pattern);
  virtual ~ServiceWorkerUnregisterJob();

  
  
  void AddCallback(const UnregistrationCallback& callback);

  
  virtual void Start() OVERRIDE;
  virtual void Abort() OVERRIDE;
  virtual bool Equals(ServiceWorkerRegisterJobBase* job) OVERRIDE;
  virtual RegistrationJobType GetType() OVERRIDE;

 private:
  void OnRegistrationFound(
      ServiceWorkerStatusCode status,
      const scoped_refptr<ServiceWorkerRegistration>& registration);
  void Complete(ServiceWorkerStatusCode status);
  void CompleteInternal(ServiceWorkerStatusCode status);
  void ResolvePromise(ServiceWorkerStatusCode status);

  base::WeakPtr<ServiceWorkerContextCore> context_;
  const GURL pattern_;
  std::vector<UnregistrationCallback> callbacks_;
  bool is_promise_resolved_;
  base::WeakPtrFactory<ServiceWorkerUnregisterJob> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerUnregisterJob);
};
}  

#endif  
