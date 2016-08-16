// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_URL_REQUEST_URL_REQUEST_REDIRECT_JOB_H_
#define NET_URL_REQUEST_URL_REQUEST_REDIRECT_JOB_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "net/base/net_export.h"
#include "net/http/http_response_info.h"
#include "net/url_request/url_request_job.h"

class GURL;

namespace net {

class NET_EXPORT URLRequestRedirectJob : public URLRequestJob {
 public:
  
  
  
  
  enum ResponseCode {
    REDIRECT_302_FOUND = 302,
    REDIRECT_307_TEMPORARY_REDIRECT = 307,
  };

  
  
  URLRequestRedirectJob(URLRequest* request,
                        NetworkDelegate* network_delegate,
                        const GURL& redirect_destination,
                        ResponseCode response_code,
                        const std::string& redirect_reason);

  
  virtual void GetResponseInfo(HttpResponseInfo* info) OVERRIDE;
  virtual void GetLoadTimingInfo(
      LoadTimingInfo* load_timing_info) const OVERRIDE;
  virtual void Start() OVERRIDE;
  virtual bool CopyFragmentOnRedirect(const GURL& location) const OVERRIDE;
  virtual int GetResponseCode() const OVERRIDE;

 private:
  virtual ~URLRequestRedirectJob();

  void StartAsync();

  const GURL redirect_destination_;
  const ResponseCode response_code_;
  base::TimeTicks receive_headers_end_;
  base::Time response_time_;
  std::string redirect_reason_;

  scoped_refptr<HttpResponseHeaders> fake_headers_;

  base::WeakPtrFactory<URLRequestRedirectJob> weak_factory_;
};

}  

#endif  
