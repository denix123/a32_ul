// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_BROWSER_CONFIGURATION_POLICY_HANDLER_PARAMETERS_H_
#define COMPONENTS_POLICY_CORE_BROWSER_CONFIGURATION_POLICY_HANDLER_PARAMETERS_H_

#include <string>

#include "components/policy/policy_export.h"

namespace policy {

struct POLICY_EXPORT PolicyHandlerParameters {
  std::string user_id_hash;
};

}  

#endif  
