// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_USER_AGENT_H_
#define CONTENT_PUBLIC_COMMON_USER_AGENT_H_

#include <string>

#include "content/common/content_export.h"

namespace content {

CONTENT_EXPORT std::string GetWebKitVersion();

CONTENT_EXPORT int GetWebKitMajorVersion();
CONTENT_EXPORT int GetWebKitMinorVersion();

CONTENT_EXPORT std::string GetWebKitRevision();

CONTENT_EXPORT std::string BuildOSCpuInfo();

CONTENT_EXPORT std::string BuildUserAgentFromProduct(
    const std::string& product);

CONTENT_EXPORT std::string BuildUserAgentFromOSAndProduct(
    const std::string& os_info,
    const std::string& product);

}  

#endif  
