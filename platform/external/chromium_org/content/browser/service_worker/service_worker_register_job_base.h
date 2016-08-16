// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_REGISTER_JOB_BASE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_REGISTER_JOB_BASE_H_

namespace content {

class ServiceWorkerRegisterJobBase {
 public:
  enum RegistrationJobType {
    REGISTRATION_JOB,
    UNREGISTRATION_JOB,
    UPDATE_JOB
  };

  virtual ~ServiceWorkerRegisterJobBase() {}

  
  virtual void Start() = 0;

  
  
  virtual void Abort() = 0;

  
  
  
  
  virtual bool Equals(ServiceWorkerRegisterJobBase* job) = 0;

  
  virtual RegistrationJobType GetType() = 0;
};

}  

#endif  
