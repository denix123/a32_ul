// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_UNREGISTRATION_REQUEST_H_
#define GOOGLE_APIS_GCM_ENGINE_UNREGISTRATION_REQUEST_H_

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

class GCM_EXPORT UnregistrationRequest : public net::URLFetcherDelegate {
 public:
  
  
  enum Status {
    SUCCESS,                  
    URL_FETCHING_FAILED,      
    NO_RESPONSE_BODY,         
    RESPONSE_PARSING_FAILED,  
                              
                              
    INCORRECT_APP_ID,         
                              
    INVALID_PARAMETERS,       
    SERVICE_UNAVAILABLE,      
    INTERNAL_SERVER_ERROR,    
    HTTP_NOT_OK,              
    UNKNOWN_ERROR,            
    
    
    
    UNREGISTRATION_STATUS_COUNT,
  };

  
  typedef base::Callback<void(Status success)> UnregistrationCallback;

  
  struct GCM_EXPORT RequestInfo {
    RequestInfo(uint64 android_id,
                uint64 security_token,
                const std::string& app_id);
    ~RequestInfo();

    
    uint64 android_id;
    
    uint64 security_token;
    
    std::string app_id;
  };

  
  
  
  UnregistrationRequest(
      const GURL& registration_url,
      const RequestInfo& request_info,
      const net::BackoffEntry::Policy& backoff_policy,
      const UnregistrationCallback& callback,
      scoped_refptr<net::URLRequestContextGetter> request_context_getter,
      GCMStatsRecorder* recorder);
  virtual ~UnregistrationRequest();

  
  void Start();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

 private:
  
  
  void RetryWithBackoff(bool update_backoff);

  UnregistrationCallback callback_;
  RequestInfo request_info_;
  GURL registration_url_;

  net::BackoffEntry backoff_entry_;
  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;
  scoped_ptr<net::URLFetcher> url_fetcher_;
  base::TimeTicks request_start_time_;

  
  GCMStatsRecorder* recorder_;

  base::WeakPtrFactory<UnregistrationRequest> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(UnregistrationRequest);
};

}  

#endif  
