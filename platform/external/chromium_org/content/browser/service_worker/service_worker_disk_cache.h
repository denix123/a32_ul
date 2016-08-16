// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_DISK_CACHE_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_DISK_CACHE_H_

#include "content/browser/appcache/appcache_disk_cache.h"
#include "content/common/content_export.h"

namespace content {


class CONTENT_EXPORT ServiceWorkerDiskCache
    : public AppCacheDiskCache {
};

class CONTENT_EXPORT ServiceWorkerResponseReader
    : public AppCacheResponseReader {
 protected:
  
  friend class ServiceWorkerStorage;
  ServiceWorkerResponseReader(
      int64 response_id,
      ServiceWorkerDiskCache* disk_cache);
};

class CONTENT_EXPORT ServiceWorkerResponseWriter
    : public AppCacheResponseWriter {
 protected:
  
  friend class ServiceWorkerStorage;
  ServiceWorkerResponseWriter(
      int64 response_id,
      ServiceWorkerDiskCache* disk_cache);
};

}  

#endif  
