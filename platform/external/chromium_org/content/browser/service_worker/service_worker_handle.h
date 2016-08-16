// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_HANDLE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_HANDLE_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/service_worker/service_worker_version.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_types.h"

namespace IPC {
class Sender;
}

namespace content {

class ServiceWorkerContextCore;
class ServiceWorkerRegistration;

class CONTENT_EXPORT ServiceWorkerHandle
    : NON_EXPORTED_BASE(public ServiceWorkerVersion::Listener) {
 public:
  
  
  
  
  
  
  static scoped_ptr<ServiceWorkerHandle> Create(
      base::WeakPtr<ServiceWorkerContextCore> context,
      IPC::Sender* sender,
      int thread_id,
      int provider_id,
      ServiceWorkerVersion* version);

  ServiceWorkerHandle(base::WeakPtr<ServiceWorkerContextCore> context,
                      IPC::Sender* sender,
                      int thread_id,
                      int provider_id,
                      ServiceWorkerRegistration* registration,
                      ServiceWorkerVersion* version);
  virtual ~ServiceWorkerHandle();

  
  virtual void OnWorkerStarted(ServiceWorkerVersion* version) OVERRIDE;
  virtual void OnWorkerStopped(ServiceWorkerVersion* version) OVERRIDE;
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
  virtual void OnVersionStateChanged(ServiceWorkerVersion* version) OVERRIDE;

  ServiceWorkerObjectInfo GetObjectInfo();

  int thread_id() const { return thread_id_; }
  int provider_id() const { return provider_id_; }
  int handle_id() const { return handle_id_; }
  ServiceWorkerRegistration* registration() { return registration_.get(); }
  ServiceWorkerVersion* version() { return version_.get(); }

  bool HasNoRefCount() const { return ref_count_ <= 0; }
  void IncrementRefCount();
  void DecrementRefCount();

 private:
  base::WeakPtr<ServiceWorkerContextCore> context_;
  IPC::Sender* sender_;  
  const int thread_id_;
  const int provider_id_;
  const int handle_id_;
  int ref_count_;  
  scoped_refptr<ServiceWorkerRegistration> registration_;
  scoped_refptr<ServiceWorkerVersion> version_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerHandle);
};

}  

#endif  
