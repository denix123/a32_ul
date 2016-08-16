// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_LOADER_CROSS_SITE_RESOURCE_HANDLER_H_
#define CONTENT_BROWSER_LOADER_CROSS_SITE_RESOURCE_HANDLER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/loader/layered_resource_handler.h"
#include "content/common/content_export.h"
#include "net/url_request/url_request_status.h"

namespace net {
class URLRequest;
}

namespace content {

struct TransitionLayerData;

class CrossSiteResourceHandler : public LayeredResourceHandler {
 public:
  CrossSiteResourceHandler(scoped_ptr<ResourceHandler> next_handler,
                           net::URLRequest* request);
  virtual ~CrossSiteResourceHandler();

  
  virtual bool OnRequestRedirected(const net::RedirectInfo& redirect_info,
                                   ResourceResponse* response,
                                   bool* defer) OVERRIDE;
  virtual bool OnResponseStarted(ResourceResponse* response,
                                 bool* defer) OVERRIDE;
  virtual bool OnReadCompleted(int bytes_read,
                               bool* defer) OVERRIDE;
  virtual void OnResponseCompleted(const net::URLRequestStatus& status,
                                   const std::string& security_info,
                                   bool* defer) OVERRIDE;

  
  
  void ResumeResponse();

  
  
  CONTENT_EXPORT static void SetLeakRequestsForTesting(
      bool leak_requests_for_testing);

  
  
  
  void ResumeResponseDeferredAtStart(int request_id);

  
  bool did_defer_for_testing() const { return did_defer_; }

 private:
  
  
  void StartCrossSiteTransition(ResourceResponse* response);

  
  
  bool DeferForNavigationPolicyCheck(ResourceRequestInfoImpl* info,
                                     ResourceResponse* response,
                                     bool* defer);

  bool OnNavigationTransitionResponseStarted(
      ResourceResponse* response,
      bool* defer,
      const TransitionLayerData& transition_data);

  bool OnNormalResponseStarted(ResourceResponse* response,
                               bool* defer);

  void ResumeOrTransfer(bool is_transfer);
  void ResumeIfDeferred();

  
  
  void OnDidDefer();

  bool has_started_response_;
  bool in_cross_site_transition_;
  bool completed_during_transition_;
  bool did_defer_;
  net::URLRequestStatus completed_status_;
  std::string completed_security_info_;
  scoped_refptr<ResourceResponse> response_;

  
  
  
  
  base::WeakPtrFactory<CrossSiteResourceHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(CrossSiteResourceHandler);
};

}  

#endif  
