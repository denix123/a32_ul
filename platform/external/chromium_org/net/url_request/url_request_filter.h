// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef NET_URL_REQUEST_URL_REQUEST_FILTER_H_
#define NET_URL_REQUEST_URL_REQUEST_FILTER_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"
#include "net/url_request/url_request.h"
#include "net/url_request/url_request_interceptor.h"

class GURL;

namespace net {
class URLRequestJob;
class URLRequestInterceptor;

class NET_EXPORT URLRequestFilter : public URLRequestInterceptor {
 public:
  static URLRequest::ProtocolFactory Factory;

  
  static URLRequestFilter* GetInstance();

  void AddHostnameHandler(const std::string& scheme,
                          const std::string& hostname,
                          URLRequest::ProtocolFactory* factory);
  void AddHostnameInterceptor(
      const std::string& scheme,
      const std::string& hostname,
      scoped_ptr<URLRequestInterceptor> interceptor);
  void RemoveHostnameHandler(const std::string& scheme,
                             const std::string& hostname);

  
  
  bool AddUrlHandler(const GURL& url,
                     URLRequest::ProtocolFactory* factory);
  bool AddUrlInterceptor(const GURL& url,
                         scoped_ptr<URLRequestInterceptor> interceptor);

  void RemoveUrlHandler(const GURL& url);

  
  
  void ClearHandlers();

  
  int hit_count() const { return hit_count_; }

  
  virtual URLRequestJob* MaybeInterceptRequest(
      URLRequest* request,
      NetworkDelegate* network_delegate) const OVERRIDE;

 private:
  
  typedef std::map<std::pair<std::string, std::string>,
      URLRequestInterceptor* > HostnameInterceptorMap;
  
  typedef base::hash_map<std::string, URLRequestInterceptor*> URLInterceptorMap;

  URLRequestFilter();
  virtual ~URLRequestFilter();

  
  HostnameInterceptorMap hostname_interceptor_map_;

  
  URLInterceptorMap url_interceptor_map_;

  mutable int hit_count_;

  
  static URLRequestFilter* shared_instance_;

  DISALLOW_COPY_AND_ASSIGN(URLRequestFilter);
};

}  

#endif  
