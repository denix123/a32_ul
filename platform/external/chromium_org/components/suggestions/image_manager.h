// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SUGGESTIONS_IMAGE_MANAGER_H_
#define COMPONENTS_SUGGESTIONS_IMAGE_MANAGER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "components/suggestions/proto/suggestions.pb.h"
#include "ui/gfx/image/image_skia.h"
#include "url/gurl.h"

namespace suggestions {

class ImageManager {
 public:
  ImageManager() {}
  virtual ~ImageManager() {}

  
  
  virtual void Initialize(const SuggestionsProfile& suggestions) = 0;

  
  
  virtual void GetImageForURL(
      const GURL& url,
      base::Callback<void(const GURL&, const SkBitmap*)> callback) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(ImageManager);
};

}  

#endif  
