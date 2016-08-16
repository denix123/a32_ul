// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_MAC_UTIL_H_
#define COMPONENTS_POLICY_CORE_COMMON_MAC_UTIL_H_

#include <CoreFoundation/CoreFoundation.h>

#include "base/memory/scoped_ptr.h"
#include "components/policy/policy_export.h"


namespace base {
class Value;
}

namespace policy {

POLICY_EXPORT scoped_ptr<base::Value> PropertyToValue(
    CFPropertyListRef property);

}  

#endif  
