// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_EMBEDDED_WORKER_INSTANCE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_EMBEDDED_WORKER_INSTANCE_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/gtest_prod_util.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "url/gurl.h"

struct EmbeddedWorkerMsg_StartWorker_Params;

namespace IPC {
class Message;
}

namespace content {

class EmbeddedWorkerRegistry;
class ServiceWorkerContextCore;
struct ServiceWorkerFetchRequest;

class CONTENT_EXPORT EmbeddedWorkerInstance {
 public:
  typedef base::Callback<void(ServiceWorkerStatusCode)> StatusCallback;
  enum Status {
    STOPPED,
    STARTING,
    RUNNING,
    STOPPING,
  };

  class Listener {
   public:
    virtual ~Listener() {}
    virtual void OnStarted() {}
    virtual void OnStopped() {}
    virtual void OnPausedAfterDownload() {}
    virtual void OnReportException(const base::string16& error_message,
                                   int line_number,
                                   int column_number,
                                   const GURL& source_url) {}
    virtual void OnReportConsoleMessage(int source_identifier,
                                        int message_level,
                                        const base::string16& message,
                                        int line_number,
                                        const GURL& source_url) {}
    
    
    
    virtual bool OnMessageReceived(const IPC::Message& message) = 0;
  };

  ~EmbeddedWorkerInstance();

  
  
  
  
  void Start(int64 service_worker_version_id,
             const GURL& scope,
             const GURL& script_url,
             bool pause_after_download,
             const StatusCallback& callback);

  
  
  
  
  ServiceWorkerStatusCode Stop();

  
  
  ServiceWorkerStatusCode SendMessage(const IPC::Message& message);

  void ResumeAfterDownload();

  int embedded_worker_id() const { return embedded_worker_id_; }
  Status status() const { return status_; }
  int process_id() const { return process_id_; }
  int thread_id() const { return thread_id_; }
  int worker_devtools_agent_route_id() const {
    return worker_devtools_agent_route_id_;
  }

  void AddListener(Listener* listener);
  void RemoveListener(Listener* listener);

 private:
  typedef ObserverList<Listener> ListenerList;

  friend class EmbeddedWorkerRegistry;
  FRIEND_TEST_ALL_PREFIXES(EmbeddedWorkerInstanceTest, StartAndStop);

  
  
  EmbeddedWorkerInstance(base::WeakPtr<ServiceWorkerContextCore> context,
                         int embedded_worker_id);

  
  
  static void RunProcessAllocated(
      base::WeakPtr<EmbeddedWorkerInstance> instance,
      base::WeakPtr<ServiceWorkerContextCore> context,
      scoped_ptr<EmbeddedWorkerMsg_StartWorker_Params> params,
      const EmbeddedWorkerInstance::StatusCallback& callback,
      ServiceWorkerStatusCode status,
      int process_id);
  void ProcessAllocated(scoped_ptr<EmbeddedWorkerMsg_StartWorker_Params> params,
                        const StatusCallback& callback,
                        int process_id,
                        ServiceWorkerStatusCode status);
  
  
  void SendStartWorker(scoped_ptr<EmbeddedWorkerMsg_StartWorker_Params> params,
                       const StatusCallback& callback,
                       int worker_devtools_agent_route_id,
                       bool wait_for_debugger);

  
  
  void OnReadyForInspection();

  
  
  void OnScriptLoaded(int thread_id);

  
  
  void OnScriptLoadFailed();

  
  
  
  void OnStarted();

  void OnPausedAfterDownload();

  
  
  
  
  void OnStopped();

  
  
  
  bool OnMessageReceived(const IPC::Message& message);

  
  void OnReportException(const base::string16& error_message,
                         int line_number,
                         int column_number,
                         const GURL& source_url);

  
  void OnReportConsoleMessage(int source_identifier,
                              int message_level,
                              const base::string16& message,
                              int line_number,
                              const GURL& source_url);

  base::WeakPtr<ServiceWorkerContextCore> context_;
  scoped_refptr<EmbeddedWorkerRegistry> registry_;
  const int embedded_worker_id_;
  Status status_;

  
  int process_id_;
  int thread_id_;
  int worker_devtools_agent_route_id_;

  ListenerList listener_list_;

  base::WeakPtrFactory<EmbeddedWorkerInstance> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(EmbeddedWorkerInstance);
};

}  

#endif  
