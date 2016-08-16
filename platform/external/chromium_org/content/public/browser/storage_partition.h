// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_STORAGE_PARTITION_H_
#define CONTENT_PUBLIC_BROWSER_STORAGE_PARTITION_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/time/time.h"
#include "content/common/content_export.h"

class GURL;

namespace base {
class Time;
}

namespace storage {
class FileSystemContext;
}

namespace net {
class URLRequestContextGetter;
}

namespace storage {
class QuotaManager;
class SpecialStoragePolicy;
}

namespace storage {
class DatabaseTracker;
}

namespace content {

class AppCacheService;
class BrowserContext;
class IndexedDBContext;
class DOMStorageContext;
class ServiceWorkerContext;

class CONTENT_EXPORT StoragePartition {
 public:
  virtual base::FilePath GetPath() = 0;
  virtual net::URLRequestContextGetter* GetURLRequestContext() = 0;
  virtual net::URLRequestContextGetter* GetMediaURLRequestContext() = 0;
  virtual storage::QuotaManager* GetQuotaManager() = 0;
  virtual AppCacheService* GetAppCacheService() = 0;
  virtual storage::FileSystemContext* GetFileSystemContext() = 0;
  virtual storage::DatabaseTracker* GetDatabaseTracker() = 0;
  virtual DOMStorageContext* GetDOMStorageContext() = 0;
  virtual IndexedDBContext* GetIndexedDBContext() = 0;
  virtual ServiceWorkerContext* GetServiceWorkerContext() = 0;

  static const uint32 REMOVE_DATA_MASK_APPCACHE        = 1 << 0;
  static const uint32 REMOVE_DATA_MASK_COOKIES         = 1 << 1;
  static const uint32 REMOVE_DATA_MASK_FILE_SYSTEMS    = 1 << 2;
  static const uint32 REMOVE_DATA_MASK_INDEXEDDB       = 1 << 3;
  static const uint32 REMOVE_DATA_MASK_LOCAL_STORAGE   = 1 << 4;
  static const uint32 REMOVE_DATA_MASK_SHADER_CACHE    = 1 << 5;
  static const uint32 REMOVE_DATA_MASK_WEBSQL          = 1 << 6;
  static const uint32 REMOVE_DATA_MASK_WEBRTC_IDENTITY = 1 << 7;
  static const uint32 REMOVE_DATA_MASK_SERVICE_WORKERS = 1 << 8;
  static const uint32 REMOVE_DATA_MASK_ALL             = 0xFFFFFFFF;

  
  static const uint32 QUOTA_MANAGED_STORAGE_MASK_TEMPORARY  = 1 << 0;
  
  static const uint32 QUOTA_MANAGED_STORAGE_MASK_PERSISTENT = 1 << 1;
  
  static const uint32 QUOTA_MANAGED_STORAGE_MASK_SYNCABLE   = 1 << 2;
  static const uint32 QUOTA_MANAGED_STORAGE_MASK_ALL        = 0xFFFFFFFF;

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void ClearDataForOrigin(uint32 remove_mask,
                                  uint32 quota_storage_remove_mask,
                                  const GURL& storage_origin,
                                  net::URLRequestContextGetter* rq_context,
                                  const base::Closure& callback) = 0;

  
  
  
  typedef base::Callback<bool(const GURL&, storage::SpecialStoragePolicy*)>
      OriginMatcherFunction;

  
  
  
  
  
  
  virtual void ClearData(uint32 remove_mask,
                         uint32 quota_storage_remove_mask,
                         const GURL& storage_origin,
                         const OriginMatcherFunction& origin_matcher,
                         const base::Time begin,
                         const base::Time end,
                         const base::Closure& callback) = 0;

 protected:
  virtual ~StoragePartition() {}
};

}  

#endif  
