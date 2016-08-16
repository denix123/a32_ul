// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_APPCACHE_HELPER_H_
#define CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_APPCACHE_HELPER_H_

#include <map>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "content/public/browser/appcache_service.h"
#include "net/base/completion_callback.h"
#include "url/gurl.h"

namespace content {
class BrowserContext;
}

class BrowsingDataAppCacheHelper
    : public base::RefCountedThreadSafe<BrowsingDataAppCacheHelper> {
 public:
  typedef std::map<GURL, content::AppCacheInfoVector> OriginAppCacheInfoMap;

  explicit BrowsingDataAppCacheHelper(content::BrowserContext* browser_context);

  virtual void StartFetching(const base::Closure& completion_callback);
  virtual void DeleteAppCacheGroup(const GURL& manifest_url);

  content::AppCacheInfoCollection* info_collection() const {
    DCHECK(!is_fetching_);
    return info_collection_.get();
  }

 protected:
  friend class base::RefCountedThreadSafe<BrowsingDataAppCacheHelper>;
  virtual ~BrowsingDataAppCacheHelper();

  base::Closure completion_callback_;
  scoped_refptr<content::AppCacheInfoCollection> info_collection_;

 private:
  void OnFetchComplete(int rv);

  bool is_fetching_;
  content::AppCacheService* appcache_service_;
  net::CancelableCompletionCallback appcache_info_callback_;

  DISALLOW_COPY_AND_ASSIGN(BrowsingDataAppCacheHelper);
};

class CannedBrowsingDataAppCacheHelper : public BrowsingDataAppCacheHelper {
 public:
  explicit CannedBrowsingDataAppCacheHelper(
      content::BrowserContext* browser_context);

  
  
  void AddAppCache(const GURL& manifest_url);

  
  void Reset();

  
  bool empty() const;

  
  size_t GetAppCacheCount() const;

  
  const OriginAppCacheInfoMap& GetOriginAppCacheInfoMap() const;

  
  virtual void StartFetching(const base::Closure& completion_callback) OVERRIDE;
  virtual void DeleteAppCacheGroup(const GURL& manifest_url) OVERRIDE;

 private:
  virtual ~CannedBrowsingDataAppCacheHelper();

  DISALLOW_COPY_AND_ASSIGN(CannedBrowsingDataAppCacheHelper);
};

#endif  
