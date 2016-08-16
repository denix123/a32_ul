// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_REGISTER_JOB_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_REGISTER_JOB_H_

#include <vector>

#include "base/memory/weak_ptr.h"
#include "content/browser/service_worker/embedded_worker_instance.h"
#include "content/browser/service_worker/service_worker_register_job_base.h"
#include "content/browser/service_worker/service_worker_registration.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "url/gurl.h"

namespace content {

class ServiceWorkerJobCoordinator;
class ServiceWorkerStorage;

class ServiceWorkerRegisterJob : public ServiceWorkerRegisterJobBase,
                                 public EmbeddedWorkerInstance::Listener,
                                 public ServiceWorkerRegistration::Listener {
 public:
  typedef base::Callback<void(ServiceWorkerStatusCode status,
                              ServiceWorkerRegistration* registration,
                              ServiceWorkerVersion* version)>
      RegistrationCallback;

  
  CONTENT_EXPORT ServiceWorkerRegisterJob(
      base::WeakPtr<ServiceWorkerContextCore> context,
      const GURL& pattern,
      const GURL& script_url);

  
  CONTENT_EXPORT ServiceWorkerRegisterJob(
      base::WeakPtr<ServiceWorkerContextCore> context,
      ServiceWorkerRegistration* registration);
  virtual ~ServiceWorkerRegisterJob();

  
  
  
  
  void AddCallback(const RegistrationCallback& callback,
                   ServiceWorkerProviderHost* provider_host);

  
  virtual void Start() OVERRIDE;
  virtual void Abort() OVERRIDE;
  virtual bool Equals(ServiceWorkerRegisterJobBase* job) OVERRIDE;
  virtual RegistrationJobType GetType() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerProviderHostWaitingVersionTest,
                           AssociateInstallingVersionToDocuments);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerProviderHostWaitingVersionTest,
                           DisassociateVersionFromDocuments);

  enum Phase {
    INITIAL,
    START,
    WAIT_FOR_UNINSTALL,
    REGISTER,
    UPDATE,
    INSTALL,
    STORE,
    COMPLETE,
    ABORT,
  };

  
  
  struct Internal {
    Internal();
    ~Internal();
    scoped_refptr<ServiceWorkerRegistration> registration;

    
    
    scoped_refptr<ServiceWorkerVersion> new_version;

    scoped_refptr<ServiceWorkerRegistration> uninstalling_registration;
  };

  void set_registration(
      const scoped_refptr<ServiceWorkerRegistration>& registration);
  ServiceWorkerRegistration* registration();
  void set_new_version(ServiceWorkerVersion* version);
  ServiceWorkerVersion* new_version();
  void set_uninstalling_registration(
      const scoped_refptr<ServiceWorkerRegistration>& registration);
  ServiceWorkerRegistration* uninstalling_registration();

  void SetPhase(Phase phase);

  void ContinueWithRegistration(
      ServiceWorkerStatusCode status,
      const scoped_refptr<ServiceWorkerRegistration>& registration);
  void ContinueWithUpdate(
      ServiceWorkerStatusCode status,
      const scoped_refptr<ServiceWorkerRegistration>& registration);
  void RegisterAndContinue(ServiceWorkerStatusCode status);
  void WaitForUninstall(
      const scoped_refptr<ServiceWorkerRegistration>& registration);
  void ContinueWithRegistrationForSameScriptUrl(
      const scoped_refptr<ServiceWorkerRegistration>& existing_registration,
      ServiceWorkerStatusCode status);
  void UpdateAndContinue();
  void OnStartWorkerFinished(ServiceWorkerStatusCode status);
  void OnStoreRegistrationComplete(ServiceWorkerStatusCode status);
  void InstallAndContinue();
  void OnInstallFinished(ServiceWorkerStatusCode status);
  void ActivateAndContinue();
  void OnActivateFinished(ServiceWorkerStatusCode status);
  void Complete(ServiceWorkerStatusCode status);
  void CompleteInternal(ServiceWorkerStatusCode status);
  void ResolvePromise(ServiceWorkerStatusCode status,
                      ServiceWorkerRegistration* registration,
                      ServiceWorkerVersion* version);

  
  virtual void OnPausedAfterDownload() OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void OnRegistrationFinishedUninstalling(
      ServiceWorkerRegistration* registration) OVERRIDE;

  void OnCompareScriptResourcesComplete(
      ServiceWorkerVersion* most_recent_version,
      ServiceWorkerStatusCode status,
      bool are_equal);

  void AssociateProviderHostsToRegistration(
      ServiceWorkerRegistration* registration);

  
  base::WeakPtr<ServiceWorkerContextCore> context_;

  RegistrationJobType job_type_;
  const GURL pattern_;
  const GURL script_url_;
  std::vector<RegistrationCallback> callbacks_;
  Phase phase_;
  Internal internal_;
  bool is_promise_resolved_;
  ServiceWorkerStatusCode promise_resolved_status_;
  scoped_refptr<ServiceWorkerRegistration> promise_resolved_registration_;
  scoped_refptr<ServiceWorkerVersion> promise_resolved_version_;
  base::WeakPtrFactory<ServiceWorkerRegisterJob> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerRegisterJob);
};

}  

#endif  
