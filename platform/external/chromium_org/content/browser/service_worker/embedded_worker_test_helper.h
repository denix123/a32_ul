// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_EMBEDDED_WORKER_TEST_HELPER_H_
#define CONTENT_BROWSER_SERVICE_WORKER_EMBEDDED_WORKER_TEST_HELPER_H_

#include <vector>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_test_sink.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

struct EmbeddedWorkerMsg_StartWorker_Params;
class GURL;

namespace content {

class EmbeddedWorkerRegistry;
class EmbeddedWorkerTestHelper;
class ServiceWorkerContextCore;
class ServiceWorkerContextWrapper;
struct ServiceWorkerFetchRequest;

class EmbeddedWorkerTestHelper : public IPC::Sender,
                                 public IPC::Listener {
 public:
  
  
  explicit EmbeddedWorkerTestHelper(int mock_render_process_id);
  virtual ~EmbeddedWorkerTestHelper();

  
  
  void SimulateAddProcessToPattern(const GURL& pattern, int process_id);

  
  virtual bool Send(IPC::Message* message) OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  IPC::TestSink* ipc_sink() { return &sink_; }
  
  IPC::TestSink* inner_ipc_sink() { return &inner_sink_; }

  ServiceWorkerContextCore* context();
  ServiceWorkerContextWrapper* context_wrapper() { return wrapper_.get(); }
  void ShutdownContext();

  int mock_render_process_id() const { return mock_render_process_id_;}

 protected:
  
  
  
  
  
  
  virtual void OnStartWorker(int embedded_worker_id,
                             int64 service_worker_version_id,
                             const GURL& scope,
                             const GURL& script_url,
                             bool pause_after_download);
  virtual void OnResumeAfterDownload(int embedded_worker_id);
  virtual void OnStopWorker(int embedded_worker_id);
  virtual bool OnMessageToWorker(int thread_id,
                                 int embedded_worker_id,
                                 const IPC::Message& message);

  
  
  
  
  virtual void OnActivateEvent(int embedded_worker_id, int request_id);
  virtual void OnInstallEvent(int embedded_worker_id,
                              int request_id,
                              int active_version_id);
  virtual void OnFetchEvent(int embedded_worker_id,
                            int request_id,
                            const ServiceWorkerFetchRequest& request);

  
  
  void SimulatePausedAfterDownload(int embedded_worker_id);
  void SimulateWorkerReadyForInspection(int embedded_worker_id);
  void SimulateWorkerScriptLoaded(int thread_id, int embedded_worker_id);
  void SimulateWorkerStarted(int embedded_worker_id);
  void SimulateWorkerStopped(int embedded_worker_id);
  void SimulateSend(IPC::Message* message);

  EmbeddedWorkerRegistry* registry();

 private:
  void OnStartWorkerStub(const EmbeddedWorkerMsg_StartWorker_Params& params);
  void OnResumeAfterDownloadStub(int embedded_worker_id);
  void OnStopWorkerStub(int embedded_worker_id);
  void OnMessageToWorkerStub(int thread_id,
                             int embedded_worker_id,
                             const IPC::Message& message);
  void OnActivateEventStub(int request_id);
  void OnInstallEventStub(int request_id, int active_version_id);
  void OnFetchEventStub(int request_id,
                        const ServiceWorkerFetchRequest& request);

  scoped_refptr<ServiceWorkerContextWrapper> wrapper_;

  IPC::TestSink sink_;
  IPC::TestSink inner_sink_;

  int next_thread_id_;
  int mock_render_process_id_;

  
  int current_embedded_worker_id_;

  base::WeakPtrFactory<EmbeddedWorkerTestHelper> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(EmbeddedWorkerTestHelper);
};

}  

#endif  
