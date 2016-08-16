// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_SERVICE_WORKER_USAGE_INFO_H_
#define CONTENT_PUBLIC_BROWSER_SERVICE_WORKER_USAGE_INFO_H_

#include <vector>

#include "content/common/content_export.h"
#include "url/gurl.h"

namespace content {

class CONTENT_EXPORT ServiceWorkerUsageInfo {
 public:
  ServiceWorkerUsageInfo(const GURL& origin, const std::vector<GURL>& scopes);
  ServiceWorkerUsageInfo(const GURL& origin);
  ServiceWorkerUsageInfo();
  ~ServiceWorkerUsageInfo();

  
  GURL origin;

  
  
  std::vector<GURL> scopes;

  
  
};

}  

#endif  
