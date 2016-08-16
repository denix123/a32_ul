// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_PROVIDER_LOGOS_LOGO_COMMON_H_
#define COMPONENTS_SEARCH_PROVIDER_LOGOS_LOGO_COMMON_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/ref_counted_memory.h"
#include "base/time/time.h"
#include "third_party/skia/include/core/SkBitmap.h"

namespace search_provider_logos {

extern const int64 kMaxTimeToLiveMS;

struct LogoMetadata {
  LogoMetadata();
  ~LogoMetadata();

  

  
  std::string on_click_url;
  
  std::string alt_text;
  
  std::string mime_type;

  

  
  std::string source_url;
  
  
  std::string fingerprint;
  
  
  bool can_show_after_expiration;
  
  
  base::Time expiration_time;
};

struct EncodedLogo {
  EncodedLogo();
  ~EncodedLogo();

  
  scoped_refptr<base::RefCountedString> encoded_image;
  
  LogoMetadata metadata;
};

struct Logo {
  Logo();
  ~Logo();

  
  SkBitmap image;
  
  LogoMetadata metadata;
};

}  

#endif  
