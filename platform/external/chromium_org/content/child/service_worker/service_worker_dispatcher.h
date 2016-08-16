// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_SERVICE_WORKER_SERVICE_WORKER_DISPATCHER_H_
#define CONTENT_CHILD_SERVICE_WORKER_SERVICE_WORKER_DISPATCHER_H_

#include <map>
#include <vector>

#include "base/id_map.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "content/child/worker_task_runner.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerError.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerProvider.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerState.h"

class GURL;

namespace blink {
class WebURL;
}

namespace IPC {
class Message;
}

namespace content {

class ServiceWorkerMessageFilter;
class ServiceWorkerProviderContext;
class ThreadSafeSender;
class WebServiceWorkerImpl;
class WebServiceWorkerRegistrationImpl;
struct ServiceWorkerObjectInfo;
struct ServiceWorkerRegistrationObjectInfo;
struct ServiceWorkerVersionAttributes;

class ServiceWorkerDispatcher : public WorkerTaskRunner::Observer {
 public:
  typedef blink::WebServiceWorkerProvider::WebServiceWorkerRegistrationCallbacks
      WebServiceWorkerRegistrationCallbacks;
  typedef
      blink::WebServiceWorkerProvider::WebServiceWorkerUnregistrationCallbacks
      WebServiceWorkerUnregistrationCallbacks;
  typedef
      blink::WebServiceWorkerProvider::WebServiceWorkerGetRegistrationCallbacks
      WebServiceWorkerGetRegistrationCallbacks;

  explicit ServiceWorkerDispatcher(ThreadSafeSender* thread_safe_sender);
  virtual ~ServiceWorkerDispatcher();

  void OnMessageReceived(const IPC::Message& msg);
  bool Send(IPC::Message* msg);

  
  void RegisterServiceWorker(
      int provider_id,
      const GURL& pattern,
      const GURL& script_url,
      WebServiceWorkerRegistrationCallbacks* callbacks);
  
  void UnregisterServiceWorker(
      int provider_id,
      const GURL& pattern,
      WebServiceWorkerUnregistrationCallbacks* callbacks);
  
  void GetRegistration(
      int provider_id,
      const GURL& document_url,
      WebServiceWorkerRegistrationCallbacks* callbacks);

  
  
  
  
  void AddProviderContext(ServiceWorkerProviderContext* provider_context);
  void RemoveProviderContext(ServiceWorkerProviderContext* provider_context);

  
  
  void AddScriptClient(int provider_id,
                       blink::WebServiceWorkerProviderClient* client);
  void RemoveScriptClient(int provider_id);

  
  
  
  
  
  
  
  
  
  
  
  
  
  WebServiceWorkerImpl* GetServiceWorker(
      const ServiceWorkerObjectInfo& info,
      bool adopt_handle);

  
  
  
  
  WebServiceWorkerRegistrationImpl* FindServiceWorkerRegistration(
      const ServiceWorkerRegistrationObjectInfo& info,
      bool adopt_handle);

  
  
  
  
  WebServiceWorkerRegistrationImpl* CreateServiceWorkerRegistration(
      const ServiceWorkerRegistrationObjectInfo& info,
      bool adopt_handle);

  
  
  static ServiceWorkerDispatcher* GetOrCreateThreadSpecificInstance(
      ThreadSafeSender* thread_safe_sender);

  
  
  static ServiceWorkerDispatcher* GetThreadSpecificInstance();

 private:
  typedef IDMap<WebServiceWorkerRegistrationCallbacks,
      IDMapOwnPointer> RegistrationCallbackMap;
  typedef IDMap<WebServiceWorkerUnregistrationCallbacks,
      IDMapOwnPointer> UnregistrationCallbackMap;
  typedef IDMap<WebServiceWorkerGetRegistrationCallbacks,
      IDMapOwnPointer> GetRegistrationCallbackMap;
  typedef std::map<int, blink::WebServiceWorkerProviderClient*> ScriptClientMap;
  typedef std::map<int, ServiceWorkerProviderContext*> ProviderContextMap;
  typedef std::map<int, WebServiceWorkerImpl*> WorkerObjectMap;
  typedef std::map<int, ServiceWorkerProviderContext*> WorkerToProviderMap;
  typedef std::map<int, WebServiceWorkerRegistrationImpl*>
      RegistrationObjectMap;

