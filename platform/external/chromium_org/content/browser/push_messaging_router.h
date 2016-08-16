// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_PUSH_MESSAGING_ROUTER_H_
#define CONTENT_BROWSER_PUSH_MESSAGING_ROUTER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "content/public/common/push_messaging_status.h"
#include "url/gurl.h"

namespace content {

class BrowserContext;
class ServiceWorkerContextWrapper;
class ServiceWorkerRegistration;

class PushMessagingRouter {
 public:
  typedef base::Callback<void(PushMessagingStatus )>
      DeliverMessageCallback;

  
  
  
  static void DeliverMessage(
      BrowserContext* browser_context,
      const GURL& origin,
      int64 service_worker_registration_id,
      const std::string& data,
      const DeliverMessageCallback& deliver_message_callback);

 private:
  
  
  static void FindServiceWorkerRegistration(
      const GURL& origin,
      int64 service_worker_registration_id,
      const std::string& data,
      const DeliverMessageCallback& deliver_message_callback,
      scoped_refptr<ServiceWorkerContextWrapper> service_worker_context);

  
  
  
  static void FindServiceWorkerRegistrationCallback(
      const std::string& data,
      const DeliverMessageCallback& deliver_message_callback,
      ServiceWorkerStatusCode service_worker_status,
      const scoped_refptr<ServiceWorkerRegistration>&
          service_worker_registration);

  
  
  static void DeliverMessageEnd(
      const DeliverMessageCallback& deliver_message_callback,
      const scoped_refptr<ServiceWorkerRegistration>&
          service_worker_registration,
      ServiceWorkerStatusCode service_worker_status);

  DISALLOW_IMPLICIT_CONSTRUCTORS(PushMessagingRouter);
};

}  

#endif  
