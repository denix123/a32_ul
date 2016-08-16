// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_URL_REQUEST_URL_REQUEST_INTERCEPTOR_H_
#define NET_URL_REQUEST_URL_REQUEST_INTERCEPTOR_H_

#include "base/macros.h"
#include "net/base/net_export.h"

namespace net {

class URLRequest;
class URLRequestJob;
class NetworkDelegate;

class NET_EXPORT URLRequestInterceptor {
 public:
  URLRequestInterceptor();
  virtual ~URLRequestInterceptor();

  
  
  
  virtual URLRequestJob* MaybeInterceptRequest(
      URLRequest* request, NetworkDelegate* network_delegate) const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(URLRequestInterceptor);
};

}  

#endif  