  friend class WebServiceWorkerImpl;
  friend class WebServiceWorkerRegistrationImpl;

  
  virtual void OnWorkerRunLoopStopped() OVERRIDE;

  void OnAssociateRegistration(int thread_id,
                               int provider_id,
                               const ServiceWorkerRegistrationObjectInfo& info,
                               const ServiceWorkerVersionAttributes& attrs);
  void OnDisassociateRegistration(int thread_id,
                                  int provider_id);
  void OnRegistered(int thread_id,
                    int request_id,
                    const ServiceWorkerRegistrationObjectInfo& info,
                    const ServiceWorkerVersionAttributes& attrs);
  void OnUnregistered(int thread_id,
                      int request_id,
                      bool is_success);
  void OnDidGetRegistration(int thread_id,
                            int request_id,
                            const ServiceWorkerRegistrationObjectInfo& info,
                            const ServiceWorkerVersionAttributes& attrs);
  void OnRegistrationError(int thread_id,
                           int request_id,
                           blink::WebServiceWorkerError::ErrorType error_type,
                           const base::string16& message);
  void OnUnregistrationError(int thread_id,
                             int request_id,
                             blink::WebServiceWorkerError::ErrorType error_type,
                             const base::string16& message);
  void OnGetRegistrationError(
      int thread_id,
      int request_id,
      blink::WebServiceWorkerError::ErrorType error_type,
      const base::string16& message);
  void OnServiceWorkerStateChanged(int thread_id,
                                   int handle_id,
                                   blink::WebServiceWorkerState state);
  void OnSetVersionAttributes(int thread_id,
                              int provider_id,
                              int registration_handle_id,
                              int changed_mask,
                              const ServiceWorkerVersionAttributes& attributes);
  void OnUpdateFound(int thread_id,
                     const ServiceWorkerRegistrationObjectInfo& info);
  void OnSetControllerServiceWorker(int thread_id,
                                    int provider_id,
                                    const ServiceWorkerObjectInfo& info);
  void OnPostMessage(int thread_id,
                     int provider_id,
                     const base::string16& message,
                     const std::vector<int>& sent_message_port_ids,
                     const std::vector<int>& new_routing_ids);

  void SetInstallingServiceWorker(
      int provider_id,
      int registration_handle_id,
      const ServiceWorkerObjectInfo& info);
  void SetWaitingServiceWorker(
      int provider_id,
      int registration_handle_id,
      const ServiceWorkerObjectInfo& info);
  void SetActiveServiceWorker(
      int provider_id,
      int registration_handle_id,
      const ServiceWorkerObjectInfo& info);
  void SetReadyRegistration(
      int provider_id,
      int registration_handle_id);

  
  void AddServiceWorker(int handle_id, WebServiceWorkerImpl* worker);
  void RemoveServiceWorker(int handle_id);

  
  void AddServiceWorkerRegistration(
      int registration_handle_id,
      WebServiceWorkerRegistrationImpl* registration);
  void RemoveServiceWorkerRegistration(
      int registration_handle_id);

  WebServiceWorkerRegistrationImpl* FindOrCreateRegistration(
      const ServiceWorkerRegistrationObjectInfo& info,
      const ServiceWorkerVersionAttributes& attrs);

  RegistrationCallbackMap pending_registration_callbacks_;
  UnregistrationCallbackMap pending_unregistration_callbacks_;
  GetRegistrationCallbackMap pending_get_registration_callbacks_;
  ScriptClientMap script_clients_;
  ProviderContextMap provider_contexts_;
  WorkerObjectMap service_workers_;
  RegistrationObjectMap registrations_;

  
  
  WorkerToProviderMap worker_to_provider_;

  scoped_refptr<ThreadSafeSender> thread_safe_sender_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerDispatcher);
};

}  

#endif  
