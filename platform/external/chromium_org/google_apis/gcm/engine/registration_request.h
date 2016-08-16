// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_REGISTRATION_REQUEST_H_
#define GOOGLE_APIS_GCM_ENGINE_REGISTRATION_REQUEST_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "google_apis/gcm/base/gcm_export.h"
#include "net/base/backoff_entry.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}

namespace gcm {

class GCMStatsRecorder;

class GCM_EXPORT RegistrationRequest : public net::URLFetcherDelegate {
 public:
  
  
  
  
  enum Status {
    SUCCESS,                    
    INVALID_PARAMETERS,         
    INVALID_SENDER,             
    AUTHENTICATION_FAILED,      
    DEVICE_REGISTRATION_ERROR,  
    UNKNOWN_ERROR,              
    URL_FETCHING_FAILED,        
    HTTP_NOT_OK,                
    RESPONSE_PARSING_FAILED,    
    REACHED_MAX_RETRIES,        
    
    
    
    STATUS_COUNT
  };

  
  typedef base::Callback<void(Status status,
                              const std::string& registration_id)>
      RegistrationCallback;

  
  
  
  struct GCM_EXPORT RequestInfo {
    RequestInfo(uint64 android_id,
                uint64 security_token,
                const std::string& app_id,
                const std::vector<std::string>& sender_ids);
    ~RequestInfo();

    
    uint64 android_id;
    
    uint64 security_token;
    
    std::string app_id;
    
    std::string cert;
    
    std::vector<std::string> sender_ids;
  };

  RegistrationRequest(
      const GURL& registration_url,
      const RequestInfo& request_info,
      const net::BackoffEntry::Policy& backoff_policy,
      const RegistrationCallback& callback,
      int max_retry_count,
      scoped_refptr<net::URLRequestContextGetter> request_context_getter,
      GCMStatsRecorder* recorder);
  virtual ~RegistrationRequest();

  void Start();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

 private:
  
  
  void RetryWithBackoff(bool update_backoff);

  
  
  Status ParseResponse(const net::URLFetcher* source, std::string* token);

  RegistrationCallback callback_;
  RequestInfo request_info_;
  GURL registration_url_;

  net::BackoffEntry backoff_entry_;
  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;
  scoped_ptr<net::URLFetcher> url_fetcher_;
  int retries_left_;
  base::TimeTicks request_start_time_;

  
  GCMStatsRecorder* recorder_;

  base::WeakPtrFactory<RegistrationRequest> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(RegistrationRequest);
};

}  

#endif  
