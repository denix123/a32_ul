// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_APPCACHE_SERVICE_H_
#define CONTENT_PUBLIC_BROWSER_APPCACHE_SERVICE_H_

#include <map>
#include <set>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "content/public/common/appcache_info.h"
#include "net/base/completion_callback.h"

namespace content {

class AppCacheStorage;

struct CONTENT_EXPORT AppCacheInfoCollection
    : public base::RefCountedThreadSafe<AppCacheInfoCollection> {
  AppCacheInfoCollection();

  std::map<GURL, AppCacheInfoVector> infos_by_origin;

 private:
  friend class base::RefCountedThreadSafe<AppCacheInfoCollection>;
  virtual ~AppCacheInfoCollection();
};

class CONTENT_EXPORT AppCacheService {
 public:
  
  
  virtual void CanHandleMainResourceOffline(const GURL& url,
                                            const GURL& first_party,
                                            const net::CompletionCallback&
                                            callback) = 0;

  
  
  
  
  virtual void GetAllAppCacheInfo(AppCacheInfoCollection* collection,
                                  const net::CompletionCallback& callback) = 0;

  
  
  
  
  
  virtual void DeleteAppCacheGroup(const GURL& manifest_url,
                                   const net::CompletionCallback& callback) = 0;

 protected:
  virtual ~AppCacheService() {}
};

}  

#endif  
