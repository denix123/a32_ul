// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_WEB_APPLICATION_INFO_H_
#define CHROME_COMMON_WEB_APPLICATION_INFO_H_

#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/size.h"
#include "url/gurl.h"

struct WebApplicationInfo {
  struct IconInfo {
    IconInfo();
    ~IconInfo();

    GURL url;
    int width;
    int height;
    SkBitmap data;
  };

  enum MobileCapable {
    MOBILE_CAPABLE_UNSPECIFIED,
    MOBILE_CAPABLE,
    MOBILE_CAPABLE_APPLE
  };

  WebApplicationInfo();
  ~WebApplicationInfo();

  
  base::string16 title;

  
  base::string16 description;

  
  GURL app_url;

  
  std::vector<IconInfo> icons;

  
  
  MobileCapable mobile_capable;
};

#endif  
