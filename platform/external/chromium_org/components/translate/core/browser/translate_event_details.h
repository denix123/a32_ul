// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_EVENT_DETAILS_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_EVENT_DETAILS_H_

#include <string>

#include "base/time/time.h"

namespace translate {

struct TranslateEventDetails {
  TranslateEventDetails(const std::string& in_filename,
                        int in_line,
                        const std::string& in_message);

  
  base::Time time;

  
  std::string filename;

  
  int line;

  
  std::string message;
};

}  

#endif  
