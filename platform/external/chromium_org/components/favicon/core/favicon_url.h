// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_CORE_FAVICON_URL_
#define COMPONENTS_FAVICON_CORE_FAVICON_URL_

#include <vector>

#include "components/favicon_base/favicon_types.h"
#include "ui/gfx/geometry/size.h"
#include "url/gurl.h"

namespace favicon {

struct FaviconURL {
  FaviconURL();
  FaviconURL(const GURL& url,
             favicon_base::IconType type,
             const std::vector<gfx::Size>& sizes);
  ~FaviconURL();

  
  GURL icon_url;

  
  favicon_base::IconType icon_type;

  
  std::vector<gfx::Size> icon_sizes;
};

}  

#endif  
