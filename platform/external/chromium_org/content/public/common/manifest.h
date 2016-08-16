// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_MANIFEST_H_
#define CONTENT_PUBLIC_COMMON_MANIFEST_H_

#include <vector>

#include "base/strings/nullable_string16.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationLockType.h"
#include "ui/gfx/geometry/size.h"
#include "url/gurl.h"

namespace content {

struct CONTENT_EXPORT Manifest {
  enum DisplayMode {
    DISPLAY_MODE_UNSPECIFIED,
    DISPLAY_MODE_FULLSCREEN,
    DISPLAY_MODE_STANDALONE,
    DISPLAY_MODE_MINIMAL_UI,
    DISPLAY_MODE_BROWSER
  };

  
  
  struct CONTENT_EXPORT Icon {
    Icon();
    ~Icon();

    
    
    GURL src;

    
    
    
    
    base::NullableString16 type;

    
    double density;

    
    
    std::vector<gfx::Size> sizes;

    
    static const double kDefaultDensity;
  };

  Manifest();
  ~Manifest();

  
  
  bool IsEmpty() const;

  
  base::NullableString16 name;

  
  base::NullableString16 short_name;

  
  GURL start_url;

  
  
  DisplayMode display;

  
  
  blink::WebScreenOrientationLockType orientation;

  
  
  std::vector<Icon> icons;

  
  
  
  static const size_t kMaxIPCStringLength;
};

} 

#endif 
