// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_TIMEZONE_TIMEZONE_REQUEST_H_
#define CHROME_BROWSER_CHROMEOS_TIMEZONE_TIMEZONE_REQUEST_H_

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

struct TimeZoneResponseData {
  enum Status {
    OK,
    INVALID_REQUEST,
    OVER_QUERY_LIMIT,
    REQUEST_DENIED,
    UNKNOWN_ERROR,
    ZERO_RESULTS,
    REQUEST_ERROR  
  };

  TimeZoneResponseData();

  std::string ToStringForDebug() const;

  double dstOffset;
  double rawOffset;
  std::string timeZoneId;
  std::string timeZoneName;
  std::string error_message;
  Status status;
};

GURL DefaultTimezoneProviderURL();

class TimeZoneRequest : private net::URLFetcherDelegate {
 public:
  
  
  
  
  typedef base::Callback<void(scoped_ptr<TimeZoneResponseData> ,
                              bool )>
      TimeZoneResponseCallback;

  
  
  
  
  TimeZoneRequest(net::URLRequestContextGetter* url_context_getter,
                  const GURL& service_url,
                  const Geoposition& geoposition,
                  bool sensor,
                  base::TimeDelta retry_timeout);

  virtual ~TimeZoneRequest();

  
  
  
  void MakeRequest(TimeZoneResponseCallback callback);

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

  scoped_refptr<net::URLRequestContextGetter> url_context_getter_;
  const GURL service_url_;
  Geoposition geoposition_;
  const bool sensor_;

  TimeZoneResponseCallback callback_;

  GURL request_url_;
  scoped_ptr<net::URLFetcher> url_fetcher_;

  
  base::Time request_started_at_;

  
  base::Time retry_timeout_abs_;

  
  base::OneShotTimer<TimeZoneRequest> timezone_request_scheduled_;

  base::TimeDelta retry_sleep_on_server_error_;

  base::TimeDelta retry_sleep_on_bad_response_;

  
  unsigned retries_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(TimeZoneRequest);
};

}  

#endif  
