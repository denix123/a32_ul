// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_CACHE_UTIL_H_
#define MEDIA_BLINK_CACHE_UTIL_H_

#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"

namespace blink {
class WebURLResponse;
}

namespace media {

enum UncacheableReason {
  kNoData = 1 << 0,  
  kPre11PartialResponse = 1 << 1,  
  kNoStrongValidatorOnPartialResponse = 1 << 2,  
  kShortMaxAge = 1 << 3,  
  kExpiresTooSoon = 1 << 4,  
  kHasMustRevalidate = 1 << 5,  
  kNoCache = 1 << 6,  
  kNoStore = 1 << 7,  
  kMaxReason  
};

uint32 MEDIA_EXPORT GetReasonsForUncacheability(
    const blink::WebURLResponse& response);

}  

#endif  
