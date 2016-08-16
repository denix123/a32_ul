// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_LOADER_RESOURCE_SCHEDULER_H_
#define CONTENT_BROWSER_LOADER_RESOURCE_SCHEDULER_H_

#include <map>
#include <set>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/timer/timer.h"
#include "content/common/content_export.h"
#include "net/base/priority_queue.h"
#include "net/base/request_priority.h"

namespace net {
class HostPortPair;
class URLRequest;
}

namespace content {
class ResourceThrottle;

class CONTENT_EXPORT ResourceScheduler : public base::NonThreadSafe {
 public:
  enum ClientThrottleState {
    
    
    
    
    
    

    
    
    
    PAUSED,
    
    COALESCED,
    
    THROTTLED,
    
    
    
    
    UNTHROTTLED,
    
    ACTIVE_AND_LOADING,
  };

  enum RequestClassification {
    NORMAL_REQUEST,
    
    IN_FLIGHT_DELAYABLE_REQUEST,
    
    LAYOUT_BLOCKING_REQUEST,
  };

  ResourceScheduler();
  ~ResourceScheduler();

  
  void set_timer_for_testing(scoped_ptr<base::Timer> timer) {
    coalescing_timer_.reset(timer.release());
  }

  
  void SetThrottleOptionsForTesting(bool should_throttle, bool should_coalesce);

  bool should_coalesce() const { return should_coalesce_; }
  bool should_throttle() const { return should_throttle_; }

  ClientThrottleState GetClientStateForTesting(int child_id, int route_id);

  
  
  
  scoped_ptr<ResourceThrottle> ScheduleRequest(
      int child_id, int route_id, net::URLRequest* url_request);

  

  
  void OnClientCreated(int child_id, int route_id, bool is_visible);

  
  void OnClientDeleted(int child_id, int route_id);

  
  void OnLoadingStateChanged(int child_id, int route_id, bool is_loaded);

  
  void OnVisibilityChanged(int child_id, int route_id, bool is_visible);

  

  
  void OnNavigate(int child_id, int route_id);

  
  
  void OnWillInsertBody(int child_id, int route_id);

  

  
  
  void OnReceivedSpdyProxiedHttpResponse(int child_id, int route_id);

  

  
  bool active_clients_loaded() const { return active_clients_loading_ == 0; }

  
  void OnAudibilityChanged(int child_id, int route_id, bool is_audible);

  bool IsClientVisibleForTesting(int child_id, int route_id);

 private:
  class RequestQueue;
  class ScheduledResourceRequest;
  struct RequestPriorityParams;
  struct ScheduledResourceSorter {
    bool operator()(const ScheduledResourceRequest* a,
                    const ScheduledResourceRequest* b) const;
  };
  class Client;

  typedef int64 ClientId;
  typedef std::map<ClientId, Client*> ClientMap;
  typedef std::set<ScheduledResourceRequest*> RequestSet;

  
  void RemoveRequest(ScheduledResourceRequest* request);

  
  
  
  void IncrementActiveClientsLoading();
  
  
  void DecrementActiveClientsLoading();

  void OnLoadingActiveClientsStateChangedForAllClients();

  size_t CountActiveClientsLoading() const;

  
  void IncrementCoalescedClients();
  
  void DecrementCoalescedClients();

  void LoadCoalescedRequests();

  size_t CountCoalescedClients() const;

  
  
  
  
  
  
  void ReprioritizeRequest(ScheduledResourceRequest* request,
                           net::RequestPriority new_priority,
                           int intra_priority_value);

  
  ClientId MakeClientId(int child_id, int route_id);

  
  Client* GetClient(int child_id, int route_id);

  bool should_coalesce_;
  bool should_throttle_;
  ClientMap client_map_;
  size_t active_clients_loading_;
  size_t coalesced_clients_;
  
  scoped_ptr<base::Timer> coalescing_timer_;
  RequestSet unowned_requests_;
};

}  

#endif  
