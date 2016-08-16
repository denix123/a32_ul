// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_CHECKIN_REQUEST_H_
#define GOOGLE_APIS_GCM_ENGINE_CHECKIN_REQUEST_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "google_apis/gcm/base/gcm_export.h"
#include "google_apis/gcm/protocol/android_checkin.pb.h"
#include "google_apis/gcm/protocol/checkin.pb.h"
#include "net/base/backoff_entry.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}

namespace gcm {

class GCMStatsRecorder;

class GCM_EXPORT CheckinRequest : public net::URLFetcherDelegate {
 public:
  
  
  typedef base::Callback<void(const checkin_proto::AndroidCheckinResponse&
                                  checkin_response)> CheckinRequestCallback;

  
  struct GCM_EXPORT RequestInfo {
    RequestInfo(uint64 android_id,
                uint64 security_token,
                const std::map<std::string, std::string>& account_tokens,
                const std::string& settings_digest,
                const checkin_proto::ChromeBuildProto& chrome_build_proto);
    ~RequestInfo();

    
    uint64 android_id;
    
    uint64 security_token;
    
    std::map<std::string, std::string> account_tokens;
    
    std::string settings_digest;
    
    checkin_proto::ChromeBuildProto chrome_build_proto;
  };

  CheckinRequest(const GURL& checkin_url,
                 const RequestInfo& request_info,
                 const net::BackoffEntry::Policy& backoff_policy,
                 const CheckinRequestCallback& callback,
                 net::URLRequestContextGetter* request_context_getter,
                 GCMStatsRecorder* recorder);
  virtual ~CheckinRequest();

  void Start();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

 private:
  
  
  void RetryWithBackoff(bool update_backoff);

  net::URLRequestContextGetter* request_context_getter_;
  CheckinRequestCallback callback_;

  net::BackoffEntry backoff_entry_;
  GURL checkin_url_;
  scoped_ptr<net::URLFetcher> url_fetcher_;
  const RequestInfo request_info_;
  base::TimeTicks request_start_time_;

  
  GCMStatsRecorder* recorder_;

  base::WeakPtrFactory<CheckinRequest> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(CheckinRequest);
};

}  

#endif  
