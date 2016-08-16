// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_IMAGE_STORE_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_IMAGE_STORE_H_

#include <map>
#include <set>

#include "base/sequence_checker.h"
#include "ui/gfx/image/image.h"

class GURL;

class ImageStore {
 public:
  ImageStore();
  virtual ~ImageStore();

  
  virtual bool HasKey(const GURL& page_url) = 0;

  
  
  
  
  virtual void Insert(const GURL& page_url,
                      const GURL& image_url,
                      const gfx::Image& image) = 0;

  
  virtual void Erase(const GURL& page_url) = 0;

  
  
  
  virtual std::pair<gfx::Image, GURL> Get(const GURL& page_url) = 0;

  
  
  virtual gfx::Size GetSize(const GURL& page_url) = 0;

  
  virtual void GetAllPageUrls(std::set<GURL>* urls) = 0;

  
  virtual void ClearAll() = 0;

  
  void ChangeImageURL(const GURL& from, const GURL& to);

  
  
  virtual int64 GetStoreSizeInBytes() = 0;

 protected:
  base::SequenceChecker sequence_checker_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ImageStore);
};

#endif  
