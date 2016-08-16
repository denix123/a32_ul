// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_PROCESS_MANAGER_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_PROCESS_MANAGER_H_

#include <map>
#include <vector>

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/common/service_worker/service_worker_status_code.h"

class GURL;

namespace content {

class BrowserContext;
class SiteInstance;

class CONTENT_EXPORT ServiceWorkerProcessManager {
 public:
  
  
  explicit ServiceWorkerProcessManager(BrowserContext* browser_context);

  
  ~ServiceWorkerProcessManager();

  
  
  void Shutdown();

  
  
  
  
  
  
  void AllocateWorkerProcess(
      int embedded_worker_id,
      const GURL& pattern,
      const GURL& script_url,
      const base::Callback<void(ServiceWorkerStatusCode, int process_id)>&
          callback);

  
  
  void ReleaseWorkerProcess(int embedded_worker_id);

  
  
  
  
  
  void SetProcessIdForTest(int process_id) {
    process_id_for_test_ = process_id;
  }

  
  
  void AddProcessReferenceToPattern(const GURL& pattern, int process_id);
  void RemoveProcessReferenceFromPattern(const GURL& pattern, int process_id);

  
  bool PatternHasProcessToRun(const GURL& pattern) const;

 private:
  FRIEND_TEST_ALL_PREFIXES(ServiceWorkerProcessManagerTest, SortProcess);

  
  struct ProcessInfo {
    explicit ProcessInfo(const scoped_refptr<SiteInstance>& site_instance);
    explicit ProcessInfo(int process_id);
    ~ProcessInfo();

    
    
    
    scoped_refptr<SiteInstance> site_instance;

    
    
    
    
    int process_id;
  };

  
  typedef std::map<int, int> ProcessRefMap;

  
  typedef std::map<const GURL, ProcessRefMap> PatternProcessRefMap;

  
  std::vector<int> SortProcessesForPattern(const GURL& pattern) const;

  
  BrowserContext* browser_context_;

  
  
  
  
  
  
  
  std::map<int, ProcessInfo> instance_info_;

  
  
  int process_id_for_test_;

  
  
  PatternProcessRefMap pattern_processes_;

  
  base::WeakPtrFactory<ServiceWorkerProcessManager> weak_this_factory_;
  const base::WeakPtr<ServiceWorkerProcessManager> weak_this_;
};

}  

namespace base {
template <>
struct CONTENT_EXPORT DefaultDeleter<content::ServiceWorkerProcessManager> {
  void operator()(content::ServiceWorkerProcessManager* ptr) const;
};
}  

#endif  
