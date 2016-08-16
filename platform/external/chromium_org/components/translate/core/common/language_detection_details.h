// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_COMMON_LANGUAGE_DETECTION_DETAILS_H_
#define COMPONENTS_TRANSLATE_CORE_COMMON_LANGUAGE_DETECTION_DETAILS_H_

#include <string>

#include "base/strings/string16.h"
#include "base/time/time.h"
#include "url/gurl.h"

namespace translate {

struct LanguageDetectionDetails {
  LanguageDetectionDetails();
  ~LanguageDetectionDetails();

  
  base::Time time;

  
  GURL url;

  
  std::string content_language;

  
  std::string cld_language;

  
  bool is_cld_reliable;

  // The language written in the lang attribute of the html element.
  std::string html_root_language;

  
  std::string adopted_language;

  
  base::string16 contents;
};

}  

#endif  
