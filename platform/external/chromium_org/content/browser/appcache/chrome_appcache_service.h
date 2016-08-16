// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_APPCACHE_CHROME_APPCACHE_SERVICE_H_
#define CONTENT_BROWSER_APPCACHE_CHROME_APPCACHE_SERVICE_H_

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/sequenced_task_runner_helpers.h"
#include "content/browser/appcache/appcache_policy.h"
#include "content/browser/appcache/appcache_service_impl.h"
#include "content/common/content_export.h"
#include "storage/browser/quota/special_storage_policy.h"

namespace base {
class FilePath;
}

namespace net {
class URLRequestContextGetter;
}

namespace content {
class ResourceContext;

struct ChromeAppCacheServiceDeleter;

class CONTENT_EXPORT ChromeAppCacheService
    : public base::RefCountedThreadSafe<ChromeAppCacheService,
                                        ChromeAppCacheServiceDeleter>,
      NON_EXPORTED_BASE(public AppCacheServiceImpl),
      NON_EXPORTED_BASE(public AppCachePolicy) {
 public:
  explicit ChromeAppCacheService(storage::QuotaManagerProxy* proxy);

  
  void InitializeOnIOThread(
      const base::FilePath& cache_path,
      ResourceContext* resource_context,
      net::URLRequestContextGetter* request_context_getter,
      scoped_refptr<storage::SpecialStoragePolicy> special_storage_policy);

  
  virtual bool CanLoadAppCache(const GURL& manifest_url,
                               const GURL& first_party) OVERRIDE;
  virtual bool CanCreateAppCache(const GURL& manifest_url,
                                 const GURL& first_party) OVERRIDE;

 protected:
  virtual ~ChromeAppCacheService();

 private:
  friend class base::DeleteHelper<ChromeAppCacheService>;
  friend class base::RefCountedThreadSafe<ChromeAppCacheService,
                                          ChromeAppCacheServiceDeleter>;
  friend struct ChromeAppCacheServiceDeleter;

  void DeleteOnCorrectThread() const;

  ResourceContext* resource_context_;
  base::FilePath cache_path_;

  DISALLOW_COPY_AND_ASSIGN(ChromeAppCacheService);
};

struct ChromeAppCacheServiceDeleter {
  static void Destruct(const ChromeAppCacheService* service) {
    service->DeleteOnCorrectThread();
  }
};

}  

#endif  