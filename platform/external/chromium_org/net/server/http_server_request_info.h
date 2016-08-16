// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SERVER_HTTP_SERVER_REQUEST_INFO_H_
#define NET_SERVER_HTTP_SERVER_REQUEST_INFO_H_

#include <map>
#include <string>

#include "net/base/ip_endpoint.h"

namespace net {

class HttpServerRequestInfo {
 public:
  HttpServerRequestInfo();
  ~HttpServerRequestInfo();

  
  
  std::string GetHeaderValue(const std::string& header_name) const;

  
  
  bool HasHeaderValue(
      const std::string& header_name,
      const std::string& header_value) const;

  
  IPEndPoint peer;

  
  std::string method;

  
  std::string path;

  
  std::string data;

  
  
  typedef std::map<std::string, std::string> HeadersMap;
  mutable HeadersMap headers;
};

}  

#endif  
