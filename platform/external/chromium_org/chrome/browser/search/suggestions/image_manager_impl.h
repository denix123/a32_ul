// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_SUGGESTIONS_IMAGE_MANAGER_IMPL_H_
#define CHROME_BROWSER_SEARCH_SUGGESTIONS_IMAGE_MANAGER_IMPL_H_

#include <map>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/bitmap_fetcher/bitmap_fetcher.h"
#include "components/leveldb_proto/proto_database.h"
#include "components/suggestions/image_manager.h"
#include "components/suggestions/proto/suggestions.pb.h"
#include "ui/gfx/image/image_skia.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}

namespace suggestions {

class ImageData;
class SuggestionsProfile;

class ImageManagerImpl : public ImageManager,
                         public chrome::BitmapFetcherDelegate {
 public:
  typedef std::vector<ImageData> ImageDataVector;

  ImageManagerImpl(
      net::URLRequestContextGetter* url_request_context,
      scoped_ptr<leveldb_proto::ProtoDatabase<ImageData> > database,
      const base::FilePath& database_dir);
  virtual ~ImageManagerImpl();

  
  virtual void Initialize(const SuggestionsProfile& suggestions) OVERRIDE;
  
  virtual void GetImageForURL(
      const GURL& url,
      base::Callback<void(const GURL&, const SkBitmap*)> callback) OVERRIDE;

 private:
  friend class MockImageManagerImpl;
  friend class ImageManagerImplBrowserTest;
  FRIEND_TEST_ALL_PREFIXES(ImageManagerImplTest, InitializeTest);
  FRIEND_TEST_ALL_PREFIXES(ImageManagerImplBrowserTest,
                           GetImageForURLNetworkCacheHit);
  FRIEND_TEST_ALL_PREFIXES(ImageManagerImplBrowserTest,
                           GetImageForURLNetworkCacheNotInitialized);

  
  ImageManagerImpl();

  typedef std::vector<base::Callback<void(const GURL&, const SkBitmap*)> >
      CallbackVector;
  typedef base::hash_map<std::string, SkBitmap> ImageMap;

  
  
  struct ImageRequest {
    ImageRequest();
    explicit ImageRequest(chrome::BitmapFetcher* f);
    ~ImageRequest();

    void swap(ImageRequest* other) {
      std::swap(url, other->url);
      std::swap(image_url, other->image_url);
      std::swap(callbacks, other->callbacks);
      std::swap(fetcher, other->fetcher);
    }

    GURL url;
    GURL image_url;
    chrome::BitmapFetcher* fetcher;
    
    
    CallbackVector callbacks;
  };

  typedef std::map<const GURL, ImageRequest> ImageRequestMap;

  
  
  bool GetImageURL(const GURL& url, GURL* image_url);

  void QueueCacheRequest(
      const GURL& url, const GURL& image_url,
      base::Callback<void(const GURL&, const SkBitmap*)> callback);

  void ServeFromCacheOrNetwork(
      const GURL& url, const GURL& image_url,
      base::Callback<void(const GURL&, const SkBitmap*)> callback);

  
  
  bool ServeFromCache(
      const GURL& url,
      base::Callback<void(const GURL&, const SkBitmap*)> callback);

  
  SkBitmap* GetBitmapFromCache(const GURL& url);

  void StartOrQueueNetworkRequest(
      const GURL& url, const GURL& image_url,
      base::Callback<void(const GURL&, const SkBitmap*)> callback);

  
  virtual void OnFetchComplete(const GURL image_url,
                               const SkBitmap* bitmap) OVERRIDE;

  
  void SaveImage(const GURL& url, const SkBitmap& bitmap);

  
  
  void OnDatabaseInit(bool success);
  
  void OnDatabaseLoad(bool success, scoped_ptr<ImageDataVector> entries);
  void OnDatabaseSave(bool success);

  
  void LoadEntriesInCache(scoped_ptr<ImageDataVector> entries);

  void ServePendingCacheRequests();

  
  
  static bool EncodeImage(const SkBitmap& bitmap,
                          std::vector<unsigned char>* dest);

  
  
  std::map<GURL, GURL> image_url_map_;

  
  
  ImageRequestMap pending_net_requests_;

  
  
  ImageRequestMap pending_cache_requests_;

  
  ImageMap image_map_;

  net::URLRequestContextGetter* url_request_context_;

  scoped_ptr<leveldb_proto::ProtoDatabase<ImageData> > database_;

  bool database_ready_;

  base::WeakPtrFactory<ImageManagerImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ImageManagerImpl);
};

}  

#endif  
