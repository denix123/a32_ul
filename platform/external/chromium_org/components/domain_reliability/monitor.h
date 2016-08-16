// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOMAIN_RELIABILITY_MONITOR_H_
#define COMPONENTS_DOMAIN_RELIABILITY_MONITOR_H_

#include <map>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/single_thread_task_runner.h"
#include "base/time/time.h"
#include "components/domain_reliability/beacon.h"
#include "components/domain_reliability/clear_mode.h"
#include "components/domain_reliability/config.h"
#include "components/domain_reliability/context.h"
#include "components/domain_reliability/dispatcher.h"
#include "components/domain_reliability/domain_reliability_export.h"
#include "components/domain_reliability/scheduler.h"
#include "components/domain_reliability/uploader.h"
#include "components/domain_reliability/util.h"
#include "net/base/load_timing_info.h"
#include "net/http/http_response_info.h"
#include "net/url_request/url_request_status.h"

namespace base {
class ThreadChecker;
class Value;
}  

namespace net {
class URLRequest;
class URLRequestContext;
class URLRequestContextGetter;
}  

namespace domain_reliability {

class DOMAIN_RELIABILITY_EXPORT DomainReliabilityMonitor {
 public:
  
  
  
  DomainReliabilityMonitor(
      const std::string& upload_reporter_string,
      scoped_refptr<base::SingleThreadTaskRunner> pref_thread,
      scoped_refptr<base::SingleThreadTaskRunner> network_thread);

  
  DomainReliabilityMonitor(
      const std::string& upload_reporter_string,
      scoped_refptr<base::SingleThreadTaskRunner> pref_thread,
      scoped_refptr<base::SingleThreadTaskRunner> network_thread,
      scoped_ptr<MockableTime> time);

  
  
  ~DomainReliabilityMonitor();

  
  
  
  void MoveToNetworkThread();

  
  

  
  
  
  void InitURLRequestContext(net::URLRequestContext* url_request_context);

  
  void InitURLRequestContext(
      scoped_refptr<net::URLRequestContextGetter> url_request_context_getter);

  
  void AddBakedInConfigs();

  
  
  void SetDiscardUploads(bool discard_uploads);

  
  
  
  void OnBeforeRedirect(net::URLRequest* request);

  
  
  
  
  void OnCompleted(net::URLRequest* request, bool started);

  
  
  
  void ClearBrowsingData(DomainReliabilityClearMode mode);

  
  
  scoped_ptr<base::Value> GetWebUIData() const;

  DomainReliabilityContext* AddContextForTesting(
      scoped_ptr<const DomainReliabilityConfig> config);

  size_t contexts_size_for_testing() const { return contexts_.size(); }

 private:
  friend class DomainReliabilityMonitorTest;
  
  friend class DomainReliabilityServiceImpl;

  typedef std::map<std::string, DomainReliabilityContext*> ContextMap;

  struct DOMAIN_RELIABILITY_EXPORT RequestInfo {
    RequestInfo();
    explicit RequestInfo(const net::URLRequest& request);
    ~RequestInfo();

    bool AccessedNetwork() const;

    GURL url;
    net::URLRequestStatus status;
    net::HttpResponseInfo response_info;
    int load_flags;
    net::LoadTimingInfo load_timing_info;
    bool is_upload;
  };

  
  
  DomainReliabilityContext* AddContext(
      scoped_ptr<const DomainReliabilityConfig> config);
  
  void ClearContexts();
  void OnRequestLegComplete(const RequestInfo& info);

  DomainReliabilityContext* GetContextForHost(const std::string& host) const;

  bool OnPrefThread() const {
    return pref_task_runner_->BelongsToCurrentThread();
  }
  bool OnNetworkThread() const {
    return network_task_runner_->BelongsToCurrentThread();
  }

  base::WeakPtr<DomainReliabilityMonitor> MakeWeakPtr();

  scoped_ptr<MockableTime> time_;
  const std::string upload_reporter_string_;
  DomainReliabilityScheduler::Params scheduler_params_;
  DomainReliabilityDispatcher dispatcher_;
  scoped_ptr<DomainReliabilityUploader> uploader_;
  ContextMap contexts_;

  scoped_refptr<base::SingleThreadTaskRunner> pref_task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> network_task_runner_;

  bool moved_to_network_thread_;
  bool discard_uploads_set_;

  base::WeakPtrFactory<DomainReliabilityMonitor> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DomainReliabilityMonitor);
};

}  

#endif  
