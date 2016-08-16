// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_SERVICE_WORKER_SERVICE_WORKER_NETWORK_PROVIDER_H_
#define CONTENT_CHILD_SERVICE_WORKER_SERVICE_WORKER_NETWORK_PROVIDER_H_

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/supports_user_data.h"
#include "content/common/content_export.h"

namespace content {

class ServiceWorkerProviderContext;

class CONTENT_EXPORT ServiceWorkerNetworkProvider
    : public base::SupportsUserData::Data {
 public:
  
  static void AttachToDocumentState(
      base::SupportsUserData* document_state,
      scoped_ptr<ServiceWorkerNetworkProvider> network_provider);

  static ServiceWorkerNetworkProvider* FromDocumentState(
      base::SupportsUserData* document_state);

  ServiceWorkerNetworkProvider();
  virtual ~ServiceWorkerNetworkProvider();

  int provider_id() const { return provider_id_; }
  ServiceWorkerProviderContext* context() { return context_.get(); }

  
  
  
  void SetServiceWorkerVersionId(int64 version_id);

 private:
  const int provider_id_;
  scoped_refptr<ServiceWorkerProviderContext> context_;
  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerNetworkProvider);
};

}  

#endif  
