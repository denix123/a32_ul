// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_GEOLOCATION_SIMPLE_GEOLOCATION_PROVIDER_H_
#define CHROME_BROWSER_CHROMEOS_GEOLOCATION_SIMPLE_GEOLOCATION_PROVIDER_H_

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "chrome/browser/chromeos/geolocation/simple_geolocation_request.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}

namespace chromeos {

class SimpleGeolocationProvider {
 public:
  SimpleGeolocationProvider(net::URLRequestContextGetter* url_context_getter,
                            const GURL& url);
  virtual ~SimpleGeolocationProvider();

  
  
  void RequestGeolocation(base::TimeDelta timeout,
                          SimpleGeolocationRequest::ResponseCallback callback);

  
  static GURL DefaultGeolocationProviderURL();

 private:
  friend class TestGeolocationAPIURLFetcherCallback;

  
  void OnGeolocationResponse(
      SimpleGeolocationRequest* request,
      SimpleGeolocationRequest::ResponseCallback callback,
      const Geoposition& geoposition,
      bool server_error,
      const base::TimeDelta elapsed);

  scoped_refptr<net::URLRequestContextGetter> url_context_getter_;

  
  const GURL url_;

  
  
  
  ScopedVector<SimpleGeolocationRequest> requests_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(SimpleGeolocationProvider);
};

}  

#endif  
