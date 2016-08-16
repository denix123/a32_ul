// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BITMAP_FETCHER_BITMAP_FETCHER_H_
#define CHROME_BROWSER_BITMAP_FETCHER_BITMAP_FETCHER_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/bitmap_fetcher_delegate.h"
#include "chrome/browser/image_decoder.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "net/url_request/url_request.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "url/gurl.h"

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}  

namespace chrome {

class BitmapFetcher : public net::URLFetcherDelegate,
                      public ImageDecoder::Delegate {
 public:
  BitmapFetcher(const GURL& url, BitmapFetcherDelegate* delegate);
  virtual ~BitmapFetcher();

  const GURL& url() const { return url_; }

  
  
  
  
  
  
  void Start(net::URLRequestContextGetter* request_context,
             const std::string& referrer,
             net::URLRequest::ReferrerPolicy referrer_policy,
             int load_flags);

  

  
  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  
  
  virtual void OnURLFetchDownloadProgress(const net::URLFetcher* source,
                                          int64 current,
                                          int64 total) OVERRIDE;

  

  
  
  
  virtual void OnImageDecoded(const ImageDecoder* decoder,
                              const SkBitmap& decoded_image) OVERRIDE;

  
  virtual void OnDecodeImageFailed(const ImageDecoder* decoder) OVERRIDE;

 private:
  
  void ReportFailure();

  scoped_ptr<net::URLFetcher> url_fetcher_;
  scoped_refptr<ImageDecoder> image_decoder_;
  const GURL url_;
  BitmapFetcherDelegate* const delegate_;

  DISALLOW_COPY_AND_ASSIGN(BitmapFetcher);
};

}  

#endif  
