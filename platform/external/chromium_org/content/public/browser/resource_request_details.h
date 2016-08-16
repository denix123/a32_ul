// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_RESOURCE_REQUEST_DETAILS_H_
#define CONTENT_PUBLIC_BROWSER_RESOURCE_REQUEST_DETAILS_H_

#include <string>

#include "content/public/common/resource_type.h"
#include "net/base/host_port_pair.h"
#include "net/cert/cert_status_flags.h"
#include "net/url_request/url_request_status.h"
#include "url/gurl.h"

namespace net {
class URLRequest;
}

namespace content {

struct ResourceRequestDetails {
  ResourceRequestDetails(const net::URLRequest* request, int cert_id);

  virtual ~ResourceRequestDetails();

  GURL url;
  GURL original_url;
  std::string method;
  std::string referrer;
  bool has_upload;
  int load_flags;
  int origin_child_id;
  net::URLRequestStatus status;
  int ssl_cert_id;
  net::CertStatus ssl_cert_status;
  ResourceType resource_type;
  net::HostPortPair socket_address;
  int render_frame_id;
  
  
  int http_response_code;
};

struct ResourceRedirectDetails : public ResourceRequestDetails {
  ResourceRedirectDetails(const net::URLRequest* request,
                          int cert_id,
                          const GURL& new_url);
  virtual ~ResourceRedirectDetails();

  
  GURL new_url;
};

}  

#endif  
