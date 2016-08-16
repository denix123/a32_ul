// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_CORE_FAVICON_DRIVER_H_
#define COMPONENTS_FAVICON_CORE_FAVICON_DRIVER_H_

class GURL;

namespace gfx {
class Image;
}

class FaviconDriver {
 public:

  
  
  
  
  
  
  
  
  virtual int StartDownload(const GURL& url, int max_bitmap_size) = 0;

  
  
  
  virtual void NotifyFaviconUpdated(bool icon_url_changed) = 0;

  
  virtual bool IsOffTheRecord() = 0;

  
  
  virtual const gfx::Image GetActiveFaviconImage() = 0;

  
  
  virtual const GURL GetActiveFaviconURL() = 0;

  
  
  virtual bool GetActiveFaviconValidity() = 0;

  
  
  virtual const GURL GetActiveURL() = 0;

  
  
  virtual void SetActiveFaviconImage(gfx::Image image) = 0;

  
  virtual void SetActiveFaviconURL(GURL url) = 0;

  
  
  virtual void SetActiveFaviconValidity(bool validity) = 0;
};

#endif  
