// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVTOOLS_EMBEDDED_WORKER_DEVTOOLS_MANAGER_H_
#define CONTENT_BROWSER_DEVTOOLS_EMBEDDED_WORKER_DEVTOOLS_MANAGER_H_

#include <map>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "content/browser/shared_worker/shared_worker_instance.h"
#include "content/common/content_export.h"

namespace content {

class DevToolsAgentHost;
class DevToolsAgentHostImpl;
class EmbeddedWorkerDevToolsAgentHost;
class ServiceWorkerContextCore;

class CONTENT_EXPORT EmbeddedWorkerDevToolsManager {
 public:
  typedef std::pair<int, int> WorkerId;

  class ServiceWorkerIdentifier {
   public:
    ServiceWorkerIdentifier(
        const ServiceWorkerContextCore* context,
        base::WeakPtr<ServiceWorkerContextCore> context_weak,
        int64 version_id,
        const GURL& url);
    ServiceWorkerIdentifier(const ServiceWorkerIdentifier& other);
    ~ServiceWorkerIdentifier();

    bool Matches(const ServiceWorkerIdentifier& other) const;

    const ServiceWorkerContextCore* context() const;
    base::WeakPtr<ServiceWorkerContextCore> context_weak() const;
    int64 version_id() const;
    GURL url() const;

   private:
    const ServiceWorkerContextCore* const context_;
    const base::WeakPtr<ServiceWorkerContextCore> context_weak_;
    const int64 version_id_;
    const GURL url_;
  };

  
  static EmbeddedWorkerDevToolsManager* GetInstance();

  DevToolsAgentHostImpl* GetDevToolsAgentHostForWorker(int worker_process_id,
                                                   int worker_route_id);

  std::vector<scoped_refptr<DevToolsAgentHost> > GetOrCreateAllAgentHosts();

  
  
  bool SharedWorkerCreated(int worker_process_id,
                           int worker_route_id,
                           const SharedWorkerInstance& instance);
  
  
  
  bool ServiceWorkerCreated(int worker_process_id,
                            int worker_route_id,
                            const ServiceWorkerIdentifier& service_worker_id);
  void WorkerReadyForInspection(int worker_process_id, int worker_route_id);
  void WorkerContextStarted(int worker_process_id, int worker_route_id);
  void WorkerDestroyed(int worker_process_id, int worker_route_id);

  void set_debug_service_worker_on_start(bool debug_on_start) {
    debug_service_worker_on_start_ = debug_on_start;
  }
  bool debug_service_worker_on_start() const {
    return debug_service_worker_on_start_;
  }

 private:
  friend struct DefaultSingletonTraits<EmbeddedWorkerDevToolsManager>;
  friend class EmbeddedWorkerDevToolsAgentHost;
  friend class EmbeddedWorkerDevToolsManagerTest;
  FRIEND_TEST_ALL_PREFIXES(EmbeddedWorkerDevToolsManagerTest, BasicTest);
  FRIEND_TEST_ALL_PREFIXES(EmbeddedWorkerDevToolsManagerTest, AttachTest);

  typedef std::map<WorkerId, EmbeddedWorkerDevToolsAgentHost*> AgentHostMap;

  EmbeddedWorkerDevToolsManager();
  virtual ~EmbeddedWorkerDevToolsManager();

  void RemoveInspectedWorkerData(WorkerId id);

  AgentHostMap::iterator FindExistingSharedWorkerAgentHost(
      const SharedWorkerInstance& instance);
  AgentHostMap::iterator FindExistingServiceWorkerAgentHost(
      const ServiceWorkerIdentifier& service_worker_id);

  void WorkerRestarted(const WorkerId& id, const AgentHostMap::iterator& it);

  
  void ResetForTesting();

  AgentHostMap workers_;

  bool debug_service_worker_on_start_;

  DISALLOW_COPY_AND_ASSIGN(EmbeddedWorkerDevToolsManager);
};

}  

#endif  
