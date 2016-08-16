// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_REGISTRATION_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_REGISTRATION_H_

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/service_worker/service_worker_version.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_types.h"
#include "url/gurl.h"

namespace content {

class ServiceWorkerRegistrationInfo;
class ServiceWorkerVersion;

class CONTENT_EXPORT ServiceWorkerRegistration
    : NON_EXPORTED_BASE(public base::RefCounted<ServiceWorkerRegistration>),
      public ServiceWorkerVersion::Listener {
 public:
  typedef base::Callback<void(ServiceWorkerStatusCode status)> StatusCallback;

  class Listener {
   public:
    virtual void OnVersionAttributesChanged(
        ServiceWorkerRegistration* registration,
        ChangedVersionAttributesMask changed_mask,
        const ServiceWorkerRegistrationInfo& info) {}
    virtual void OnRegistrationFailed(
        ServiceWorkerRegistration* registration) {}
    virtual void OnRegistrationFinishedUninstalling(
        ServiceWorkerRegistration* registration) {}
    virtual void OnUpdateFound(
        ServiceWorkerRegistration* registration) {}
  };

  ServiceWorkerRegistration(const GURL& pattern,
                            int64 registration_id,
                            base::WeakPtr<ServiceWorkerContextCore> context);

  int64 id() const { return registration_id_; }
  const GURL& pattern() const { return pattern_; }

  bool is_deleted() const { return is_deleted_; }
  void set_is_deleted(bool deleted) { is_deleted_ = deleted; }

  bool is_uninstalling() const { return is_uninstalling_; }
  bool is_uninstalled() const { return is_uninstalled_; }

  ServiceWorkerVersion* active_version() const {
    return active_version_.get();
  }

  ServiceWorkerVersion* waiting_version() const {
    return waiting_version_.get();
  }

  ServiceWorkerVersion* installing_version() const {
    return installing_version_.get();
  }

  ServiceWorkerVersion* GetNewestVersion() const;

  void AddListener(Listener* listener);
  void RemoveListener(Listener* listener);
  void NotifyRegistrationFailed();
  void NotifyUpdateFound();

  ServiceWorkerRegistrationInfo GetInfo();

  
  
  
  void SetActiveVersion(ServiceWorkerVersion* version);
  void SetWaitingVersion(ServiceWorkerVersion* version);
  void SetInstallingVersion(ServiceWorkerVersion* version);

  
  
  
  void UnsetVersion(ServiceWorkerVersion* version);

  
  
  
  void ActivateWaitingVersionWhenReady();

  
  
  
  void ClearWhenReady();

  
  
  void AbortPendingClear(const StatusCallback& callback);

  
  base::Time last_update_check() const { return last_update_check_; }
  void set_last_update_check(base::Time last) { last_update_check_ = last; }

 private:
  friend class base::RefCounted<ServiceWorkerRegistration>;

  virtual ~ServiceWorkerRegistration();

  void SetVersionInternal(
      ServiceWorkerVersion* version,
      scoped_refptr<ServiceWorkerVersion>* data_member,
      int change_flag);
  void UnsetVersionInternal(
      ServiceWorkerVersion* version,
      ChangedVersionAttributesMask* mask);

  
  virtual void OnNoControllees(ServiceWorkerVersion* version) OVERRIDE;

  
  void ActivateWaitingVersion();
  void OnActivateEventFinished(
      ServiceWorkerVersion* activating_version,
      ServiceWorkerStatusCode status);
  void OnDeleteFinished(ServiceWorkerStatusCode status);

  
  void Clear();

  void OnRestoreFinished(const StatusCallback& callback,
                         scoped_refptr<ServiceWorkerVersion> version,
                         ServiceWorkerStatusCode status);

  const GURL pattern_;
  const int64 registration_id_;
  bool is_deleted_;
  bool is_uninstalling_;
  bool is_uninstalled_;
  bool should_activate_when_ready_;
  base::Time last_update_check_;
  scoped_refptr<ServiceWorkerVersion> active_version_;
  scoped_refptr<ServiceWorkerVersion> waiting_version_;
  scoped_refptr<ServiceWorkerVersion> installing_version_;
  ObserverList<Listener> listeners_;
  base::WeakPtr<ServiceWorkerContextCore> context_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerRegistration);
};

}  

#endif  
