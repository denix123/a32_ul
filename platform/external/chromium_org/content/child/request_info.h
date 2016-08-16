// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_REQUEST_INFO_H_
#define CONTENT_CHILD_REQUEST_INFO_H_

#include <stdint.h>

#include <string>

#include "content/common/content_export.h"
#include "content/public/common/resource_type.h"
#include "net/base/request_priority.h"
#include "third_party/WebKit/public/platform/WebReferrerPolicy.h"
#include "third_party/WebKit/public/platform/WebURLRequest.h"
#include "url/gurl.h"

namespace content {

struct CONTENT_EXPORT RequestInfo {
  RequestInfo();
  ~RequestInfo();

  
  std::string method;

  
  GURL url;

  
  
  GURL first_party_for_cookies;

  
  
  GURL referrer;

  
  blink::WebReferrerPolicy referrer_policy;

  
  
  
  
  std::string headers;

  
  int load_flags;

  
  int requestor_pid;

  
  
  ResourceType request_type;

  
  net::RequestPriority priority;

  
  uint32_t request_context;

  
  int appcache_host_id;

  
  int routing_id;

  
  
  bool download_to_file;

  
  bool has_user_gesture;

  
  bool skip_service_worker;

  
  
  bool enable_load_timing;

  
  blink::WebURLRequest::ExtraData* extra_data;

 private:
  DISALLOW_COPY_AND_ASSIGN(RequestInfo);
};

}  

#endif  
