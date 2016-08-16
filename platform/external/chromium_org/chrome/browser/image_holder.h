// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_IMAGE_HOLDER_H_
#define CHROME_BROWSER_IMAGE_HOLDER_H_

#include "base/memory/scoped_vector.h"
#include "chrome/browser/bitmap_fetcher/bitmap_fetcher.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/image/image_skia.h"
#include "url/gurl.h"

class Profile;

namespace chrome {

class ImageHolderDelegate {
 public:
  virtual void OnFetchComplete() = 0;
};

class ImageHolder : public chrome::BitmapFetcherDelegate {
 public:
  ImageHolder(const GURL& low_dpi_url,
              const GURL& high_dpi_url,
              Profile* profile,
              ImageHolderDelegate* delegate);
  virtual ~ImageHolder();

  
  void StartFetch();

  
  
  bool IsFetchingDone() const;

  
  virtual void OnFetchComplete(const GURL url, const SkBitmap* bitmap) OVERRIDE;

  
  GURL low_dpi_url() const { return low_dpi_url_; }
  GURL high_dpi_url() const { return high_dpi_url_; }
  gfx::Image low_dpi_image() { return gfx::Image(image_); }

 private:
  
  void CreateBitmapFetcher(const GURL& url);

  GURL low_dpi_url_;
  GURL high_dpi_url_;
  bool low_dpi_fetched_;
  bool high_dpi_fetched_;
  gfx::ImageSkia image_;
  ImageHolderDelegate* delegate_;
  ScopedVector<chrome::BitmapFetcher> fetchers_;
  Profile* profile_;

  FRIEND_TEST_ALL_PREFIXES(ImageHolderTest, CreateBitmapFetcherTest);
  FRIEND_TEST_ALL_PREFIXES(ImageHolderTest, OnFetchCompleteTest);
  FRIEND_TEST_ALL_PREFIXES(ImageHolderTest, IsFetchingDoneTest);

  DISALLOW_COPY_AND_ASSIGN(ImageHolder);
};

}  

#endif  
