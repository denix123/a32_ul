// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_TIMEZONE_TIMEZONE_PROVIDER_H_
#define CHROME_BROWSER_CHROMEOS_TIMEZONE_TIMEZONE_PROVIDER_H_

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "chrome/browser/chromeos/timezone/timezone_request.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}

namespace chromeos {

struct Geoposition;

class TimeZoneProvider {
 public:
  TimeZoneProvider(net::URLRequestContextGetter* url_context_getter,
                   const GURL& url);
  virtual ~TimeZoneProvider();

  
  void RequestTimezone(const Geoposition& position,
                       bool sensor,
                       base::TimeDelta timeout,
                       TimeZoneRequest::TimeZoneResponseCallback callback);

 private:
  friend class TestTimeZoneAPIURLFetcherCallback;

  
  void OnTimezoneResponse(TimeZoneRequest* request,
                          TimeZoneRequest::TimeZoneResponseCallback callback,
                          scoped_ptr<TimeZoneResponseData> timezone,
                          bool server_error);

  scoped_refptr<net::URLRequestContextGetter> url_context_getter_;
  const GURL url_;

  
  
  ScopedVector<TimeZoneRequest> requests_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(TimeZoneProvider);
};

}  

#endif  
