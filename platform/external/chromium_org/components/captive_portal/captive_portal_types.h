// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_CAPTIVE_PORTAL_CAPTIVE_PORTAL_TYPES_H_
#define NET_CAPTIVE_PORTAL_CAPTIVE_PORTAL_TYPES_H_

#include <string>

#include "components/captive_portal/captive_portal_export.h"

namespace captive_portal {

enum CaptivePortalResult {
  
  RESULT_INTERNET_CONNECTED,
  
  RESULT_NO_RESPONSE,
  
  
  RESULT_BEHIND_CAPTIVE_PORTAL,
  RESULT_COUNT
};

CAPTIVE_PORTAL_EXPORT extern std::string CaptivePortalResultToString(
    CaptivePortalResult result);

}  

#endif  
