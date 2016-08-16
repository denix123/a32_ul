// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_SERVICE_WORKER_SERVICE_WORKER_STATUS_CODE_H_
#define CONTENT_COMMON_SERVICE_WORKER_SERVICE_WORKER_STATUS_CODE_H_

#include "content/common/content_export.h"

namespace content {

enum ServiceWorkerStatusCode {
  
  SERVICE_WORKER_OK,

  
  
  SERVICE_WORKER_ERROR_FAILED,

  
  SERVICE_WORKER_ERROR_ABORT,

  
  SERVICE_WORKER_ERROR_START_WORKER_FAILED,

  
  SERVICE_WORKER_ERROR_PROCESS_NOT_FOUND,

  
  SERVICE_WORKER_ERROR_NOT_FOUND,

  
  SERVICE_WORKER_ERROR_EXISTS,

  
  SERVICE_WORKER_ERROR_INSTALL_WORKER_FAILED,

  
  SERVICE_WORKER_ERROR_ACTIVATE_WORKER_FAILED,

  
  
  SERVICE_WORKER_ERROR_IPC_FAILED,

  
  SERVICE_WORKER_ERROR_NETWORK,

  
  SERVICE_WORKER_ERROR_SECURITY,
};

CONTENT_EXPORT const char* ServiceWorkerStatusToString(
    ServiceWorkerStatusCode code);

}  

#endif  
