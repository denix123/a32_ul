// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_SERVICE_WORKER_SERVICE_WORKER_PROVIDER_CONTEXT_H_
#define CONTENT_CHILD_SERVICE_WORKER_SERVICE_WORKER_PROVIDER_CONTEXT_H_

#include <set>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/sequenced_task_runner_helpers.h"
#include "base/synchronization/lock.h"
#include "content/common/service_worker/service_worker_types.h"

namespace base {
class MessageLoopProxy;
}

namespace IPC {
class Message;
}

namespace content {

class ServiceWorkerHandleReference;
class ServiceWorkerRegistrationHandleReference;
struct ServiceWorkerProviderContextDeleter;
class ThreadSafeSender;

class ServiceWorkerProviderContext
    : public base::RefCounted<ServiceWorkerProviderContext> {
 public:
  explicit ServiceWorkerProviderContext(int provider_id);

  
  void OnAssociateRegistration(const ServiceWorkerRegistrationObjectInfo& info,
                               const ServiceWorkerVersionAttributes& attrs);
  void OnDisassociateRegistration();
  void OnServiceWorkerStateChanged(int handle_id,
                                   blink::WebServiceWorkerState state);
  void OnSetInstallingServiceWorker(int registration_handle_id,
                                    const ServiceWorkerObjectInfo& info);
  void OnSetWaitingServiceWorker(int registration_handle_id,
                                 const ServiceWorkerObjectInfo& info);
  void OnSetActiveServiceWorker(int registration_handle_id,
                                const ServiceWorkerObjectInfo& info);
  void OnSetControllerServiceWorker(int registration_handle_id,
                                    const ServiceWorkerObjectInfo& info);

  int provider_id() const { return provider_id_; }

  ServiceWorkerHandleReference* installing();
  ServiceWorkerHandleReference* waiting();
  ServiceWorkerHandleReference* active();
  ServiceWorkerHandleReference* controller();
  ServiceWorkerRegistrationHandleReference* registration();

  ServiceWorkerVersionAttributes GetVersionAttributes();

  
  
  
  int installing_handle_id() const;

  
  
  
  int waiting_handle_id() const;

  
  
  
  int active_handle_id() const;

  
  
  
  int controller_handle_id() const;

  
  
  
  int registration_handle_id() const;

 private:
  friend class base::RefCounted<ServiceWorkerProviderContext>;
  ~ServiceWorkerProviderContext();

  bool IsAssociatedWithRegistration(int registration_handle_id) const;

  const int provider_id_;
  scoped_refptr<base::MessageLoopProxy> main_thread_loop_proxy_;
  scoped_refptr<ThreadSafeSender> thread_safe_sender_;
  scoped_ptr<ServiceWorkerHandleReference> installing_;
  scoped_ptr<ServiceWorkerHandleReference> waiting_;
  scoped_ptr<ServiceWorkerHandleReference> active_;
  scoped_ptr<ServiceWorkerHandleReference> controller_;
  scoped_ptr<ServiceWorkerRegistrationHandleReference> registration_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerProviderContext);
};

}  

#endif  
