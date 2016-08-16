// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_VERSION_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_VERSION_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/id_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/timer/timer.h"
#include "content/browser/service_worker/embedded_worker_instance.h"
#include "content/browser/service_worker/service_worker_cache_listener.h"
#include "content/browser/service_worker/service_worker_script_cache_map.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "content/common/service_worker/service_worker_types.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerEventResult.h"

class GURL;

namespace content {

class EmbeddedWorkerRegistry;
class ServiceWorkerContextCore;
class ServiceWorkerProviderHost;
class ServiceWorkerRegistration;
class ServiceWorkerVersionInfo;

class CONTENT_EXPORT ServiceWorkerVersion
    : NON_EXPORTED_BASE(public base::RefCounted<ServiceWorkerVersion>),
      public EmbeddedWorkerInstance::Listener {
 public:
  typedef base::Callback<void(ServiceWorkerStatusCode)> StatusCallback;
  typedef base::Callback<void(ServiceWorkerStatusCode,
                              const IPC::Message& message)> MessageCallback;
  typedef base::Callback<void(ServiceWorkerStatusCode,
                              ServiceWorkerFetchEventResult,
                              const ServiceWorkerResponse&)> FetchCallback;

  enum RunningStatus {
    STOPPED = EmbeddedWorkerInstance::STOPPED,
    STARTING = EmbeddedWorkerInstance::STARTING,
    RUNNING = EmbeddedWorkerInstance::RUNNING,
    STOPPING = EmbeddedWorkerInstance::STOPPING,
  };

  
  
  enum Status {
    NEW,         
    INSTALLING,  
    INSTALLED,   
    ACTIVATING,  
    ACTIVATED,   
    REDUNDANT,   
                 
  };

  class Listener {
   public:
    virtual void OnWorkerStarted(ServiceWorkerVersion* version) {}
    virtual void OnWorkerStopped(ServiceWorkerVersion* version) {}
    virtual void OnVersionStateChanged(ServiceWorkerVersion* version) {}
    virtual void OnErrorReported(ServiceWorkerVersion* version,
                                 const base::string16& error_message,
                                 int line_number,
                                 int column_number,
                                 const GURL& source_url) {}
    virtual void OnReportConsoleMessage(ServiceWorkerVersion* version,
                                        int source_identifier,
                                        int message_level,
                                        const base::string16& message,
                                        int line_number,
                                        const GURL& source_url) {}
    
    virtual void OnNoControllees(ServiceWorkerVersion* version) {}

   protected:
    virtual ~Listener() {}
  };

  ServiceWorkerVersion(
      ServiceWorkerRegistration* registration,
      const GURL& script_url,
      int64 version_id,
      base::WeakPtr<ServiceWorkerContextCore> context);

  int64 version_id() const { return version_id_; }
  int64 registration_id() const { return registration_id_; }
  const GURL& script_url() const { return script_url_; }
  const GURL& scope() const { return scope_; }
  RunningStatus running_status() const {
    return static_cast<RunningStatus>(embedded_worker_->status());
  }
  ServiceWorkerVersionInfo GetInfo();
  Status status() const { return status_; }

  
  
  void SetStatus(Status status);

  
  
  
  void RegisterStatusChangeCallback(const base::Closure& callback);

  
  
  void StartWorker(const StatusCallback& callback);

  
  
  
  
  void StartWorker(bool pause_after_download,
                   const StatusCallback& callback);

  
  
  void StopWorker(const StatusCallback& callback);

  
  void ScheduleUpdate();

  
  
  void DeferScheduledUpdate();

  
  void StartUpdate();

  
  
  
  
  
  void SendMessage(const IPC::Message& message, const StatusCallback& callback);

  
  
  
  
  
  
  
  
  
  
  void DispatchInstallEvent(int active_version_id,
                            const StatusCallback& callback);

  
  
  
  
  
  
  
  
  void DispatchActivateEvent(const StatusCallback& callback);

  
  
  
  
  
  void DispatchFetchEvent(const ServiceWorkerFetchRequest& request,
                          const base::Closure& prepare_callback,
                          const FetchCallback& fetch_callback);

  
  
  
  
  
  void DispatchSyncEvent(const StatusCallback& callback);

  
  
  
  
  
  void DispatchPushEvent(const StatusCallback& callback,
                         const std::string& data);

  
  
  
  void AddControllee(ServiceWorkerProviderHost* provider_host);
  void RemoveControllee(ServiceWorkerProviderHost* provider_host);

  
  bool HasControllee() const { return !controllee_map_.empty(); }

  
  void AddListener(Listener* listener);
  void RemoveListener(Listener* listener);

  ServiceWorkerScriptCacheMap* script_cache_map() { return &script_cache_map_; }
  EmbeddedWorkerInstance* embedded_worker() { return embedded_worker_.get(); }

  
  
  
  void Doom();
  bool is_doomed() const { return is_doomed_; }

 private:
  friend class base::RefCounted<ServiceWorkerVersion>;
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerControlleeRequestHandlerTest,
                           ActivateWaitingVersion);
  typedef ServiceWorkerVersion self;
  typedef std::map<ServiceWorkerProviderHost*, int> ControlleeMap;
  typedef IDMap<ServiceWorkerProviderHost> ControlleeByIDMap;
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerVersionTest, ScheduleStopWorker);

  virtual ~ServiceWorkerVersion();

  
  virtual void OnStarted() OVERRIDE;
  virtual void OnStopped() OVERRIDE;
  virtual void OnReportException(const base::string16& error_message,
                                 int line_number,
                                 int column_number,
                                 const GURL& source_url) OVERRIDE;
  virtual void OnReportConsoleMessage(int source_identifier,
                                      int message_level,
                                      const base::string16& message,
                                      int line_number,
                                      const GURL& source_url) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  void RunStartWorkerCallbacksOnError(ServiceWorkerStatusCode status);

  void DispatchInstallEventAfterStartWorker(int active_version_id,
                                            const StatusCallback& callback);
  void DispatchActivateEventAfterStartWorker(const StatusCallback& callback);

  
  void OnGetClientDocuments(int request_id);
  void OnActivateEventFinished(int request_id,
                               blink::WebServiceWorkerEventResult result);
  void OnInstallEventFinished(int request_id,
                              blink::WebServiceWorkerEventResult result);
  void OnFetchEventFinished(int request_id,
                            ServiceWorkerFetchEventResult result,
                            const ServiceWorkerResponse& response);
  void OnSyncEventFinished(int request_id);
  void OnPushEventFinished(int request_id);
  void OnPostMessageToDocument(int client_id,
                               const base::string16& message,
                               const std::vector<int>& sent_message_port_ids);

  void ScheduleStopWorker();
  void DoomInternal();

  const int64 version_id_;
  int64 registration_id_;
  GURL script_url_;
  GURL scope_;
  Status status_;
  scoped_ptr<EmbeddedWorkerInstance> embedded_worker_;
  scoped_ptr<ServiceWorkerCacheListener> cache_listener_;
  std::vector<StatusCallback> start_callbacks_;
  std::vector<StatusCallback> stop_callbacks_;
  std::vector<base::Closure> status_change_callbacks_;

  
  IDMap<StatusCallback, IDMapOwnPointer> activate_callbacks_;
  IDMap<StatusCallback, IDMapOwnPointer> install_callbacks_;
  IDMap<FetchCallback, IDMapOwnPointer> fetch_callbacks_;
  IDMap<StatusCallback, IDMapOwnPointer> sync_callbacks_;
  IDMap<StatusCallback, IDMapOwnPointer> push_callbacks_;

  ControlleeMap controllee_map_;
  ControlleeByIDMap controllee_by_id_;
  base::WeakPtr<ServiceWorkerContextCore> context_;
  ObserverList<Listener> listeners_;
  ServiceWorkerScriptCacheMap script_cache_map_;
  base::OneShotTimer<ServiceWorkerVersion> stop_worker_timer_;
  base::OneShotTimer<ServiceWorkerVersion> update_timer_;
  bool is_doomed_;

  base::WeakPtrFactory<ServiceWorkerVersion> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerVersion);
};

}  

#endif  
