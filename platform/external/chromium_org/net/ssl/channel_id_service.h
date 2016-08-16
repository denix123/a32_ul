// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_CHANNEL_ID_SERVICE_H_
#define NET_SSL_CHANNEL_ID_SERVICE_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/time.h"
#include "net/base/completion_callback.h"
#include "net/base/net_export.h"
#include "net/ssl/channel_id_store.h"

namespace base {
class TaskRunner;
}

namespace net {

class ChannelIDServiceJob;
class ChannelIDServiceRequest;
class ChannelIDServiceWorker;


class NET_EXPORT ChannelIDService
    : NON_EXPORTED_BASE(public base::NonThreadSafe) {
 public:
  class NET_EXPORT RequestHandle {
   public:
    RequestHandle();
    ~RequestHandle();

    
    
    void Cancel();

    bool is_active() const { return request_ != NULL; }

   private:
    friend class ChannelIDService;

    void RequestStarted(ChannelIDService* service,
                        ChannelIDServiceRequest* request,
                        const CompletionCallback& callback);

    void OnRequestComplete(int result);

    ChannelIDService* service_;
    ChannelIDServiceRequest* request_;
    CompletionCallback callback_;
  };

  
  
  
  static const char kEPKIPassword[];

  
  
  
  ChannelIDService(
      ChannelIDStore* channel_id_store,
      const scoped_refptr<base::TaskRunner>& task_runner);

  ~ChannelIDService();

  
  
  
  static std::string GetDomainForHost(const std::string& host);

  
  
  
  
  bool IsSystemTimeValid() const { return is_system_time_valid_; }

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int GetOrCreateChannelID(
      const std::string& host,
      std::string* private_key,
      std::string* cert,
      const CompletionCallback& callback,
      RequestHandle* out_req);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int GetChannelID(
      const std::string& host,
      std::string* private_key,
      std::string* cert,
      const CompletionCallback& callback,
      RequestHandle* out_req);

  
  ChannelIDStore* GetChannelIDStore();

  
  int cert_count();
  uint64 requests() const { return requests_; }
  uint64 cert_store_hits() const { return cert_store_hits_; }
  uint64 inflight_joins() const { return inflight_joins_; }
  uint64 workers_created() const { return workers_created_; }

 private:
  
  
  
  void CancelRequest(ChannelIDServiceRequest* req);

  void GotChannelID(int err,
                    const std::string& server_identifier,
                    base::Time expiration_time,
                    const std::string& key,
                    const std::string& cert);
  void GeneratedChannelID(
      const std::string& server_identifier,
      int error,
      scoped_ptr<ChannelIDStore::ChannelID> channel_id);
  void HandleResult(int error,
                    const std::string& server_identifier,
                    const std::string& private_key,
                    const std::string& cert);

  
  
  
  bool JoinToInFlightRequest(const base::TimeTicks& request_start,
                             const std::string& domain,
                             std::string* private_key,
                             std::string* cert,
                             bool create_if_missing,
                             const CompletionCallback& callback,
                             RequestHandle* out_req);

  
  
  
  
  int LookupChannelID(const base::TimeTicks& request_start,
                      const std::string& domain,
                      std::string* private_key,
                      std::string* cert,
                      bool create_if_missing,
                      const CompletionCallback& callback,
                      RequestHandle* out_req);

  scoped_ptr<ChannelIDStore> channel_id_store_;
  scoped_refptr<base::TaskRunner> task_runner_;

  
  
  std::map<std::string, ChannelIDServiceJob*> inflight_;

  uint64 requests_;
  uint64 cert_store_hits_;
  uint64 inflight_joins_;
  uint64 workers_created_;

  bool is_system_time_valid_;

  base::WeakPtrFactory<ChannelIDService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChannelIDService);
};

}  

#endif  
