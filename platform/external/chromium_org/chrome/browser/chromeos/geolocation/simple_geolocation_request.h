// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_GEOLOCATION_SIMPLE_GEOLOCATION_REQUEST_H_
#define CHROME_BROWSER_CHROMEOS_GEOLOCATION_SIMPLE_GEOLOCATION_REQUEST_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/timer/timer.h"
#include "chrome/browser/chromeos/geolocation/geoposition.h"
#include "net/url_request/url_fetcher.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}

namespace chromeos {

class SimpleGeolocationRequest : private net::URLFetcherDelegate {
 public:
  
  
  
  
  typedef base::Callback<void(const Geoposition& ,
                              bool ,
                              const base::TimeDelta elapsed)> ResponseCallback;

  
  
  SimpleGeolocationRequest(net::URLRequestContextGetter* url_context_getter,
                           const GURL& service_url,
                           base::TimeDelta timeout);

  virtual ~SimpleGeolocationRequest();

  
  
  
  void MakeRequest(const ResponseCallback& callback);

  void set_retry_sleep_on_server_error_for_testing(
      const base::TimeDelta value) {
    retry_sleep_on_server_error_ = value;
  }

  void set_retry_sleep_on_bad_response_for_testing(
      const base::TimeDelta value) {
    retry_sleep_on_bad_response_ = value;
  }

 private:
  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  void StartRequest();

  
  void Retry(bool server_error);

  
  void ReplyAndDestroySelf(const base::TimeDelta elapsed, bool server_error);

  
  void OnTimeout();

  scoped_refptr<net::URLRequestContextGetter> url_context_getter_;

  
  const GURL service_url_;

  ResponseCallback callback_;

  
  GURL request_url_;

  scoped_ptr<net::URLFetcher> url_fetcher_;

  
  base::Time request_started_at_;

  base::TimeDelta retry_sleep_on_server_error_;

  base::TimeDelta retry_sleep_on_bad_response_;

  const base::TimeDelta timeout_;

  
  base::OneShotTimer<SimpleGeolocationRequest> request_scheduled_;

  
  base::OneShotTimer<SimpleGeolocationRequest> timeout_timer_;

  
  unsigned retries_;

  
  Geoposition position_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(SimpleGeolocationRequest);
};

}  

#endif  
