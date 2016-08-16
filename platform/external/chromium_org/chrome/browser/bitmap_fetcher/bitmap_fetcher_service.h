// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef CHROME_BROWSER_BITMAP_FETCHER_BITMAP_FETCHER_SERVICE_H_
#define CHROME_BROWSER_BITMAP_FETCHER_BITMAP_FETCHER_SERVICE_H_

#include "base/compiler_specific.h"
#include "base/containers/mru_cache.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "chrome/browser/bitmap_fetcher_delegate.h"
#include "components/keyed_service/core/keyed_service.h"

namespace content {
class BrowserContext;
}  

namespace chrome {
class BitmapFetcher;
}  

class BitmapFetcherRequest;
class GURL;
class SkBitmap;

class BitmapFetcherService : public KeyedService,
                             public chrome::BitmapFetcherDelegate {
 public:
  typedef int RequestId;
  static const RequestId REQUEST_ID_INVALID = 0;

  class Observer {
   public:
    virtual ~Observer() {}

    
    
    virtual void OnImageChanged(RequestId request_id,
                                const SkBitmap& answers_image) = 0;
  };

  explicit BitmapFetcherService(content::BrowserContext* context);
  virtual ~BitmapFetcherService();

  
  void CancelRequest(RequestId requestId);

  
  
  
  
  
  
  
  RequestId RequestImage(const GURL& url, Observer* observer);

  
  void Prefetch(const GURL& url);

 protected:
  
  
  virtual chrome::BitmapFetcher* CreateFetcher(const GURL& url);

 private:
  friend class BitmapFetcherServiceTest;

  typedef ScopedVector<chrome::BitmapFetcher> BitmapFetchers;

  
  
  const chrome::BitmapFetcher* EnsureFetcherForUrl(const GURL& url);

  
  const chrome::BitmapFetcher* FindFetcherForUrl(const GURL& url);

  
  
  void RemoveFetcher(const chrome::BitmapFetcher* fetcher);

  
  virtual void OnFetchComplete(const GURL url, const SkBitmap* bitmap) OVERRIDE;

  
  BitmapFetchers active_fetchers_;

  
  ScopedVector<BitmapFetcherRequest> requests_;

  
  struct CacheEntry {
    CacheEntry();
    ~CacheEntry();

    scoped_ptr<const SkBitmap> bitmap;
  };
  base::OwningMRUCache<GURL, CacheEntry*> cache_;

  
  int current_request_id_;

  
  content::BrowserContext* context_;

  DISALLOW_COPY_AND_ASSIGN(BitmapFetcherService);
};

#endif  
