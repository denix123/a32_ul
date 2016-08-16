// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
#define CONTENT_PUBLIC_BROWSER_RESOURCE_DISPATCHER_HOST_DELEGATE_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "content/public/common/resource_type.h"

class GURL;
template <class T> class ScopedVector;

namespace IPC {
class Sender;
}

namespace net {
class AuthChallengeInfo;
class URLRequest;
}

namespace content {

class AppCacheService;
class ResourceContext;
class ResourceDispatcherHostLoginDelegate;
class ResourceThrottle;
class StreamHandle;
struct Referrer;
struct ResourceResponse;

class CONTENT_EXPORT ResourceDispatcherHostDelegate {
 public:
  
  virtual bool ShouldBeginRequest(const std::string& method,
                                  const GURL& url,
                                  ResourceType resource_type,
                                  ResourceContext* resource_context);

  
  
  virtual void RequestBeginning(net::URLRequest* request,
                                ResourceContext* resource_context,
                                AppCacheService* appcache_service,
                                ResourceType resource_type,
                                ScopedVector<ResourceThrottle>* throttles);

  
  
  virtual void DownloadStarting(net::URLRequest* request,
                                ResourceContext* resource_context,
                                int child_id,
                                int route_id,
                                int request_id,
                                bool is_content_initiated,
                                bool must_download,
                                ScopedVector<ResourceThrottle>* throttles);

  
  
  virtual ResourceDispatcherHostLoginDelegate* CreateLoginDelegate(
      net::AuthChallengeInfo* auth_info,
      net::URLRequest* request);

  
  
  
  virtual bool HandleExternalProtocol(const GURL& url,
                                      int child_id,
                                      int route_id);

  
  
  virtual bool ShouldForceDownloadResource(const GURL& url,
                                           const std::string& mime_type);

  
  
  
  
  
  
  
  
  
  
  
  virtual bool ShouldInterceptResourceAsStream(net::URLRequest* request,
                                               const std::string& mime_type,
                                               GURL* origin,
                                               std::string* payload);

  
  
  virtual void OnStreamCreated(net::URLRequest* request,
                               scoped_ptr<content::StreamHandle> stream);

  
  virtual void OnResponseStarted(net::URLRequest* request,
                                 ResourceContext* resource_context,
                                 ResourceResponse* response,
                                 IPC::Sender* sender);

  
  virtual void OnRequestRedirected(const GURL& redirect_url,
                                   net::URLRequest* request,
                                   ResourceContext* resource_context,
                                   ResourceResponse* response);

  
  virtual void RequestComplete(net::URLRequest* url_request);

 protected:
  ResourceDispatcherHostDelegate();
  virtual ~ResourceDispatcherHostDelegate();
};

}  

#endif  
