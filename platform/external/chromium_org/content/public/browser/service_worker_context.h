// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_SERVICE_WORKER_CONTEXT_H_
#define CONTENT_PUBLIC_BROWSER_SERVICE_WORKER_CONTEXT_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "content/public/browser/service_worker_usage_info.h"
#include "url/gurl.h"

namespace content {

class ServiceWorkerContext {
 public:
  
  
  typedef GURL Scope;

  typedef base::Callback<void(bool success)> ResultCallback;

  typedef base::Callback<void(const std::vector<ServiceWorkerUsageInfo>&
                                  usage_info)> GetUsageInfoCallback;

  
  
  
  
  
  
  
  
  
  
  
  virtual void RegisterServiceWorker(const Scope& pattern,
                                     const GURL& script_url,
                                     const ResultCallback& callback) = 0;

  
  
  
  
  
  
  
  
  virtual void UnregisterServiceWorker(const Scope& pattern,
                                       const ResultCallback& callback) = 0;

  

  
  
  
  virtual void Terminate() = 0;

  
  virtual void GetAllOriginsInfo(const GetUsageInfoCallback& callback) = 0;
  virtual void DeleteForOrigin(const GURL& origin_url) = 0;

 protected:
  ServiceWorkerContext() {}
  virtual ~ServiceWorkerContext() {}
};

}  

#endif  
