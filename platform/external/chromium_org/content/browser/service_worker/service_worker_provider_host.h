// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_PROVIDER_HOST_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_PROVIDER_HOST_H_

#include <set>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/service_worker/service_worker_registration.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_types.h"
#include "content/public/common/resource_type.h"

namespace IPC {
class Sender;
}

namespace storage {
class BlobStorageContext;
}

namespace content {

class ResourceRequestBody;
class ServiceWorkerContextCore;
class ServiceWorkerDispatcherHost;
class ServiceWorkerRequestHandler;
class ServiceWorkerVersion;

class CONTENT_EXPORT ServiceWorkerProviderHost
    : public NON_EXPORTED_BASE(ServiceWorkerRegistration::Listener),
      public base::SupportsWeakPtr<ServiceWorkerProviderHost> {
 public:
  ServiceWorkerProviderHost(int process_id,
                            int provider_id,
                            base::WeakPtr<ServiceWorkerContextCore> context,
                            ServiceWorkerDispatcherHost* dispatcher_host);
  virtual ~ServiceWorkerProviderHost();

  int process_id() const { return process_id_; }
  int provider_id() const { return provider_id_; }

  bool IsHostToRunningServiceWorker() {
    return running_hosted_version_.get() != NULL;
  }

  ServiceWorkerVersion* controlling_version() const {
    return controlling_version_.get();
  }
  ServiceWorkerVersion* active_version() const {
    return associated_registration_.get() ?
        associated_registration_->active_version() : NULL;
  }
  ServiceWorkerVersion* waiting_version() const {
    return associated_registration_.get() ?
        associated_registration_->waiting_version() : NULL;
  }
  ServiceWorkerVersion* installing_version() const {
    return associated_registration_.get() ?
        associated_registration_->installing_version() : NULL;
  }

  
  
  ServiceWorkerVersion* running_hosted_version() const {
    return running_hosted_version_.get();
  }

  void SetDocumentUrl(const GURL& url);
  const GURL& document_url() const { return document_url_; }

  
  void AssociateRegistration(ServiceWorkerRegistration* registration);

  
  void DisassociateRegistration();

  
  
  bool SetHostedVersionId(int64 versions_id);

  
  
  scoped_ptr<ServiceWorkerRequestHandler> CreateRequestHandler(
      ResourceType resource_type,
      base::WeakPtr<storage::BlobStorageContext> blob_storage_context,
      scoped_refptr<ResourceRequestBody> body);

  
  bool CanAssociateRegistration(ServiceWorkerRegistration* registration);

  
  
  
  void SetAllowAssociation(bool allow) { allow_association_ = allow; }

  
  
  bool IsContextAlive();

  
  void PostMessage(const base::string16& message,
                   const std::vector<int>& sent_message_port_ids);

  
  
  void AddScopedProcessReferenceToPattern(const GURL& pattern);

 private:
  friend class ServiceWorkerProviderHostTest;
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerContextRequestHandlerTest,
                           UpdateBefore24Hours);
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerContextRequestHandlerTest,
                           UpdateAfter24Hours);

  
  virtual void OnRegistrationFailed(
      ServiceWorkerRegistration* registration) OVERRIDE;

  
  
  void SetControllerVersionAttribute(ServiceWorkerVersion* version);

  
  
  
  ServiceWorkerObjectInfo CreateHandleAndPass(ServiceWorkerVersion* version);

  
  void IncreaseProcessReference(const GURL& pattern);
  void DecreaseProcessReference(const GURL& pattern);

  const int process_id_;
  const int provider_id_;
  GURL document_url_;

  std::vector<GURL> associated_patterns_;
  scoped_refptr<ServiceWorkerRegistration> associated_registration_;

  scoped_refptr<ServiceWorkerVersion> controlling_version_;
  scoped_refptr<ServiceWorkerVersion> running_hosted_version_;
  base::WeakPtr<ServiceWorkerContextCore> context_;
  ServiceWorkerDispatcherHost* dispatcher_host_;
  bool allow_association_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerProviderHost);
};

}  

#endif  
