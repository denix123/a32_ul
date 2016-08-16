// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_ERROR_DETAILS_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_ERROR_DETAILS_H_

#include "base/time/time.h"
#include "components/translate/core/common/translate_errors.h"
#include "url/gurl.h"

namespace translate {

struct TranslateErrorDetails {
  
  base::Time time;

  
  GURL url;

  
  TranslateErrors::Type error;
};

}  

#endif  
