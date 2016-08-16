// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BITMAP_FETCHER_DELEGATE_H_
#define CHROME_BROWSER_BITMAP_FETCHER_DELEGATE_H_

#include "url/gurl.h"

class SkBitmap;

namespace chrome {

class BitmapFetcherDelegate {
 public:
  BitmapFetcherDelegate() {}

  
  
  
  
  virtual void OnFetchComplete(const GURL url, const SkBitmap* bitmap) = 0;

 protected:
  virtual ~BitmapFetcherDelegate() {}

  DISALLOW_COPY_AND_ASSIGN(BitmapFetcherDelegate);
};

}  

#endif  
